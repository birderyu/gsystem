#ifdef _WIN32

#include "CsCriticalSection_Private.h"
#include "CsCriticalSection.h"
#include <windows.h>

/// Win32ÁÙ½çÇøÊµÀý¾ä±ú
struct CsCriticalSection_Handle
{
	CRITICAL_SECTION m_tCriticalSection;
};

CsCriticalSection_Private::CsCriticalSection_Private(CsCriticalSection *pPublic)
:CsObject_Private(pPublic), m_pHandle(NULL)
{
	Initialize();
}

CsCriticalSection_Private::~CsCriticalSection_Private()
{
	Release();
}

cs_int CsCriticalSection_Private::Lock()
{
	CsCriticalSection_Handle *pHandle = static_cast<CsCriticalSection_Handle*>(m_pHandle);
	if (!pHandle) return -1;

	
	return 0;
}

cs_int CsCriticalSection_Private::TryLock()
{
	return -1;
}

cs_void CsCriticalSection_Private::Unlock()
{

}

cs_int CsCriticalSection_Private::Initialize()
{
	if (!m_pHandle)
	{
		return 0;
	}
	CsCriticalSection_Handle *pHandle = new CsCriticalSection_Handle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	InitializeCriticalSection(&pHandle->m_tCriticalSection);

	//ReleaseMutex(pHandle->m_hMutex);
	return 0;
}

cs_void CsCriticalSection_Private::Release()
{
	if (m_pHandle)
	{
		CsCriticalSection_Handle *pHandle = static_cast<CsCriticalSection_Handle*>(m_pHandle);
		delete pHandle;
		m_pHandle = NULL;
	}
}

#endif // _WIN32