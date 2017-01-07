#ifndef _CORE_LIST_STACK_INLINE_
#define _CORE_LIST_STACK_INLINE_

template<typename DataT>
inline GListStack<DataT>::GListStack() :m_tList()
{
}

template<typename DataT>
inline GListStack<DataT>::GListStack(const DataT &data) : m_tList(data)
{
}

template<typename DataT>
inline GListStack<DataT>::~GListStack()
{
}

template<typename DataT>
inline gbool GListStack<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template<typename DataT>
inline void GListStack<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template<typename DataT>
inline gsize GListStack<DataT>::Size() const
{
	return m_tList.Size();
}

template<typename DataT>
inline gvoid GListStack<DataT>::Dispose()
{
	m_tList.RemoveAll();
}

template<typename DataT>
inline gbool GListStack<DataT>::Push(const DataT& data)
{
	return m_tList.AddFirst(data);
}

template<typename DataT>
inline gbool GListStack<DataT>::Pop(DataT *data)
{
	if (IsEmpty())
	{
		return false;
	}

	if (data)
	{
		Top(*data);
	}

	m_tList.RemoveFirst();
	return true;
}

template<typename DataT>
inline gbool GListStack<DataT>::Top(DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}

	data = m_tList.GetFirstData();
	return true;
}

#endif // _CORE_LIST_STACK_INLINE_