#ifndef _CORE_LOCK_GUARD_INLINE_
#define _CORE_LOCK_GUARD_INLINE_

namespace gsystem { // gsystem

template <typename T>
GINLINE GLockGuard<T>::GLockGuard(T &lock)
: m_tLock(lock)
{
	m_tLock.Lock();
}

template <typename T>
GINLINE GLockGuard<T>::~GLockGuard()
{
	m_tLock.Unlock();
}

} // namespace gsystem

#endif // _CORE_LOCK_GUARD_INLINE_