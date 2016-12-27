#ifndef _CORE_LIST_STACK_INLINE_
#define _CORE_LIST_STACK_INLINE_

template<typename DataT>
inline CsListStack<DataT>::CsListStack() :m_tList()
{
}

template<typename DataT>
inline CsListStack<DataT>::CsListStack(const DataT &data) : m_tList(data)
{
}

template<typename DataT>
inline CsListStack<DataT>::~CsListStack()
{
}

template<typename DataT>
inline cs_bool CsListStack<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template<typename DataT>
inline void CsListStack<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template<typename DataT>
inline cs_size_t CsListStack<DataT>::Size() const
{
	return m_tList.Size();
}

template<typename DataT>
inline cs_void CsListStack<DataT>::Dispose()
{
	m_tList.RemoveAll();
}

template<typename DataT>
inline cs_bool CsListStack<DataT>::Push(const DataT& data)
{
	return m_tList.AddFirst(data);
}

template<typename DataT>
inline cs_bool CsListStack<DataT>::Pop(DataT *data)
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
inline cs_bool CsListStack<DataT>::Top(DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}

	data = m_tList.GetFirstData();
	return true;
}

#endif // _CORE_LIST_STACK_INLINE_