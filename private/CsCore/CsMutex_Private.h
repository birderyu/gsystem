#ifndef _CORE_MUTEX_PRIVATE_H_
#define _CORE_MUTEX_PRIVATE_H_

#include "CsObject_Private.h"

class CsMutex;

class CsMutex_Private :public CsObject_Private
{
public:
	CsMutex_Private();
	CsMutex_Private(CsMutex *pPublic);
	~CsMutex_Private();
	cs_bool Lock();
	cs_bool TryLock();
	cs_void Unlock();

private:
	cs_bool Initialize();
	cs_void Release();
	cs_pointer m_pHandle;
};

#endif // _CORE_MUTEX_PRIVATE_H_