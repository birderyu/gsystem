#ifndef _CORE_LOCK_GUARD_H_
#define _CORE_LOCK_GUARD_H_

#include "gtype.h"

namespace gsystem { // gsystem

template <typename T>
class GLockGuard
{
public:
	GLockGuard(T &lock);
	~GLockGuard();

private:
	/// 锁
	T &m_tLock;
};

} // namespace gsystem

#include "inline/glockguard.inl"

#endif // _CORE_LOCK_GUARD_H_
