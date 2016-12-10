#ifndef _CORE_AUTOLOCK_INLINE_
#define _CORE_AUTOLOCK_INLINE_

template <typename LockT>
inline CsAutoLock<LockT>::CsAutoLock(LockT &tLock)
: m_tLock(tLock)
{
	m_tLock.Lock();
}

template <typename LockT>
inline CsAutoLock<LockT>::~CsAutoLock()
{
	m_tLock.Unlock();
}

#endif // _CORE_AUTOLOCK_INLINE_