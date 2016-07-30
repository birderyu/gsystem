#ifdef _WIN32
#include "CsSemaphore_Private.h"
#include "CsSemaphore.h"
#include <windows.h>

/// Win32ÐÅºÅÁ¿ÊµÀý¾ä±ú
struct CsSemaphoreHandle
{
	HANDLE m_hSemaphore;
};

CsSemaphore_Private::CsSemaphore_Private(CsSemaphore *pPublic, cs_int nInitialValue)
:CsObject_Private(pPublic), m_pHandle(NULL)
{
	Initialize(nInitialValue);
}

CsSemaphore_Private::~CsSemaphore_Private()
{
	if (m_pHandle)
	{
		CsSemaphoreHandle *pHandle = (CsSemaphoreHandle*)m_pHandle;
		delete pHandle;
		m_pHandle = NULL;
	}
}

cs_int CsSemaphore_Private::Wait()
{
	CsSemaphoreHandle *pHandle = (CsSemaphoreHandle*)m_pHandle;
	if (!pHandle) return -1;

	WaitForSingleObject(pHandle->m_hSemaphore, INFINITE);
	return 0;
}

cs_int CsSemaphore_Private::Wait(cs_ulong nMsecs)
{
	CsSemaphoreHandle *pHandle = (CsSemaphoreHandle*)m_pHandle;
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

void CsSemaphore_Private::Post()
{
	CsSemaphoreHandle *pHandle = (CsSemaphoreHandle*)m_pHandle;
	if (!pHandle) return;

	ReleaseSemaphore(pHandle->m_hSemaphore, 1, NULL);
}

cs_int CsSemaphore_Private::Initialize(cs_int nInitialValue)
{
	CsSemaphoreHandle *pHandle = (CsSemaphoreHandle*)m_pHandle;
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

#endif // _WIN32