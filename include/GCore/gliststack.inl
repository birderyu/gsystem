#ifndef _CORE_LIST_STACK_INLINE_
#define _CORE_LIST_STACK_INLINE_

template<typename DataT>
GINLINE GListStack<DataT>::GListStack() :m_tList()
{
}

template<typename DataT>
GINLINE GListStack<DataT>::GListStack(const DataT &data) : m_tList(data)
{
}

template<typename DataT>
GINLINE GListStack<DataT>::~GListStack()
{
}

template<typename DataT>
GINLINE gbool GListStack<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template<typename DataT>
GINLINE void GListStack<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template<typename DataT>
GINLINE gsize GListStack<DataT>::Size() const
{
	return m_tList.Size();
}

template<typename DataT>
GINLINE gvoid GListStack<DataT>::Dispose()
{
	m_tList.RemoveAll();
}

template<typename DataT>
GINLINE gbool GListStack<DataT>::Push(const DataT& data)
{
	return m_tList.AddFirst(data);
}

template<typename DataT>
GINLINE gbool GListStack<DataT>::Push(DataT &&data)
{
	return m_tList.AddFirst(GForward<DataT>(data));
}

template<typename DataT>
GINLINE gbool GListStack<DataT>::Pop(DataT *data)
{
	if (IsEmpty())
	{
		return false;
	}

	if (data)
	{
		*data = GMove(m_tList.GetFirstData());
	}

	m_tList.RemoveFirst();
	return true;
}

template<typename DataT>
GINLINE const DataT &GListStack<DataT>::Top() const
{
	return m_tList.GetFirstData();
}

template<typename DataT>
GINLINE DataT &GListStack<DataT>::Top()
{
	return m_tList.GetFirstData();
}

template<typename DataT>
GINLINE const DataT &GListStack<DataT>::Bottom() const
{
	return m_tList.GetLastData();
}

template<typename DataT>
GINLINE DataT &GListStack<DataT>::Bottom()
{
	return m_tList.GetLastData();
}

#endif // _CORE_LIST_STACK_INLINE_