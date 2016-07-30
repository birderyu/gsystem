#include "CsSemaphore.h"
#include "CsSemaphore_Private.h"

CsSemaphore::CsSemaphore(cs_int nInitialValue)
:CsObject(new CsSemaphore_Private(this, nInitialValue))
{
	
}

CsSemaphore::~CsSemaphore()
{
	
}

cs_int CsSemaphore::Wait()
{
	CS_PRIVATE(CsSemaphore);
	return pPrivate->Wait();
}

cs_int CsSemaphore::Wait(cs_ulong nMsecs)
{
	CS_PRIVATE(CsSemaphore);
	return pPrivate->Wait(nMsecs);
}

void CsSemaphore::Post()
{
	CS_PRIVATE(CsSemaphore);
	pPrivate->Post();
}