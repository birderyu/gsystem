#include "gsemaphore.h"
#include "gnew.h"

#ifdef G_SYSTEM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>

/// Win32ÐÅºÅÁ¿ÊµÀý¾ä±ú
struct GSemaphoreHandle
	: public GNewT<GSemaphoreHandle>
{
	HANDLE m_hSemaphore;
};

GSemaphore::GSemaphore(gint nInitialValue)
:m_pHandle(GNULL)
{
	Initialize(nInitialValue);
}

GSemaphore::~GSemaphore()
{
	if (m_pHandle)
	{
		GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
		delete pHandle;
		m_pHandle = GNULL;
	}
}

gbool GSemaphore::Wait()
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return false;

	WaitForSingleObject(pHandle->m_hSemaphore, INFINITE);
	return true;
}

gbool GSemaphore::Wait(gulong nMsecs)
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return false;

	DWORD nRet = WaitForSingleObject(pHandle->m_hSemaphore, nMsecs);
	if (nRet == WAIT_OBJECT_0)
	{
		return true; // success
	}
	if (nRet == WAIT_TIMEOUT)
	{
		return false; // timeout
	}
	return false;
}

void GSemaphore::Post()
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return;

	ReleaseSemaphore(pHandle->m_hSemaphore, 1, GNULL);
}

gint GSemaphore::Initialize(gint nInitialValue)
{
	GSemaphoreHandle *pHandle = (GSemaphoreHandle*)m_pHandle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	pHandle->m_hSemaphore = CreateSemaphore(GNULL, nInitialValue, 5000, GNULL);
	if (pHandle->m_hSemaphore == GNULL)
	{
		delete pHandle;
		m_pHandle = GNULL;
		return -1;
	}

	return 0;
}

#endif // G_SYSTEM_WINDOWS