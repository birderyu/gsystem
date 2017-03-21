// ��д��
#ifndef _CORE_READ_WRITE_LOCK_H_
#define _CORE_READ_WRITE_LOCK_H_

#include "gtype.h"

namespace gsystem { // gsystem

class GAPI GReadWriteLock
{
public:
	GReadWriteLock();
	virtual ~GReadWriteLock() = 0;

	// ����
	virtual gbool LockRead() = 0;
	virtual gbool TrylockRead() = 0;
	virtual gvoid UnlockRead() = 0;

	// д��
	virtual gbool LockWrite() = 0;
	virtual gbool TrylockWrite() = 0;
	virtual gvoid UnlockWrite() = 0;
};

} // namespace gsystem

#endif // _CORE_READ_WRITE_LOCK_H_