#include "CsMutex.h"
#include "CsMutex_Private.h"

CsMutex::CsMutex()
:CsObject(new CsMutex_Private(this))
{
	
}

CsMutex::~CsMutex()
{
	
}

cs_int CsMutex::Lock()
{
	CS_PRIVATE(CsMutex);
	return pPrivate->Lock();
}

cs_int CsMutex::TryLock()
{
	CS_PRIVATE(CsMutex);
	return pPrivate->TryLock();
}

void CsMutex::Unlock()
{
	CS_PRIVATE(CsMutex);
	pPrivate->Unlock();
}