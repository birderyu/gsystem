#include "gsemaphore.h"

#ifdef G_SYSTEM_WINDOWS

#include <windows.h>

/// Win32ÐÅºÅÁ¿ÊµÀý¾ä±ú
struct GSemaphoreHandle
{
	HANDLE m_hSemaphore;
};

GSemaphore::GSemaphore(gint nInitialValue)
:m_pHandle(NULL)
{
	Initialize(nInitialValue);
}

GSemaphore::~GSemaphore()
{
	if (m_pHandle)
	{
		GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
		delete pHandle;
		m_pHandle = NULL;
	}
}

gint GSemaphore::Wait()
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return -1;

	WaitForSingleObject(pHandle->m_hSemaphore, INFINITE);
	return 0;
}

gint GSemaphore::Wait(gulong nMsecs)
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return -1;

	DWORD nRet = WaitForSingleObject(pHandle->m_hSemaphore, nMsecs);
	if (nRet == WAIT_OBJECT_0)
	{
		return 0; // success
	}
	if (nRet == WAIT_TIMEOUT)
	{
		return -1; // timeout
	}
	return -1;
}

void GSemaphore::Post()
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return;

	ReleaseSemaphore(pHandle->m_hSemaphore, 1, NULL);
}

gint GSemaphore::Initialize(gint nInitialValue)
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	pHandle->m_hSemaphore = CreateSemaphore(NULL, nInitialValue, 5000, NULL);
	if (pHandle->m_hSemaphore == NULL)
	{
		delete pHandle;
		m_pHandle = NULL;
		return -1;
	}

	return 0;
}

#endif // G_SYSTEM_WINDOWS