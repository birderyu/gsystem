#include "gthread.h"
#include "gnew.h"

#ifdef G_SYSTEM_WINDOWS

#include <windows.h>
#include <process.h>

/// Win32½ø³ÌÊµÀý¾ä±ú
struct GThread_Handle 
	: public GNewT<GThread_Handle>
{
	HANDLE m_hThread;
};

guint WINAPI ThreadProc4Win32(gpointer pParam)
{
	if (!pParam)
	{
		return 0;
	}
	GThread* pThread = (GThread*)pParam;
	pThread->Run();
	return 0;
}

GThread::GThread()
:m_pHandle(NULL)
{

}

GThread::~GThread()
{
	if (m_pHandle)
	{
		Stop(0);
		GThread_Handle *pHandle = (GThread_Handle*)m_pHandle;
		delete pHandle;
		m_pHandle = NULL;
	}
}

gint GThread::Start()
{
	GThread_Handle* pHandle = new GThread_Handle;
	if (!pHandle)
	{
		return -1;
	}

	m_pHandle = pHandle;
	guint nThreadAddr;
	pHandle->m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc4Win32, this, 0, &nThreadAddr);
	if (pHandle->m_hThread == NULL)
	{
		delete pHandle;
		pHandle = NULL;
		return -1;
	}
	return 0;
}

gvoid GThread::Stop(gulong nMsecs)
{
	GThread_Handle *pHandle = (GThread_Handle*)m_pHandle;
	if (!pHandle)
	{
		return;
	}
	if (WAIT_OBJECT_0 != WaitForSingleObject(pHandle->m_hThread, nMsecs))
	{
		TerminateThread(pHandle->m_hThread, 0);
	}
	CloseHandle(pHandle->m_hThread);
	pHandle->m_hThread = NULL;
}

gvoid GThread::Sleep(gulong nSecs)
{
	::Sleep(1000 * nSecs);
}

gvoid GThread::MSleep(gulong nMsecs)
{
	::Sleep(nMsecs);
}

gvoid GThread::Join(GThread *pThread)
{
	GThread_Handle* pHandle = (GThread_Handle*)pThread->m_pHandle;
	if (pHandle)
	{
		WaitForSingleObject(pHandle->m_hThread, INFINITE);
		delete pHandle;
		pThread->m_pHandle = NULL;
	}
}

#endif // G_SYSTEM_WINDOWS