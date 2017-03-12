#ifndef _CORE_LOCK_GUARD_H_
#define _CORE_LOCK_GUARD_H_

#include "gglobal.h"

namespace gnova { // gnova

template <typename LockT>
class GLockGuard
{
public:
	GLockGuard(LockT &tLock);
	~GLockGuard();

private:
	/// 锁
	LockT &m_tLock;
};

} // namespace gnova

#include "glockguard.inl"

#endif // _CORE_LOCK_GUARD_H_
