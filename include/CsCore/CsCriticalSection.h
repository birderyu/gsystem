/// ÁÙ½çÇø
#ifndef _CORE_CRITICAL_SECTION_H_
#define _CORE_CRITICAL_SECTION_H_

#include "CsObject.h"

class CS_CORE_EXPORT CsCriticalSection :public CsObject
{
public:
	CsCriticalSection();
	cs_int Lock();
	cs_int TryLock();
	cs_void Unlock();

public:
	enum { CLASSCODE = CORE_CLASSCODE_CRITICAL_SECTION, };
};

#endif // _CORE_CRITICAL_SECTION_H_