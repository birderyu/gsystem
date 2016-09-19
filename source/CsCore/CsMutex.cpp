#include "CsMutex.h"
#include "CsMutex_Private.h"

CsMutex::CsMutex()
:CsObject(new CsMutex_Private(this))
{
	
}

cs_bool CsMutex::Lock()
{
	CS_PRIVATE(CsMutex);
	return pPrivate->Lock();
}

cs_bool CsMutex::TryLock()
{
	CS_PRIVATE(CsMutex);
	return pPrivate->TryLock();
}

cs_void CsMutex::Unlock()
{
	CS_PRIVATE(CsMutex);
	pPrivate->Unlock();
}