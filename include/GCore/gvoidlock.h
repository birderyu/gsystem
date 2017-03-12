/// нчкЬ
#ifndef _CORE_VOID_LOCK_H_
#define _CORE_VOID_LOCK_H_

#include "glock.h"

namespace gnova { // gnova

class GAPI GVoidLock final 
	: public GLock
{
public:
	gvoid Lock();
	gvoid Unlock();
};

} // namespace gnova

#endif // _CORE_VOID_LOCK_H_