#ifndef _CORE_UNIQUE_POINTER_INLINE_
#define _CORE_UNIQUE_POINTER_INLINE_

template <typename ClassT>
GINLINE GUniquePointer<ClassT>::GUniquePointer(ClassT *ptr)
	: m_pPointer(ptr)
{

}

template <typename ClassT>
GINLINE GUniquePointer<ClassT>::GUniquePointer(GUniquePointer<ClassT> &&ptr)
	: m_pPointer(ptr.m_pPointer)
{
	ptr.m_pPointer = GNULL;
}

template <typename ClassT>
GINLINE GUniquePointer<ClassT>::~GUniquePointer()
{
	delete m_pPointer;
}

template <typename ClassT>
GINLINE gvoid GUniquePointer<ClassT>::Reset(ClassT *ptr)
{
	delete m_pPointer;
	m_pPointer = ptr;
}

template <typename ClassT>
GINLINE ClassT *GUniquePointer<ClassT>::Release()
{
	ClassT *ptr = m_pPointer;
	m_pPointer = GNULL;
	return ptr;
}

template <typename ClassT>
GINLINE GUniquePointer<ClassT>::operator gbool() const
{
	return m_pPointer != GNULL;
}

template <typename ClassT>
GINLINE GUniquePointer<ClassT> &GUniquePointer<ClassT>::operator=(GUniquePointer<ClassT> &&ptr)
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
GINLINE ClassT &GUniquePointer<ClassT>::operator*()
{
	return *m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT &GUniquePointer<ClassT>::operator*() const
{
	return *m_pPointer;
}

template <typename ClassT>
GINLINE ClassT *GUniquePointer<ClassT>::operator->()
{
	return m_pPointer;
}

template <typename ClassT>
GINLINE const ClassT *GUniquePointer<ClassT>::operator->() const
{
	return m_pPointer;
}

template<typename ClassT, typename... TS>
GINLINE GUniquePointer<ClassT> GMakeUnique(TS&&... args)
{	// make a unique_ptr
	return GUniquePointer<ClassT>(new ClassT(GForward<TS>(args)...));
}

#endif // _CORE_UNIQUE_POINTER_INLINE_