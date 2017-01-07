#include "gcriticalsection.h"

#ifdef G_SYSTEM_WINDOWS
#include <windows.h>

/// Win32ÁÙ½çÇøÊµÀý¾ä±ú
struct GCriticalSection_Handle
{
	CRITICAL_SECTION m_tCriticalSection;
};

GCriticalSection::GCriticalSection()
:m_pHandle(NULL)
{
	Initialize();
}

GCriticalSection::~GCriticalSection()
{
	Release();
}

gbool GCriticalSection::Lock()
{
	GCriticalSection_Handle *pHandle = static_cast<GCriticalSection_Handle*>(m_pHandle);
	if (!pHandle) return false;

	
	return true;
}

gbool GCriticalSection::Trylock()
{
	return false;
}

gvoid GCriticalSection::Unlock()
{

}

gint GCriticalSection::Initialize()
{
	if (!m_pHandle)
	{
		return 0;
	}
	GCriticalSection_Handle *pHandle = new GCriticalSection_Handle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	InitializeCriticalSection(&pHandle->m_tCriticalSection);

	//ReleaseMutex(pHandle->m_hMutex);
	return 0;
}

gvoid GCriticalSection::Release()
{
	if (m_pHandle)
	{
		GCriticalSection_Handle *pHandle = static_cast<GCriticalSection_Handle*>(m_pHandle);
		delete pHandle;
		m_pHandle = NULL;
	}
}

#endif // G_SYSTEM_WINDOWS