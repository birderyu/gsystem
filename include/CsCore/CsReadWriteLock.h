// ¶ÁÐ´Ëø
#ifndef _CORE_READ_WRITE_LOCK_H_
#define _CORE_READ_WRITE_LOCK_H_

#include "CsGlobal.h"

class CS_API CsReadWriteLock
{
public:
	CsReadWriteLock();
	virtual ~CsReadWriteLock() = 0;

	// ¶ÁËø
	virtual cs_bool LockRead() = 0;
	virtual cs_bool TrylockRead() = 0;
	virtual cs_void UnlockRead() = 0;

	// Ð´Ëø
	virtual cs_bool LockWrite() = 0;
	virtual cs_bool TrylockWrite() = 0;
	virtual cs_void UnlockWrite() = 0;
};

#endif // _CORE_READ_WRITE_LOCK_H_