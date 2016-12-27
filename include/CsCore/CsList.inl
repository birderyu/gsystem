#ifndef _CORE_LIST_INLINE_
#define _CORE_LIST_INLINE_

template <typename DataT>
inline CsList<DataT>::CsList()
{

}

template <typename DataT>
inline CsList<DataT>::CsList(cs_size_t size, const DataT &data)
{
	for (cs_size_t i = 0; i < size; i++)
	{
		m_tList.AddLast(data);
	}
}

template <typename DataT>
inline CsList<DataT>::CsList(const CsList<DataT> &list)
: m_tList(list)
{

}

template <typename DataT>
inline cs_bool CsList<DataT>::Resize(cs_size_t size)
{
	cs_size_t cur_size = Size();
	if (size == cur_size)
	{
		return true;
	}
	else if (size > cur_size)
	{
		for (cs_size_t i = cur_size; i < size; i++)
		{
			m_tList.AddLast(DataT());
		}
	}
	else
	{
		// size < cur_size
		for (cs_size_t i = size; i < cur_size; i++)
		{
			m_tList.RemoveLast();
		}
	}
}

template <typename DataT>
inline cs_size_t CsList<DataT>::Size() const
{
	return m_tList.Size();
}

template <typename DataT>
inline cs_bool CsList<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template <typename DataT>
inline cs_void CsList<DataT>::Clear()
{
	m_tList.RemoveAll()
}

template <typename DataT>
inline DataT &CsList<DataT>::GetAt(cs_size_t pos)
{
	return m_tList.GetDataAt(pos);
}

template <typename DataT>
inline const DataT &CsList<DataT>::GetAt(cs_size_t pos) const
{
	return m_tList.GetDataAt(pos);
}

template <typename DataT>
inline DataT &CsList<DataT>::operator[](cs_size_t pos)
{
	return m_tList[pos];
}

template <typename DataT>
inline const DataT &CsList<DataT>::operator[](cs_size_t pos) const
{
	return m_tList[pos];
}

template <typename DataT>
inline cs_void CsList<DataT>::PushBack(const DataT &data)
{
	m_tList.AddLast(data);
}

template <typename DataT>
inline cs_void CsList<DataT>::PushFront(const DataT &data)
{
	m_tList.AddFirst(data);
}

template <typename DataT>
inline cs_void CsList<DataT>::PopBack()
{
	m_tList.RemoveLast();
}

template <typename DataT>
inline cs_void CsList<DataT>::PopFront()
{
	m_tList.RemoveFirst();
}

template <typename DataT>
inline cs_void CsList<DataT>::Append(const DataT &data)
{
	m_tList.AddLast(data);
}

template <typename DataT>
inline cs_void CsList<DataT>::Append(const CsList<DataT> &datas)
{
	for (CsList<DataT>::ConstIterator citer = datas.ConstBegin();
		citer != datas.ConstEnd(); citer++)
	{
		m_tList.AddLast(*citer);
	}
}

template <typename DataT>
inline typename CsList<DataT>::Iterator CsList<DataT>::Begin()
{
	return CsList<DataT>::Iterator(m_tList.GetFirstNode());
}

template <typename DataT>
inline typename CsList<DataT>::ConstIterator CsList<DataT>::Begin() const
{
	return CsList<DataT>::ConstIterator(m_tList.GetFirstNode());
}

template <typename DataT>
inline typename CsList<DataT>::ConstIterator CsList<DataT>::ConstBegin() const
{
	return CsList<DataT>::ConstIterator(m_tList.GetFirstNode());
}

template <typename DataT>
inline typename CsList<DataT>::Iterator CsList<DataT>::End()
{
	return CsList<DataT>::Iterator();
}

template <typename DataT>
inline typename CsList<DataT>::ConstIterator CsList<DataT>::End() const
{
	return CsList<DataT>::ConstIterator();
}

template <typename DataT>
inline typename CsList<DataT>::ConstIterator CsList<DataT>::ConstEnd() const
{
	return CsList<DataT>::ConstIterator();
}

template <typename DataT>
inline DataT &CsList<DataT>::First()
{
	return m_tList.GetFirstData();
}

template <typename DataT>
inline const DataT &CsList<DataT>::First() const
{
	return m_tList.GetFirstData();
}

template <typename DataT>
inline DataT &CsList<DataT>::Last()
{
	return m_tList.GetLastData();
}

template <typename DataT>
inline const DataT &CsList<DataT>::Last() const
{
	return m_tList.GetLastData();
}

template <typename DataT>
inline cs_bool CsList<DataT>::StartWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename DataT>
inline cs_bool CsList<DataT>::EndWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

#endif // _CORE_LIST_INLINE_