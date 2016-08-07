#ifndef _CSCORE_CSAUTOLOCK_PRIVATE_H_
#define _CSCORE_CSAUTOLOCK_PRIVATE_H_

#include "CsObject_Private.h"

class CsAutoLock;
class CsMutex;

/// 自动锁
class CsAutoLock_Private :public CsObject_Private
{
public:
	CsAutoLock_Private(CsAutoLock *pPublic, CsMutex *pMutex);
	~CsAutoLock_Private();
	void Unlock();

private:
	CsMutex *m_pMutex;
	cs_bool m_bLocked;
};

#endif // _CSCORE_CSAUTOLOCK_PRIVATE_H_