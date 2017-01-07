#ifndef _CORE_ARRAY_STACK_INLINE_
#define _CORE_ARRAY_STACK_INLINE_

template<typename DataT>
inline GArrayStack<DataT>::GArrayStack(gsize capacity)
: m_TopCursor(NULL_POS)
{
	m_tArray.Resize(capacity);
}

template<typename DataT>
inline GArrayStack<DataT>::GArrayStack(const GArrayStack<DataT> &other)
: m_TopCursor(other.m_TopCursor)
, m_tArray(other.m_tArray)
{

}

template<typename DataT>
inline GArrayStack<DataT>& GArrayStack<DataT>::operator=(const GArrayStack<DataT>& other)
{
	if (this == &other)
	{
		return *this;
	}
	m_TopCursor = other.m_TopCursor;
	m_tArray = other.m_tArray;
	return *this;
}

template<typename DataT>
inline GArrayStack<DataT>::~GArrayStack()
{
	Dispose();
}

template<typename DataT>
inline gvoid GArrayStack<DataT>::Dispose()
{
	m_TopCursor = NULL_POS;
	m_tArray.Dispose();
}

template<typename DataT>
inline gbool GArrayStack<DataT>::IsEmpty() const
{
	return NULL_POS == m_TopCursor;
}

template<typename DataT>
inline gvoid GArrayStack<DataT>::Clear()
{
	m_TopCursor = NULL_POS;
}

template<typename DataT>
inline gsize GArrayStack<DataT>::Size() const
{
	if (m_TopCursor == NULL_POS)
	{
		return 0;
	}
	return m_TopCursor + 1;
}

template<typename DataT>
inline gbool GArrayStack<DataT>::IsFull() const
{
	if (m_TopCursor == NULL_POS)
	{
		return false;
	}
	return m_TopCursor >= m_tArray.Size() - 1;
}

template<typename DataT>
inline gbool GArrayStack<DataT>::Resize(gsize capacity)
{
	m_TopCursor = NULL_POS;
	m_tArray.Dispose();
	return m_tArray.Resize(capacity);
}

template<typename DataT>
inline gbool GArrayStack<DataT>::Push(const DataT& data)
{
	if (IsFull())
	{
		return false;
	}
	if (m_TopCursor == NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = data;
	}
	else
	{
		m_tArray[++m_TopCursor] = data;
	}
	return true;
}

template<typename DataT>
inline gbool GArrayStack<DataT>::Pop(DataT* data = NULL)
{
	if (IsEmpty())
	{
		return false;
	}
	if (data)
	{
		*data = m_tArray[m_TopCursor];
	}
	if (m_TopCursor == 0)
	{
		m_TopCursor = NULL_POS;
	}
	else
	{
		--m_TopCursor;
	}
	return true;
}

template<typename DataT>
inline gbool GArrayStack<DataT>::Top(DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	data = m_tArray[m_TopCursor];
	return true;
}

#endif // _CORE_ARRAY_STACK_INLINE_