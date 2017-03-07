#ifndef _CORE_REFERENCE_COUNTER_INLINE_
#define _CORE_REFERENCE_COUNTER_INLINE_

template <typename ClassT>
GINLINE GReferenceCounter<ClassT>::GReferenceCounter(ClassT *ptr, gsize count)
: m_pPointer(ptr), m_nCount(count)
{

}

template <typename ClassT>
GINLINE GReferenceCounter<ClassT>::~GReferenceCounter()
{
	delete m_pPointer;
}

template <typename ClassT>
GINLINE gsize GReferenceCounter<ClassT>::Add()
{
	return GAtom::IncrementAndFetch(&m_nCount);
}

template <typename ClassT>
GINLINE gvoid GReferenceCounter<ClassT>::Release()
{
	if (GAtom::DecrementAndFetch(&m_nCount) == 0)
		delete this;
}

template <typename ClassT>
GINLINE gsize GReferenceCounter<ClassT>::Count() const
{
	return GAtom::GetValue(&m_nCount);
}

template <typename ClassT>
GINLINE ClassT * GReferenceCounter<ClassT>::Pointer()
{
	return m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT *GReferenceCounter<ClassT>::Pointer() const
{
	return m_pPointer;
}

#endif // _CORE_REFERENCE_COUNTER_INLINE_