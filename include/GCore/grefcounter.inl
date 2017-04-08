#ifndef _CORE_REFERENCE_COUNTER_INLINE_
#define _CORE_REFERENCE_COUNTER_INLINE_

#include "gatom.h"

namespace gsystem { // gsystem

template <typename ClassT>
GINLINE GRefCounter<ClassT>::GRefCounter(ClassT *ptr, gsize count)
: m_pPointer(ptr), m_nCount(count)
{

}

template <typename ClassT>
GINLINE GRefCounter<ClassT>::~GRefCounter()
{
	delete m_pPointer;
}

template <typename ClassT>
GINLINE gsize GRefCounter<ClassT>::Add()
{
	return GAtom::IncrementAndFetch(&m_nCount);
}

template <typename ClassT>
GINLINE gvoid GRefCounter<ClassT>::Release()
{
	if (GAtom::DecrementAndFetch(&m_nCount) == 0)
		delete this;
}

template <typename ClassT>
GINLINE gsize GRefCounter<ClassT>::Count() const
{
	return GAtom::GetValue(&m_nCount);
}

template <typename ClassT>
GINLINE ClassT * GRefCounter<ClassT>::Pointer()
{
	return m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT *GRefCounter<ClassT>::Pointer() const
{
	return m_pPointer;
}

} // namespace gsystem

#endif // _CORE_REFERENCE_COUNTER_INLINE_