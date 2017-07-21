#ifndef _CORE_SHARED_POINTER_GINLINE_
#define _CORE_SHARED_POINTER_GINLINE_

namespace gsystem { // gsystem

template <typename ClassT> GINLINE
GSharedPtr<ClassT>::GSharedPtr(ClassT *ptr, gsize count)
	: m_pRefCounter(new GRefCounter<ClassT>(ptr, count))
{

}

template <typename ClassT> GINLINE
GSharedPtr<ClassT>::GSharedPtr(const GSharedPtr<ClassT> &ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	m_pRefCounter->Add();
}

template <typename ClassT>
GINLINE GSharedPtr<ClassT>::GSharedPtr(GSharedPtr<ClassT> &&ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	ptr.m_pRefCounter = GNULL;
}

template <typename ClassT>
GINLINE GSharedPtr<ClassT>::~GSharedPtr()
{
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
}

template <typename ClassT>
GINLINE gvoid GSharedPtr<ClassT>::Reset(ClassT *ptr, gsize count)
{
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
	m_pRefCounter = new GRefCounter<ClassT>(ptr, count);
}

template <typename ClassT>
template <typename NexClassT>
GINLINE GSharedPtr<NexClassT> GSharedPtr<ClassT>::DynamicConvertTo()
{
	if (GNULL == m_pRefCounter || GNULL == m_pRefCounter->Pointer())
	{
		return GSharedPtr<NexClassT>(GNULL);
	}
	NexClassT *ptr = dynamic_cast<NexClassT*>(m_pRefCounter->Pointer());
	if (GNULL == ptr)
	{
		return GSharedPtr<NexClassT>(GNULL);
	}
	return GSharedPtr<NexClassT>(ptr, m_pRefCounter->Add());
}

template <typename ClassT>
GINLINE gbool GSharedPtr<ClassT>::Shared() const
{
	if (GNULL == m_pRefCounter)
	{
		return false;
	}
	return m_pRefCounter->Count() > 1;
}

template <typename ClassT>
GINLINE GSharedPtr<ClassT>::operator gbool() const
{
	return GNULL != m_pRefCounter &&
		GNULL != m_pRefCounter->Pointer();
}

template <typename ClassT>
GINLINE GSharedPtr<ClassT> &GSharedPtr<ClassT>::operator=(const GSharedPtr<ClassT> &ptr)
{
	if (this == &ptr)
	{
		return *this;
	}
	
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
	m_pRefCounter = ptr.m_pRefCounter;
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Add();
	}
	return *this;
}

template <typename ClassT>
GINLINE GSharedPtr<ClassT> &GSharedPtr<ClassT>::operator=(GSharedPtr<ClassT> &&ptr)
{
	if (this == &ptr)
	{
		return *this;
	}
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
	m_pRefCounter = ptr.m_pRefCounter;
	ptr.m_pRefCounter = GNULL;
	return *this;
}

template <typename ClassT>
GINLINE ClassT &GSharedPtr<ClassT>::operator*()
{
	GASSERT(m_pRefCounter);
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT>
GINLINE const ClassT &GSharedPtr<ClassT>::operator*() const
{
	GASSERT(m_pRefCounter);
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT>
GINLINE ClassT* GSharedPtr<ClassT>::operator->()
{
	if (GNULL == m_pRefCounter)
	{
		return GNULL;
	}
	return m_pRefCounter->Pointer();
}

template <typename ClassT>
GINLINE const ClassT* GSharedPtr<ClassT>::operator->() const
{
	if (GNULL == m_pRefCounter)
	{
		return GNULL;
	}
	return m_pRefCounter->Pointer();
}

template<typename ClassT, typename... TS> GINLINE
GSharedPtr<ClassT> GMakeShared(TS&&... args)
{
	return GSharedPtr<ClassT>(new ClassT(GForward<TS>(args)...), 1);
}

} // namespace gsystem

#endif // _CORE_SHARED_POINTER_GINLINE_