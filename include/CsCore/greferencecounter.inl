#ifndef _CORE_REFERENCE_COUNTER_INLINE_
#define _CORE_REFERENCE_COUNTER_INLINE_

template <typename ClassT, typename LockT>
inline GReferenceCounter<ClassT, LockT>::GReferenceCounter(ClassT *ptr, gsize count)
: m_pPointer(ptr), m_nCount(count)
{

}

template <typename ClassT, typename LockT>
inline GReferenceCounter<ClassT, LockT>::~GReferenceCounter()
{
	delete m_pPointer;
}

template <typename ClassT, typename LockT>
inline gsize GReferenceCounter<ClassT, LockT>::Add()
{
	return ++m_nCount;
}

template <typename ClassT, typename LockT>
inline gvoid GReferenceCounter<ClassT, LockT>::Release()
{
	if (--m_nCount == 0)
		delete this;
}

template <typename ClassT, typename LockT>
inline gsize GReferenceCounter<ClassT, LockT>::Count() const
{
	return m_nCount.GetValue();
}

template <typename ClassT, typename LockT>
inline ClassT * GReferenceCounter<ClassT, LockT>::Pointer()
{
	return m_pPointer;
}

template <typename ClassT, typename LockT>
inline const ClassT *GReferenceCounter<ClassT, LockT>::Pointer() const
{
	return m_pPointer;
}

#endif // _CORE_REFERENCE_COUNTER_INLINE_