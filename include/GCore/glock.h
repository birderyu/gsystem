// Ëø
#ifndef _CORE_LOCK_H_
#define _CORE_LOCK_H_

#include "gtype.h"

namespace gsystem { // gsystem

class GAPI GLock
{
public:
	virtual ~GLock() = 0;
	virtual gvoid Lock() = 0;
	virtual gvoid Unlock() = 0;
};

} // namespace gsystem

#endif // _CORE_MUTEX_H_