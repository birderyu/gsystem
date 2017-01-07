#ifndef _CORE_SHARED_POINTER_INLINE_
#define _CORE_SHARED_POINTER_INLINE_

template <typename ClassT, typename LockT>
inline GSharedPointer<ClassT, LockT>::GSharedPointer(ClassT *ptr, gsize count)
: m_pRefCounter(new GReferenceCounter<ClassT, LockT>(ptr, count))
{

}

template <typename ClassT, typename LockT>
inline GSharedPointer<ClassT, LockT>::GSharedPointer(const GSharedPointer<ClassT, LockT> &ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	m_pRefCounter->Add();
}

template <typename ClassT, typename LockT>
inline GSharedPointer<ClassT, LockT>::~GSharedPointer()
{
	m_pRefCounter->Release();
}

template <typename ClassT, typename LockT>
inline gvoid GSharedPointer<ClassT, LockT>::Reset(ClassT *ptr)
{
	m_pRefCounter->Release();
	m_pRefCounter = new GReferenceCounter<ClassT, LockT>(ptr);
}

template <typename ClassT, typename LockT>
inline gbool GSharedPointer<ClassT, LockT>::IsNull() const
{
	return m_pRefCounter->Pointer() == NULL;
}

template <typename ClassT, typename LockT>
inline gbool GSharedPointer<ClassT, LockT>::IsShared() const
{
	return m_pRefCounter->Count() > 1;
}

template <typename ClassT, typename LockT>
inline gsize GSharedPointer<ClassT, LockT>::Add()
{
	return m_pRefCounter->Add();
}

template <typename ClassT, typename LockT>
inline gvoid GSharedPointer<ClassT, LockT>::Release()
{
	m_pRefCounter->Release();
}

template <typename ClassT, typename LockT>
inline gsize GSharedPointer<ClassT, LockT>::Count() const
{
	return m_pRefCounter->Count();
}

template <typename ClassT, typename LockT>
inline GSharedPointer<ClassT, LockT> &GSharedPointer<ClassT, LockT>::operator=(const GSharedPointer<ClassT, LockT> &ptr)
{
	ptr.m_pRefCounter->Add();
	m_pRefCounter->Release();
	m_pRefCounter = ptr.m_pRefCounter;
	return *this;
}

template <typename ClassT, typename LockT>
inline ClassT &GSharedPointer<ClassT, LockT>::operator*()
{
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT, typename LockT>
inline const ClassT &GSharedPointer<ClassT, LockT>::operator*() const
{
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT, typename LockT>
inline ClassT *GSharedPointer<ClassT, LockT>::operator&()
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline const ClassT *GSharedPointer<ClassT, LockT>::operator&() const
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline ClassT* GSharedPointer<ClassT, LockT>::operator->()
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline const ClassT* GSharedPointer<ClassT, LockT>::operator->() const
{
	return m_pRefCounter->Pointer();
}

#endif // _CORE_SHARED_POINTER_INLINE_