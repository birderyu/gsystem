#ifndef _CORE_ATOMIC_INLINE_
#define _CORE_ATOMIC_INLINE_

template <typename ElemT, typename LockT>
inline GAtomic<ElemT, LockT>::GAtomic()
#ifdef G_USE_STD_ATOMIC
#else
: m_tAtomic_Ex(m_tLock)
#endif
{

}

template <typename ElemT, typename LockT>
inline GAtomic<ElemT, LockT>::GAtomic(typename GAtomic<ElemT, LockT>::ValueType val)
#ifdef G_USE_STD_ATOMIC
: m_tValue(val)
#else
: m_tAtomic_Ex(m_tLock, val)
#endif
{

}

template <typename ElemT, typename LockT>
inline GAtomic<ElemT, LockT>::GAtomic(const GAtomic<ElemT, LockT> &val)
#ifdef G_USE_STD_ATOMIC
: m_tValue(val.m_tValue)
#else
: m_tAtomic_Ex(m_tLock, val.GetValue())
#endif
{

}

template <typename ElemT, typename LockT>
inline GAtomic<ElemT, LockT> &GAtomic<ElemT, LockT>::operator=(typename GAtomic<ElemT, LockT>::ValueType val)
{
#ifdef G_USE_STD_ATOMIC
	m_tValue = val;
	return *this;
#else
	m_tAtomic_Ex = val;
	return *this;
#endif
}

template <typename ElemT, typename LockT>
inline GAtomic<ElemT, LockT> &GAtomic<ElemT, LockT>::operator=(const GAtomic<ElemT, LockT> &val)
{
#ifdef G_USE_STD_ATOMIC
	m_tValue = val.GetValue();
	return *this;
#else
	m_tAtomic_Ex = val.m_pPrivate;
	return *this;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator++()
{
#ifdef G_USE_STD_ATOMIC
	return ++m_tValue;
#else
	return ++m_tAtomic_Ex;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator++(gint)
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue++;
#else
	return m_tAtomic_Ex++;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator+=(typename GAtomic<ElemT, LockT>::ValueType val)
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue += val;
#else
	return m_tAtomic_Ex += val;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator--()
{
#ifdef G_USE_STD_ATOMIC
	return --m_tValue;
#else
	return --m_tAtomic_Ex;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator--(gint)
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue--;
#else
	return m_tAtomic_Ex--;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::operator-=(typename GAtomic<ElemT, LockT>::ValueType val)
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue -= val;
#else
	return m_tAtomic_Ex -= val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator==(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue == val;
#else
	return m_tAtomic_Ex == val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator!=(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue != val;
#else
	return m_tAtomic_Ex != val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator>=(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue >= val;
#else
	return m_tAtomic_Ex >= val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator>(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue > val;
#else
	return m_tAtomic_Ex > val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator<=(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue <= val;
#else
	return m_tAtomic_Ex <= val;
#endif
}

template <typename ElemT, typename LockT>
inline gbool GAtomic<ElemT, LockT>::operator<(typename GAtomic<ElemT, LockT>::ValueType val) const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue < val;
#else
	return m_tAtomic_Ex < val;
#endif
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic<ElemT, LockT>::GetValue() const
{
#ifdef G_USE_STD_ATOMIC
	return m_tValue.load();
#else
	return m_tAtomic_Ex.GetValue();
#endif
}

template <typename ElemT, typename LockT>
inline gvoid GAtomic<ElemT, LockT>::SetValue(typename GAtomic<ElemT, LockT>::ValueType val)
{
#ifdef G_USE_STD_ATOMIC
	m_tValue.store(val);
#else
	m_tAtomic_Ex.SetValue(val);
#endif
}

#ifndef G_USE_STD_ATOMIC
template <typename ElemT, typename LockT>
inline LockT &GAtomic<ElemT, LockT>::GetLock()
{
	return m_tAtomic_Ex.GetLock();
}
#endif

template <typename ElemT, typename LockT>
inline GAtomic_Ex<ElemT, LockT>::GAtomic_Ex(LockT &lock)
: m_rLock(lock), m_tValue()
{

}

template <typename ElemT, typename LockT>
inline GAtomic_Ex<ElemT, LockT>::GAtomic_Ex(LockT &lock, typename GAtomic_Ex<ElemT, LockT>::ValueType val)
: m_rLock(lock), m_tValue(val)
{

}

template <typename ElemT, typename LockT>
inline GAtomic_Ex<ElemT, LockT>::GAtomic_Ex(const GAtomic_Ex<ElemT, LockT>& val)
: m_rLock(val.GetLock()), m_tValue(val.GetValue())
{

}

template <typename ElemT, typename LockT>
inline GAtomic_Ex<ElemT, LockT> &GAtomic_Ex<ElemT, LockT>::operator=(typename GAtomic_Ex<ElemT, LockT>::ValueType val)
{
	GLockGuard<LockT> tLock(m_rLock);
	m_tValue = val;
	return *this;
}

template <typename ElemT, typename LockT>
inline GAtomic_Ex<ElemT, LockT> &GAtomic_Ex<ElemT, LockT>::operator=(const GAtomic_Ex<ElemT, LockT> &val)
{
	GAtomic_Ex<ElemT, LockT> tmp(val);

	GLockGuard<LockT> tLock(m_rLock);
	std::swap(m_tValue, tmp.m_tValue);

	return *this;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator++()
{
	GLockGuard<LockT> tLock(m_rLock);
	return ++m_tValue;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator++(gint)
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue++;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator+=(typename GAtomic_Ex<ElemT, LockT>::ValueType val)
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue += val;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator--()
{
	GLockGuard<LockT> tLock(m_rLock);
	return --m_tValue;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator--(gint)
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue--;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::operator-=(typename GAtomic_Ex<ElemT, LockT>::ValueType val)
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue -= val;
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator==(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue == val;
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator!=(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	// GLockGuard<LockT> tLock(m_rLock);
	return !(*this == val);
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator>=(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue >= val;
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator>(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue > val;
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator<=(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue <= val;
}

template <typename ElemT, typename LockT>
inline gbool GAtomic_Ex<ElemT, LockT>::operator<(typename GAtomic_Ex<ElemT, LockT>::ValueType val) const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue < val;
}

template <typename ElemT, typename LockT>
inline ElemT GAtomic_Ex<ElemT, LockT>::GetValue() const
{
	GLockGuard<LockT> tLock(m_rLock);
	return m_tValue;
}

template <typename ElemT, typename LockT>
inline gvoid GAtomic_Ex<ElemT, LockT>::SetValue(typename GAtomic_Ex<ElemT, LockT>::ValueType val)
{
	GLockGuard<LockT> tLock(m_rLock);
	m_tValue = val;
}

template <typename ElemT, typename LockT>
inline LockT &GAtomic_Ex<ElemT, LockT>::GetLock()
{
	return m_rLock;
}

#endif // _CORE_ATOMIC_INLINE_