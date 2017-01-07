// Ëø
#ifndef _CORE_LOCK_H_
#define _CORE_LOCK_H_

#include "gglobal.h"

class GAPI GLock
{
public:
	virtual ~GLock() = 0;
	virtual gbool Lock() = 0;
	virtual gbool Trylock() = 0;
	virtual gvoid Unlock() = 0;
};

#endif // _CORE_MUTEX_H_