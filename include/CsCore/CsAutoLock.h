#ifndef _CSCORE_CSAUTOLOCK_H_
#define _CSCORE_CSAUTOLOCK_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsMutex;

/// 自动锁
class CsCore_Export CsAutoLock :public CsObject
{
public:
	CsAutoLock(CsMutex *pMutex);
	~CsAutoLock();
	void Unlock();

public:
	enum { CLASSCODE = CORE_CLASSCODE_AUTO_LOCK, };
};

#endif // _CSCORE_CSAUTOLOCK_H_
