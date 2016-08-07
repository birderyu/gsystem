#ifndef _CSCORE_CSMUTEX_PRIVATE_H_
#define _CSCORE_CSMUTEX_PRIVATE_H_

#include "CsObject_Private.h"

class CsMutex;

class CsMutex_Private :public CsObject_Private
{
public:
	CsMutex_Private(CsMutex *pPublic);
	~CsMutex_Private();
	cs_int Lock();
	cs_int TryLock();
	void Unlock();

private:
	cs_int Initialize();
	void *m_pHandle;
};

#endif // _CSCORE_CSMUTEX_PRIVATE_H_