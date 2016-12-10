// Ëø
#ifndef _CORE_LOCK_H_
#define _CORE_LOCK_H_

#include "CsGlobal.h"

class CS_API CsLock
{
public:
	virtual ~CsLock() = 0;
	virtual cs_bool Lock() = 0;
	virtual cs_bool Trylock() = 0;
	virtual cs_void Unlock() = 0;
};

#endif // _CORE_MUTEX_H_