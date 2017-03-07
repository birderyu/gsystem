#ifndef _CORE_LIST_INLINE_
#define _CORE_LIST_INLINE_

template <typename DataT>
GINLINE GList<DataT>::GList()
{

}

template <typename DataT>
GINLINE GList<DataT>::GList(gsize size, const DataT &data)
{
	for (gsize i = 0; i < size; i++)
	{
		m_tList.AddLast(data);
	}
}

template <typename DataT>
GINLINE GList<DataT>::GList(const GList<DataT> &list)
: m_tList(list.m_tList)
{

}

template <typename DataT>
GINLINE GList<DataT>::GList(GList<DataT> &&list)
: m_tList(GMove(list.m_tList))
{

}

template <typename DataT>
GINLINE GList<DataT> &GList<DataT>::operator=(const GList<DataT> &list)
{
	if (this == &list)
	{
		return *this;
	}

	// Clear(); // 不需要清空元素，因为GDoubleLinkedList的=操作符已经处理了数据的清理
	m_tList = list.m_tList;
	return *this;
}

template <typename DataT>
GINLINE GList<DataT> &GList<DataT>::operator=(GList<DataT> &&list)
{
	if (this == &list)
	{
		return *this;
	}

	// Clear(); // 不需要清空元素，因为GDoubleLinkedList的=操作符已经处理了数据的清理
	m_tList = GMove(list.m_tList);
	return *this;
}

template <typename DataT>
GINLINE gbool GList<DataT>::Resize(gsize size)
{
	gsize cur_size = Size();
	if (size == cur_size)
	{
		return true;
	}
	else if (size > cur_size)
	{
		for (gsize i = cur_size; i < size; i++)
		{
			m_tList.AddLast(DataT());
		}
	}
	else
	{
		// size < cur_size
		for (gsize i = size; i < cur_size; i++)
		{
			m_tList.RemoveLast();
		}
	}
}

template <typename DataT>
GINLINE gsize GList<DataT>::Size() const
{
	return m_tList.Size();
}

template <typename DataT>
GINLINE gbool GList<DataT>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template <typename DataT>
GINLINE gvoid GList<DataT>::Clear()
{
	m_tList.RemoveAll();
}

template <typename DataT>
GINLINE DataT &GList<DataT>::GetAt(gsize pos)
{
	return m_tList.GetDataAt(pos);
}

template <typename DataT>
GINLINE const DataT &GList<DataT>::GetAt(gsize pos) const
{
	return m_tList.GetDataAt(pos);
}

template <typename DataT>
GINLINE DataT &GList<DataT>::operator[](gsize pos)
{
	return m_tList[pos];
}

template <typename DataT>
GINLINE const DataT &GList<DataT>::operator[](gsize pos) const
{
	return m_tList[pos];
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PushBack(const DataT &data)
{
	m_tList.AddLast(data);
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PushBack(DataT &&data)
{
	m_tList.AddLast(GForward<DataT>(data));
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PushFront(const DataT &data)
{
	m_tList.AddFirst(data);
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PushFront(DataT &&data)
{
	m_tList.AddFirst(GForward<DataT>(data));
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PopBack()
{
	m_tList.RemoveLast();
}

template <typename DataT>
GINLINE gvoid GList<DataT>::PopFront()
{
	m_tList.RemoveFirst();
}

template <typename DataT>
GINLINE gvoid GList<DataT>::Append(const DataT &data)
{
	m_tList.AddLast(data);
}

template <typename DataT>
GINLINE gvoid GList<DataT>::Append(DataT &&data)
{
	m_tList.AddLast(GForward<DataT>(data));
}

template <typename DataT>
GINLINE gvoid GList<DataT>::Append(const GList<DataT> &list)
{
	// 直接将list的链表拷贝到当前链表的后面
	m_tList += list.m_tList;
}

template <typename DataT>
GINLINE gvoid GList<DataT>::Append(GList<DataT> &&list)
{
	// 直接将list的链表衔接到当前链表的后面，并将list置空
	m_tList += GMove(list.m_tList);
}

template <typename DataT>
GINLINE typename GList<DataT>::Iterator GList<DataT>::Begin()
{
	return GList<DataT>::Iterator(m_tList.GetFirstNode());
}

template <typename DataT>
GINLINE typename GList<DataT>::ConstIterator GList<DataT>::Begin() const
{
	return GList<DataT>::ConstIterator(m_tList.GetFirstNode());
}

template <typename DataT>
GINLINE typename GList<DataT>::ConstIterator GList<DataT>::ConstBegin() const
{
	return GList<DataT>::ConstIterator(m_tList.GetFirstNode());
}

template <typename DataT>
GINLINE typename GList<DataT>::Iterator GList<DataT>::End()
{
	return GList<DataT>::Iterator();
}

template <typename DataT>
GINLINE typename GList<DataT>::ConstIterator GList<DataT>::End() const
{
	return GList<DataT>::ConstIterator();
}

template <typename DataT>
GINLINE typename GList<DataT>::ConstIterator GList<DataT>::ConstEnd() const
{
	return GList<DataT>::ConstIterator();
}

template <typename DataT>
GINLINE DataT &GList<DataT>::First()
{
	return m_tList.GetFirstData();
}

template <typename DataT>
GINLINE const DataT &GList<DataT>::First() const
{
	return m_tList.GetFirstData();
}

template <typename DataT>
GINLINE DataT &GList<DataT>::Last()
{
	return m_tList.GetLastData();
}

template <typename DataT>
GINLINE const DataT &GList<DataT>::Last() const
{
	return m_tList.GetLastData();
}

template <typename DataT>
GINLINE gbool GList<DataT>::StartWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename DataT>
GINLINE gbool GList<DataT>::EndWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

#endif // _CORE_LIST_INLINE_