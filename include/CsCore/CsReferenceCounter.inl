#ifndef _CORE_REFERENCE_COUNTER_INLINE_
#define _CORE_REFERENCE_COUNTER_INLINE_

template <typename ClassT, typename LockT>
inline CsReferenceCounter<ClassT, LockT>::CsReferenceCounter(ClassT *ptr, cs_size_t count)
: m_pPointer(ptr), m_nCount(count)
{

}

template <typename ClassT, typename LockT>
inline CsReferenceCounter<ClassT, LockT>::~CsReferenceCounter()
{
	delete m_pPointer;
}

template <typename ClassT, typename LockT>
inline cs_size_t CsReferenceCounter<ClassT, LockT>::Add()
{
	return ++m_nCount;
}

template <typename ClassT, typename LockT>
inline cs_void CsReferenceCounter<ClassT, LockT>::Release()
{
	if (--m_nCount == 0)
		delete this;
}

template <typename ClassT, typename LockT>
inline cs_size_t CsReferenceCounter<ClassT, LockT>::Count() const
{
	return m_nCount.GetValue();
}

template <typename ClassT, typename LockT>
inline ClassT * CsReferenceCounter<ClassT, LockT>::Pointer()
{
	return m_pPointer;
}

template <typename ClassT, typename LockT>
inline const ClassT *CsReferenceCounter<ClassT, LockT>::Pointer() const
{
	return m_pPointer;
}

#endif // _CORE_REFERENCE_COUNTER_INLINE_