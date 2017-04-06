// ¶ÁÐ´Ëø
#ifndef _CORE_READ_WRITE_LOCK_H_
#define _CORE_READ_WRITE_LOCK_H_

#include "GCore/gtype.h"

namespace gsystem { // gsystem

class GAPI GRWLock
{
public:
	GRWLock();
	virtual ~GRWLock() = 0;

	// ¶ÁËø
	virtual gbool LockRead() = 0;
	virtual gbool TrylockRead() = 0;
	virtual gvoid UnlockRead() = 0;

	// Ð´Ëø
	virtual gbool LockWrite() = 0;
	virtual gbool TrylockWrite() = 0;
	virtual gvoid UnlockWrite() = 0;
};

} // namespace gsystem

#endif // _CORE_READ_WRITE_LOCK_H_