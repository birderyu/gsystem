#include "gcriticalsection.h"

#ifdef G_SYSTEM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>

GCriticalSection::GCriticalSection()
{
	Initialize(false, 0);
}

GCriticalSection::GCriticalSection(gbool spin, gsize spin_count)
{
	Initialize(spin, spin_count);
}

GCriticalSection::~GCriticalSection()
{
	Release();
}

gvoid GCriticalSection::Lock()
{
	EnterCriticalSection((CRITICAL_SECTION*)m_pHandle);
}

gvoid GCriticalSection::Unlock()
{
	LeaveCriticalSection((CRITICAL_SECTION*)m_pHandle);
}

gvoid GCriticalSection::Initialize(gbool spin, gsize spin_count)
{
	if (spin)
	{
		InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION*)m_pHandle, spin_count);
	}
	else
	{
		InitializeCriticalSection((CRITICAL_SECTION*)m_pHandle);
	}
}

gvoid GCriticalSection::Release()
{
	DeleteCriticalSection((CRITICAL_SECTION*)m_pHandle);
}

#endif // G_SYSTEM_WINDOWS