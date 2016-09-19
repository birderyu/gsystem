#include "CsCriticalSection.h"
#include "CsCriticalSection_Private.h"

CsCriticalSection::CsCriticalSection()
:CsObject(new CsCriticalSection_Private(this))
{

}

cs_int CsCriticalSection::Lock()
{
	CS_PRIVATE(CsCriticalSection);
	return pPrivate->Lock();
}

cs_int CsCriticalSection::TryLock()
{
	CS_PRIVATE(CsCriticalSection);
	return pPrivate->TryLock();
}

cs_void CsCriticalSection::Unlock()
{
	CS_PRIVATE(CsCriticalSection);
	pPrivate->Unlock();
}