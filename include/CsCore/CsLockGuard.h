#ifndef _CORE_LOCK_GUARD_H_
#define _CORE_LOCK_GUARD_H_

#include "CsGlobal.h"

template <typename LockT>
class CsLockGuard
{
public:
	CsLockGuard(LockT &tLock);
	~CsLockGuard();

private:
	/// 锁
	LockT &m_tLock;
};

#include "CsLockGuard.inl"

#endif // _CORE_LOCK_GUARD_H_
