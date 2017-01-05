#ifndef _CORE_SHARED_POINTER_INLINE_
#define _CORE_SHARED_POINTER_INLINE_

template <typename ClassT, typename LockT>
inline CsSharedPointer<ClassT, LockT>::CsSharedPointer(ClassT *ptr, cs_size_t count)
: m_pRefCounter(new CsReferenceCounter<ClassT, LockT>(ptr, count))
{

}

template <typename ClassT, typename LockT>
inline CsSharedPointer<ClassT, LockT>::CsSharedPointer(const CsSharedPointer<ClassT, LockT> &ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	m_pRefCounter->Add();
}

template <typename ClassT, typename LockT>
inline CsSharedPointer<ClassT, LockT>::~CsSharedPointer()
{
	m_pRefCounter->Release();
}

template <typename ClassT, typename LockT>
inline cs_void CsSharedPointer<ClassT, LockT>::Reset(ClassT *ptr)
{
	m_pRefCounter->Release();
	m_pRefCounter = new CsReferenceCounter<ClassT, LockT>(ptr);
}

template <typename ClassT, typename LockT>
inline cs_bool CsSharedPointer<ClassT, LockT>::IsNull() const
{
	return m_pRefCounter->Pointer() == NULL;
}

template <typename ClassT, typename LockT>
inline cs_bool CsSharedPointer<ClassT, LockT>::IsShared() const
{
	return m_pRefCounter->Count() > 1;
}

template <typename ClassT, typename LockT>
inline cs_size_t CsSharedPointer<ClassT, LockT>::Add()
{
	return m_pRefCounter->Add();
}

template <typename ClassT, typename LockT>
inline cs_void CsSharedPointer<ClassT, LockT>::Release()
{
	m_pRefCounter->Release();
}

template <typename ClassT, typename LockT>
inline cs_size_t CsSharedPointer<ClassT, LockT>::Count() const
{
	return m_pRefCounter->Count();
}

template <typename ClassT, typename LockT>
inline CsSharedPointer<ClassT, LockT> &CsSharedPointer<ClassT, LockT>::operator=(const CsSharedPointer<ClassT, LockT> &ptr)
{
	ptr.m_pRefCounter->Add();
	m_pRefCounter->Release();
	m_pRefCounter = ptr.m_pRefCounter;
	return *this;
}

template <typename ClassT, typename LockT>
inline ClassT &CsSharedPointer<ClassT, LockT>::operator*()
{
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT, typename LockT>
inline const ClassT &CsSharedPointer<ClassT, LockT>::operator*() const
{
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT, typename LockT>
inline ClassT *CsSharedPointer<ClassT, LockT>::operator&()
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline const ClassT *CsSharedPointer<ClassT, LockT>::operator&() const
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline ClassT* CsSharedPointer<ClassT, LockT>::operator->()
{
	return m_pRefCounter->Pointer();
}

template <typename ClassT, typename LockT>
inline const ClassT* CsSharedPointer<ClassT, LockT>::operator->() const
{
	return m_pRefCounter->Pointer();
}

#endif // _CORE_SHARED_POINTER_INLINE_