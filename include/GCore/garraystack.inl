#ifndef _CORE_ARRAY_STACK_INLINE_
#define _CORE_ARRAY_STACK_INLINE_

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(gsize capacity)
: m_TopCursor(NULL_POS), m_tArray(capacity)
{
	
}

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(const GArrayStack<DataT> &stack)
: m_TopCursor(stack.m_TopCursor)
, m_tArray(stack.m_tArray)
{
	
}

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(GArrayStack<DataT> &&stack)
: m_TopCursor(stack.m_TopCursor)
, m_tArray(GMove(stack.m_tArray))
{
	stack.m_TopCursor = NULL_POS;
}

template<typename DataT>
GINLINE GArrayStack<DataT>& GArrayStack<DataT>::operator=(const GArrayStack<DataT> &stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tArray = stack.m_tArray;
	m_TopCursor = stack.m_TopCursor;
	return *this;
}

template<typename DataT>
GINLINE GArrayStack<DataT>& GArrayStack<DataT>::operator=(GArrayStack<DataT> &&stack)
{
	if (this == &stack)
	{
		return *this;
	}
	// 不需要再调用Dispose，因为GDynamicArray的移动操作符已经处理了原数据的销毁
	m_tArray = GMove(stack.m_tArray);
	m_TopCursor = stack.m_TopCursor;
	stack.m_TopCursor = NULL_POS;
	return *this;
}

template<typename DataT>
GINLINE GArrayStack<DataT>::~GArrayStack()
{
	Dispose();
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Dispose()
{
	m_TopCursor = NULL_POS;
	m_tArray.Dispose();
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::IsEmpty() const
{
	return NULL_POS == m_TopCursor;
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Clear()
{
	m_tArray.Clear();
	m_TopCursor = NULL_POS;
}

template<typename DataT>
GINLINE gsize GArrayStack<DataT>::Size() const
{
	if (m_TopCursor == NULL_POS)
	{
		return 0;
	}
	return m_TopCursor + 1;
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::IsFull() const
{
	if (m_TopCursor == NULL_POS)
	{
		return false;
	}
	return m_TopCursor >= m_tArray.Size() - 1;
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::Resize(gsize capacity)
{
	m_TopCursor = NULL_POS;
	m_tArray.Dispose();
	return m_tArray.Resize(capacity);
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::Push(const DataT &data)
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
GINLINE gbool GArrayStack<DataT>::Push(DataT &&data)
{
	if (IsFull())
	{
		return false;
	}
	if (m_TopCursor == NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = GForward<DataT>(data);
	}
	else
	{
		m_tArray[++m_TopCursor] = GForward<DataT>(data);
	}
	return true;
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::Pop(DataT* data = GNULL)
{
	if (IsEmpty())
	{
		return false;
	}
	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(m_tArray[m_TopCursor]);
	}
	// 销毁元素
	GDestruct(&m_tArray[m_TopCursor]);

	// 游标前移
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
GINLINE const DataT &GArrayStack<DataT>::Top() const
{
	return m_tArray[m_TopCursor];
}

template<typename DataT>
GINLINE DataT &GArrayStack<DataT>::Top()
{
	return m_tArray[m_TopCursor];
}

template<typename DataT>
GINLINE const DataT &GArrayStack<DataT>::Bottom() const
{
	return m_tArray[0];
}

template<typename DataT>
GINLINE DataT &GArrayStack<DataT>::Bottom()
{
	return m_tArray[0];
}

#endif // _CORE_ARRAY_STACK_INLINE_