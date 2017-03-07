#include "gthread.h"

#ifdef G_SYSTEM_WINDOWS

#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif

#include <windows.h>
#include <process.h>

#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

gvoid GThread::Sleep(gulong nSecs)
{
	::Sleep(1000 * nSecs);
}

gvoid GThread::MSleep(gulong nMsecs)
{
	::Sleep(nMsecs);
}

gvoid GThread::Join(GRunnable &thread)
{
#ifdef G_SYSTEM_WINDOWS
	HANDLE thread_handle = (HANDLE)thread.m_pHandle;
	if (thread_handle)
	{
		WaitForSingleObject(thread_handle, INFINITE);
		thread.m_pHandle = GNULL;
	}
#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS
}

GThread::GThread()
{

}

GThread::GThread(GThread &&thread)
{
	
}

GThread::~GThread()
{

}

GThread &GThread::operator==(GThread &&thread)
{
	return *this;
}

gbool GThread::Start()
{
	return GRunnable::Start();
}

gvoid GThread::Stop(gulong msecs)
{
	GRunnable::Stop();
}

gint GThread::Run()
{
	return 0;
}