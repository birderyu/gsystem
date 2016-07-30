#ifndef _CSCORE_CSMUTEX_H_
#define _CSCORE_CSMUTEX_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

/// »¥³âËø
class CsCore_Export CsMutex :public CsObject
{
public:
	CsMutex();
	~CsMutex();
	cs_int Lock();
	cs_int TryLock();
	void Unlock();

public:
	enum { CLASSCODE = CORE_CLASSCODE_MUTEX, };
};

#endif // _CSCORE_CSMUTEX_H_
