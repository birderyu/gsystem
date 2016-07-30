#include "CsAutoLock.h"
#include "CsAutoLock_Private.h"

CsAutoLock::CsAutoLock(CsMutex *pMutex)
:CsObject(new CsAutoLock_Private(this, pMutex))
{
	
}

CsAutoLock::~CsAutoLock()
{
	
}

void CsAutoLock::Unlock()
{
	CS_PRIVATE(CsAutoLock);
	pPrivate->Unlock();
}