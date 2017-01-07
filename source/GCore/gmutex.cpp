#include "gmutex.h"

#ifdef G_SYSTEM_WINDOWS

#include <windows.h>

/// Win32»¥³âÁ¿ÊµÀý¾ä±ú
struct GMutex_Handle
{
	HANDLE m_hMutex;
};

GMutex::GMutex()
: m_pHandle(NULL)
{
	Initialize();
}

GMutex::~GMutex()
{
	Release();
}

gbool GMutex::Lock()
{
	GMutex_Handle *pHandle = static_cast<GMutex_Handle*>(m_pHandle);
	if (!pHandle) return false;

	WaitForSingleObject(pHandle->m_hMutex, INFINITE);
	return true;
}

gbool GMutex::Trylock()
{
	GMutex_Handle *pHandle = static_cast<GMutex_Handle*>(m_pHandle);
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

gvoid GMutex::Unlock()
{
	GMutex_Handle *pHandle = static_cast<GMutex_Handle*>(m_pHandle);
	if (!pHandle) return;

	ReleaseMutex(pHandle->m_hMutex);
}

gbool GMutex::Initialize()
{
	if (!m_pHandle)
	{
		return true;
	}
	GMutex_Handle *pHandle = new GMutex_Handle;
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

gvoid GMutex::Release()
{
	if (m_pHandle)
	{
		GMutex_Handle *pHandle = static_cast<GMutex_Handle*>(m_pHandle);
		delete pHandle;
		m_pHandle = NULL;
	}
}

#endif // G_SYSTEM_WINDOWS