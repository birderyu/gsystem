/// нчкЬ
#ifndef _CORE_VOID_LOCK_H_
#define _CORE_VOID_LOCK_H_

#include "glock.h"

class GAPI GVoidLock final 
	: public GLock
{
public:
	gvoid Lock();
	gvoid Unlock();
};

#endif // _CORE_VOID_LOCK_H_