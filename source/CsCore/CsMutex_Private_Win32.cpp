#ifdef _WIN32

#include "CsMutex_Private.h"
#include "CsMutex.h"
#include <windows.h>

/// Win32������ʵ�����
struct CsMutex_Handle
{
	HANDLE m_hMutex;
};

CsMutex_Private::CsMutex_Private()
:CsObject_Private(NULL), m_pHandle(NULL)
{
	Initialize();
}

CsMutex_Private::CsMutex_Private(CsMutex *pPublic)
:CsObject_Private(pPublic), m_pHandle(NULL)
{
	Initialize();
}

CsMutex_Private::~CsMutex_Private()
{
	Release();
}

cs_bool CsMutex_Private::Lock()
{
	CsMutex_Handle *pHandle = static_cast<CsMutex_Handle*>(m_pHandle);
	if (!pHandle) return false;

	WaitForSingleObject(pHandle->m_hMutex, INFINITE);
	return true;
}

cs_bool CsMutex_Private::TryLock()
{
	CsMutex_Handle *pHandle = static_cast<CsMutex_Handle*>(m_pHandle);
	if (!pHandle) return false;

	DWORD nRet = WaitForSingleObject(pHandle->m_hMutex, 1);
	if (nRet == WAIT_OBJECT_0)
	{
		return true; // success
	}
	if (nRet == WAIT_TIMEOUT)
	{
		return false; // timeout
	}
	return true;
}

cs_void CsMutex_Private::Unlock()
{
	CsMutex_Handle *pHandle = static_cast<CsMutex_Handle*>(m_pHandle);
	if (!pHandle) return;

	ReleaseMutex(pHandle->m_hMutex);
}

cs_bool CsMutex_Private::Initialize()
{
	if (!m_pHandle)
	{
		return true;
	}
	CsMutex_Handle *pHandle = new CsMutex_Handle;
	if (!pHandle) return false;
	m_pHandle = pHandle;

	pHandle->m_hMutex = CreateMutex(NULL, true, NULL);
	if (pHandle->m_hMutex == NULL)
	{
		delete pHandle;
		pHandle = NULL;
		return false;
	}

	ReleaseMutex(pHandle->m_hMutex);
	return true;
}

cs_void CsMutex_Private::Release()
{
	if (m_pHandle)
	{
		CsMutex_Handle *pHandle = static_cast<CsMutex_Handle*>(m_pHandle);
		delete pHandle;
		m_pHandle = NULL;
	}
}

#endif // _WIN32