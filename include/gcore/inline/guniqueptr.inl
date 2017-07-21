#ifndef _CORE_UNIQUE_POINTER_INLINE_
#define _CORE_UNIQUE_POINTER_INLINE_

namespace gsystem { // gsystem

template <typename ClassT>
GINLINE GUniquePtr<ClassT>::GUniquePtr(ClassT *ptr)
	: m_pPointer(ptr)
{

}

template <typename ClassT>
GINLINE GUniquePtr<ClassT>::GUniquePtr(GUniquePtr<ClassT> &&ptr)
	: m_pPointer(ptr.m_pPointer)
{
	ptr.m_pPointer = GNULL;
}

template <typename ClassT>
GINLINE GUniquePtr<ClassT>::~GUniquePtr()
{
	delete m_pPointer;
}

template <typename ClassT>
GINLINE gvoid GUniquePtr<ClassT>::Reset(ClassT *ptr)
{
	delete m_pPointer;
	m_pPointer = ptr;
}

template <typename ClassT>
GINLINE ClassT *GUniquePtr<ClassT>::Release()
{
	ClassT *ptr = m_pPointer;
	m_pPointer = GNULL;
	return ptr;
}

template <typename ClassT>
GINLINE GUniquePtr<ClassT>::operator gbool() const
{
	return m_pPointer != GNULL;
}

template <typename ClassT>
GINLINE GUniquePtr<ClassT> &GUniquePtr<ClassT>::operator=(GUniquePtr<ClassT> &&ptr)
{
	if (this == &ptr)
	{
		return *this;
	}
	delete m_pPointer;
	m_pPointer = ptr.m_pPointer;
	ptr.m_pPointer = GNULL;
}

template <typename ClassT>
GINLINE ClassT &GUniquePtr<ClassT>::operator*()
{
	return *m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT &GUniquePtr<ClassT>::operator*() const
{
	return *m_pPointer;
}

template <typename ClassT>
GINLINE ClassT *GUniquePtr<ClassT>::operator->()
{
	return m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT *GUniquePtr<ClassT>::operator->() const
{
	return m_pPointer;
}

template<typename ClassT, typename... TS>
GINLINE GUniquePtr<ClassT> GMakeUnique(TS&&... args)
{	// make a unique_ptr
	return GUniquePtr<ClassT>(new ClassT(GForward<TS>(args)...));
}

} // namespace gsystem

#endif // _CORE_UNIQUE_POINTER_INLINE_