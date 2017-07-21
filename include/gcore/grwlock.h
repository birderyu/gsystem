// Ëø
#ifndef _CORE_READ_WRITE_LOCK_H_
#define _CORE_READ_WRITE_LOCK_H_

#include "gtype.h"

namespace gsystem { // gsystem

class GAPI GRWLock
{
public:
	virtual ~GRWLock() = 0;
	virtual gvoid ReadLock() = 0;
	virtual gvoid ReadUnlock() = 0;
	virtual gvoid WriteLock() = 0;
	virtual gvoid WriteUnlock() = 0;
};

} // namespace gsystem

#endif // _CORE_READ_WRITE_LOCK_H_