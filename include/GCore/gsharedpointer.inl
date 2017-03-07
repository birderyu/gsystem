#ifndef _CORE_SHARED_POINTER_GINLINE_
#define _CORE_SHARED_POINTER_GINLINE_

template <typename ClassT>
GINLINE GSharedPointer<ClassT>::GSharedPointer(ClassT *ptr, gsize count)
: m_pRefCounter(new GReferenceCounter<ClassT>(ptr, count))
{

}

template <typename ClassT>
GINLINE GSharedPointer<ClassT>::GSharedPointer(const GSharedPointer<ClassT> &ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	m_pRefCounter->Add();
}

template <typename ClassT>
GINLINE GSharedPointer<ClassT>::GSharedPointer(GSharedPointer<ClassT> &&ptr)
: m_pRefCounter(ptr.m_pRefCounter)
{
	ptr.m_pRefCounter = GNULL;
}

template <typename ClassT>
GINLINE GSharedPointer<ClassT>::~GSharedPointer()
{
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
}

template <typename ClassT>
GINLINE gvoid GSharedPointer<ClassT>::Reset(ClassT *ptr, gsize count)
{
	if (GNULL != m_pRefCounter)
	{
		m_pRefCounter->Release();
	}
	m_pRefCounter = new GReferenceCounter<ClassT>(ptr, count);
}

template <typename ClassT>
template <typename NexClassT>
GINLINE GSharedPointer<NexClassT> GSharedPointer<ClassT>::DynamicConvertTo()
{
	if (GNULL == m_pRefCounter || GNULL == m_pRefCounter->Pointer())
	{
		return GSharedPointer<NexClassT>(GNULL);
	}
	NexClassT *ptr = dynamic_cast<NexClassT*>(m_pRefCounter->Pointer());
	if (GNULL == ptr)
	{
		return GSharedPointer<NexClassT>(GNULL);
	}
	return GSharedPointer<NexClassT>(ptr, m_pRefCounter->Add());
}

template <typename ClassT>
GINLINE gbool GSharedPointer<ClassT>::Shared() const
{
	if (GNULL == m_pRefCounter)
	{
		return false;
	}
	return m_pRefCounter->Count() > 1;
}

template <typename ClassT>
GINLINE GSharedPointer<ClassT>::operator gbool() const
{
	return GNULL != m_pRefCounter &&
		GNULL != m_pRefCounter->Pointer();
}

template <typename ClassT>
GINLINE GSharedPointer<ClassT> &GSharedPointer<ClassT>::operator=(const GSharedPointer<ClassT> &ptr)
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
GINLINE GSharedPointer<ClassT> &GSharedPointer<ClassT>::operator=(GSharedPointer<ClassT> &&ptr)
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
GINLINE ClassT &GSharedPointer<ClassT>::operator*()
{
	GASSERT(m_pRefCounter);
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT>
GINLINE const ClassT &GSharedPointer<ClassT>::operator*() const
{
	GASSERT(m_pRefCounter);
	return *(m_pRefCounter->Pointer());
}

template <typename ClassT>
GINLINE ClassT* GSharedPointer<ClassT>::operator->()
{
	if (GNULL == m_pRefCounter)
	{
		return GNULL;
	}
	return m_pRefCounter->Pointer();
}

template <typename ClassT>
GINLINE const ClassT* GSharedPointer<ClassT>::operator->() const
{
	if (GNULL == m_pRefCounter)
	{
		return GNULL;
	}
	return m_pRefCounter->Pointer();
}

template<typename ClassT, typename... TS>
GINLINE GSharedPointer<ClassT> GMakeShared(TS&&... args)
{
	return GSharedPointer<ClassT>(new ClassT(GForward<TS>(args)...), 1);
}

#endif // _CORE_SHARED_POINTER_GINLINE_