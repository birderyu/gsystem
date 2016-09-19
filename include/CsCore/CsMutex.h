/// 互斥量
#ifndef _CORE_MUTEX_H_
#define _CORE_MUTEX_H_

#include "CsObject.h"

class CS_CORE_EXPORT CsMutex :public CsObject
{
public:
	CsMutex();
	cs_bool Lock();
	cs_bool TryLock();
	cs_void Unlock();

public:
	enum { CLASSCODE = CORE_CLASSCODE_MUTEX, };
};

#endif // _CORE_MUTEX_H_
