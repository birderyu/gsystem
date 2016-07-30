#ifdef _WIN32
#include "CsMutex_Private.h"
#include "CsMutex.h"
#include <windows.h>

/// Win32»¥³âËøÊµÀý¾ä±ú
struct CsMutex_Handle
{
	HANDLE m_hMutex;
};

CsMutex_Private::CsMutex_Private(CsMutex *pPublic)
:CsObject_Private(pPublic), m_pHandle(NULL)
{
	Initialize();
}

CsMutex_Private::~CsMutex_Private()
{
	if (m_pHandle)
	{
		CsMutex_Handle *pHandle = (CsMutex_Handle*)m_pHandle;
		delete pHandle;
		m_pHandle = NULL;
	}
}

cs_int CsMutex_Private::Lock()
{
	CsMutex_Handle *pHandle = (CsMutex_Handle*)m_pHandle;
	if (!pHandle) return -1;

	WaitForSingleObject(pHandle->m_hMutex, INFINITE);
	return 0;
}

cs_int CsMutex_Private::TryLock()
{
	CsMutex_Handle *pHandle = (CsMutex_Handle*)m_pHandle;
	if (!pHandle) return -1;

	DWORD nRet = WaitForSingleObject(pHandle->m_hMutex, 1);
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

void CsMutex_Private::Unlock()
{
	CsMutex_Handle *pHandle_Priv = (CsMutex_Handle*)m_pHandle;
	if (!pHandle_Priv) return;

	ReleaseMutex(pHandle_Priv->m_hMutex);
}

cs_int CsMutex_Private::Initialize()
{
	CsMutex_Handle *pHandle = new CsMutex_Handle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	pHandle->m_hMutex = CreateMutex(NULL, true, NULL);
	if (pHandle->m_hMutex == NULL)
	{
		delete pHandle;
		pHandle = NULL;
		return -1;
	}

	ReleaseMutex(pHandle->m_hMutex);
	return 0;
}

#endif // _WIN32