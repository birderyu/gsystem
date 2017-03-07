#include "grunnable.h"

#ifdef G_SYSTEM_WINDOWS

#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif

#include <windows.h>
#include <process.h>

#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

#ifdef G_SYSTEM_WINDOWS
guint WINAPI ThreadProc4Win32(gpointer param)
{
	if (!param)
	{
		return 0;
	}
	GRunnable* thread = (GRunnable*)param;
	thread->Run();
	return 0;
}
#endif // G_SYSTEM_WINDOWS

GRunnable::GRunnable()
	: m_pHandle(GNULL)
{

}

GRunnable::~GRunnable()
{
	Stop(0);
}

gbool GRunnable::Start()
{
#ifdef G_SYSTEM_WINDOWS
	guint thread_addr;
	HANDLE thread_handle = (HANDLE)_beginthreadex(GNULL, 0, ThreadProc4Win32, this, 0, &thread_addr);
	if (thread_handle == GNULL)
	{
		m_pHandle = GNULL;
		return false;
	}
	m_pHandle = (gpointer)thread_handle;
	return true;
#else // !G_SYSTEM_WINDOWS
	// TODO，线程的跨平台实现
	return false;
#endif // G_SYSTEM_WINDOWS
}

gvoid GRunnable::Stop(gulong msecs)
{
	if (GNULL == m_pHandle)
	{
		return;
	}
#ifdef G_SYSTEM_WINDOWS
	HANDLE thread_handle = (HANDLE)m_pHandle;
	if (WAIT_OBJECT_0 != WaitForSingleObject(thread_handle, msecs))
	{
		TerminateThread(thread_handle, 0);
	}
	CloseHandle(thread_handle);
	m_pHandle = GNULL;
#else // !G_SYSTEM_WINDOWS
	// TODO，线程的跨平台实现
#endif // G_SYSTEM_WINDOWS
}