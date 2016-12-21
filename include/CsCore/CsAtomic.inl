#ifndef _CORE_ATOMIC_INLINE_
#define _CORE_ATOMIC_INLINE_

template <typename ElemT, typename LockT>
inline CsAtomic<ElemT, LockT>::CsAtomic()
#ifdef CS_USE_STD_ATOMIC
#else
: m_tAtomic_Ex(m_tLock)
#endif
{

}

template <typename ElemT, typename LockT>
inline CsAtomic<ElemT, LockT>::CsAtomic(typename CsAtomic<ElemT, LockT>::ValueType val)
#ifdef CS_USE_STD_ATOMIC
: m_tValue(val)
#else
: m_tAtomic_Ex(m_tLock, val)
#endif
{

}

template <typename ElemT, typename LockT>
inline CsAtomic<ElemT, LockT>::CsAtomic(const CsAtomic<ElemT, LockT> &val)
#ifdef CS_USE_STD_ATOMIC
: m_tValue(val.m_tValue)
#else
: m_tAtomic_Ex(m_tLock, val.GetValue())
#endif
{

}

template <typename ElemT, typename LockT>
inline CsAtomic<ElemT, LockT> &CsAtomic<ElemT, LockT>::operator=(typename CsAtomic<ElemT, LockT>::ValueType val)
{
#ifdef CS_USE_STD_ATOMIC
	m_tValue = val;
	return *this;
#else
	m_tAtomic_Ex = val;
	return *this;
#endif
}

template <typename ElemT, typename LockT>
inline CsAtomic<ElemT, LockT> &CsAtomic<ElemT, LockT>::operator=(const CsAtomic<ElemT, LockT> &val)
{
#ifdef CS_USE_STD_ATOMIC
	m_tValue = val.GetValue();
	return *this;
#else
	m_tAtomic_Ex = val.m_pPrivate;
	return *this;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator++()
{
#ifdef CS_USE_STD_ATOMIC
	return ++m_tValue;
#else
	return ++m_tAtomic_Ex;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator++(cs_int)
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue++;
#else
	return m_tAtomic_Ex++;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator+=(typename CsAtomic<ElemT, LockT>::ValueType val)
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue += val;
#else
	return m_tAtomic_Ex += val;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator--()
{
#ifdef CS_USE_STD_ATOMIC
	return --m_tValue;
#else
	return --m_tAtomic_Ex;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator--(cs_int)
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue--;
#else
	return m_tAtomic_Ex--;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::operator-=(typename CsAtomic<ElemT, LockT>::ValueType val)
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue -= val;
#else
	return m_tAtomic_Ex -= val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator==(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue == val;
#else
	return m_tAtomic_Ex == val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator!=(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue != val;
#else
	return m_tAtomic_Ex != val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator>=(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue >= val;
#else
	return m_tAtomic_Ex >= val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator>(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue > val;
#else
	return m_tAtomic_Ex > val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator<=(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue <= val;
#else
	return m_tAtomic_Ex <= val;
#endif
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic<ElemT, LockT>::operator<(typename CsAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue < val;
#else
	return m_tAtomic_Ex < val;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic<ElemT, LockT>::GetValue() const
{
#ifdef CS_USE_STD_ATOMIC
	return m_tValue.load();
#else
	return m_tAtomic_Ex.GetValue();
#endif
}

template <typename ElemT, typename LockT>
inline cs_void CsAtomic<ElemT, LockT>::SetValue(typename CsAtomic<ElemT, LockT>::ValueType val)
{
#ifdef CS_USE_STD_ATOMIC
	m_tValue.store(val);
#else
	m_tAtomic_Ex.SetValue(val);
#endif
}

#ifndef CS_USE_STD_ATOMIC
template <typename ElemT, typename LockT>
inline LockT &CsAtomic<ElemT, LockT>::GetLock()
{
	return m_tAtomic_Ex.GetLock();
}
#endif

template <typename ElemT, typename LockT>
inline CsAtomic_Ex<ElemT, LockT>::CsAtomic_Ex(LockT &lock)
: m_rLock(lock), m_tValue()
{

}

template <typename ElemT, typename LockT>
inline CsAtomic_Ex<ElemT, LockT>::CsAtomic_Ex(LockT &lock, typename CsAtomic_Ex<ElemT, LockT>::ValueType val)
: m_rLock(lock), m_tValue(val)
{

}

template <typename ElemT, typename LockT>
inline CsAtomic_Ex<ElemT, LockT>::CsAtomic_Ex(const CsAtomic_Ex<ElemT, LockT>& val)
: m_rLock(val.GetLock()), m_tValue(val.GetValue())
{

}

template <typename ElemT, typename LockT>
inline CsAtomic_Ex<ElemT, LockT> &CsAtomic_Ex<ElemT, LockT>::operator=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val)
{
	CsLockGuard<LockT> tLock(m_rLock);
	m_tValue = val;
	return *this;
}

template <typename ElemT, typename LockT>
inline CsAtomic_Ex<ElemT, LockT> &CsAtomic_Ex<ElemT, LockT>::operator=(const CsAtomic_Ex<ElemT, LockT> &val)
{
	CsAtomic_Ex<ElemT, LockT> tmp(val);

	CsLockGuard<LockT> tLock(m_rLock);
	std::swap(m_tValue, tmp.m_tValue);

	return *this;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator++()
{
	CsLockGuard<LockT> tLock(m_rLock);
	return ++m_tValue;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator++(cs_int)
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue++;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator+=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val)
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue += val;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator--()
{
	CsLockGuard<LockT> tLock(m_rLock);
	return --m_tValue;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator--(cs_int)
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue--;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::operator-=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val)
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue -= val;
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator==(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue == val;
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator!=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	//CsAutoLock<LockT> tLock(m_tLock);
	return !(*this == val);
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator>=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue >= val;
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator>(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue > val;
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator<=(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue <= val;
}

template <typename ElemT, typename LockT>
inline cs_bool CsAtomic_Ex<ElemT, LockT>::operator<(typename CsAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue < val;
}

template <typename ElemT, typename LockT>
inline ElemT CsAtomic_Ex<ElemT, LockT>::GetValue() const
{
	CsLockGuard<LockT> tLock(m_rLock);
	return m_tValue;
}

template <typename ElemT, typename LockT>
inline cs_void CsAtomic_Ex<ElemT, LockT>::SetValue(typename CsAtomic_Ex<ElemT, LockT>::ValueType val)
{
	CsLockGuard<LockT> tLock(m_rLock);
	m_tValue = val;
}

template <typename ElemT, typename LockT>
inline LockT &CsAtomic_Ex<ElemT, LockT>::GetLock()
{
	return m_rLock;
}

#endif // _CORE_ATOMIC_INLINE_