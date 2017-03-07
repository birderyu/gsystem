#ifndef _CORE_LOCK_GUARD_INLINE_
#define _CORE_LOCK_GUARD_INLINE_

template <typename LockT>
GINLINE GLockGuard<LockT>::GLockGuard(LockT &tLock)
: m_tLock(tLock)
{
	m_tLock.Lock();
}

template <typename LockT>
GINLINE GLockGuard<LockT>::~GLockGuard()
{
	m_tLock.Unlock();
}

#endif // _CORE_LOCK_GUARD_INLINE_