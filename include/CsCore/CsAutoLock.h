/// 自动锁
/// 根据传入的锁类型自动加锁

#ifndef _CORE_AUTOLOCK_H_
#define _CORE_AUTOLOCK_H_

#include "CsGlobal.h"

template <typename LockT>
class CsAutoLock
{
public:
	CsAutoLock(LockT &tLock);
	~CsAutoLock();

private:
	/// 锁
	LockT &m_tLock;
};

#include "CsAutoLock.inl"

#endif // _CORE_AUTOLOCK_H_
