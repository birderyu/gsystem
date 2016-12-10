/// нчкЬ
#ifndef _CORE_VOID_LOCK_H_
#define _CORE_VOID_LOCK_H_

#include "CsLock.h"

class CS_API CsNullLock final 
	: public CsLock
{
public:
	cs_bool Lock();
	cs_bool Trylock();
	cs_void Unlock();
};

#endif // _CORE_VOID_LOCK_H_