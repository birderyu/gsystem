#include "gmutex.h"

#ifdef G_SYSTEM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>

GMutex::GMutex()
: m_pHandle(GNULL)
{
	Initialize();
}

GMutex::~GMutex()
{
	Release();
}

gvoid GMutex::Lock()
{
	if (!m_pHandle)
	{
		return;
	}
	WaitForSingleObject((HANDLE)m_pHandle, INFINITE);
}

gbool GMutex::Trylock()
{
	if (!m_pHandle)
	{
		return false;
	}

	DWORD ret = WaitForSingleObject((HANDLE)m_pHandle, 1);
	if (ret == WAIT_OBJECT_0)
	{
		return true; // success
	}
	if (ret == WAIT_TIMEOUT)
	{
		return false; // timeout
	}
	return true;
}

gvoid GMutex::Unlock()
{
	if (!m_pHandle)
	{
		return;
	}
	ReleaseMutex((HANDLE)m_pHandle);
}

gbool GMutex::Initialize()
{
	m_pHandle = CreateMutex(GNULL, false, GNULL);
	if (m_pHandle == GNULL)
	{
		return false;
	}
	return true;
}

gvoid GMutex::Release()
{
	m_pHandle = GNULL;
}

#endif // G_SYSTEM_WINDOWS