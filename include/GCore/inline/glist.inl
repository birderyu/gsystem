#ifndef _CORE_LIST_INLINE_
#define _CORE_LIST_INLINE_

namespace gsystem { // gsystem

template <typename T>
GINLINE GList<T>::GList()
{

}

template <typename T>
GINLINE GList<T>::GList(gsize size, const T &data)
{
	for (gsize i = 0; i < size; i++)
	{
		m_tList.AddLast(data);
	}
}

template <typename T>
GINLINE GList<T>::GList(const GList<T> &list)
: m_tList(list.m_tList)
{

}

template <typename T>
GINLINE GList<T>::GList(GList<T> &&list)
: m_tList(GMove(list.m_tList))
{

}

template <typename T>
GINLINE GList<T> &GList<T>::operator=(const GList<T> &list)
{
	if (this == &list)
	{
		return *this;
	}

	// Clear(); // 不需要清空元素，因为GDoubleLinkedList的=操作符已经处理了数据的清理
	m_tList = list.m_tList;
	return *this;
}

template <typename T>
GINLINE GList<T> &GList<T>::operator=(GList<T> &&list)
{
	if (this == &list)
	{
		return *this;
	}

	// Clear(); // 不需要清空元素，因为GDoubleLinkedList的=操作符已经处理了数据的清理
	m_tList = GMove(list.m_tList);
	return *this;
}

template <typename T>
GINLINE gvoid GList<T>::Resize(gsize size)
{
	gsize cur_size = Size();
	if (size == cur_size)
	{
		return;
	}
	else if (size > cur_size)
	{
		for (gsize i = cur_size; i < size; i++)
		{
			m_tList.AddLast(T());
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

template <typename T>
GINLINE gsize GList<T>::Size() const
{
	return m_tList.Size();
}

template <typename T>
GINLINE gbool GList<T>::IsEmpty() const
{
	return m_tList.IsEmpty();
}

template <typename T>
GINLINE gvoid GList<T>::Clear()
{
	m_tList.RemoveAll();
}

template <typename T>
GINLINE gvoid GList<T>::Destroy()
{
	m_tList.RemoveAll();
}

template <typename T>
GINLINE T &GList<T>::GetAt(gsize pos)
{
	return m_tList.GetValueAt(pos);
}

template <typename T>
GINLINE const T &GList<T>::GetAt(gsize pos) const
{
	return m_tList.GetValueAt(pos);
}

template <typename T>
GINLINE T &GList<T>::operator[](gsize pos)
{
	return m_tList[pos];
}

template <typename T>
GINLINE const T &GList<T>::operator[](gsize pos) const
{
	return m_tList[pos];
}

template <typename T>
GINLINE gvoid GList<T>::PushBack(const T &data)
{
	m_tList.AddLast(data);
}

template <typename T>
GINLINE gvoid GList<T>::PushBack(T &&data)
{
	m_tList.AddLast(GForward<T>(data));
}

template <typename T>
GINLINE gvoid GList<T>::PushFront(const T &data)
{
	m_tList.AddFirst(data);
}

template <typename T>
GINLINE gvoid GList<T>::PushFront(T &&data)
{
	m_tList.AddFirst(GForward<T>(data));
}

template <typename T>
GINLINE gvoid GList<T>::PopBack(T *data)
{
	m_tList.RemoveLast(data);
}

template <typename T>
GINLINE gvoid GList<T>::PopFront(T *data)
{
	m_tList.RemoveFirst(data);
}

template <typename T>
GINLINE gvoid GList<T>::Append(const T &data)
{
	m_tList.AddLast(data);
}

template <typename T>
GINLINE gvoid GList<T>::Append(T &&data)
{
	m_tList.AddLast(GForward<T>(data));
}

template <typename T>
GINLINE gvoid GList<T>::Append(const GList<T> &list)
{
	// 直接将list的链表拷贝到当前链表的后面
	m_tList += list.m_tList;
}

template <typename T>
GINLINE gvoid GList<T>::Append(GList<T> &&list)
{
	// 直接将list的链表衔接到当前链表的后面，并将list置空
	m_tList += GMove(list.m_tList);
}

template <typename T>
GINLINE typename GList<T>::Iterator GList<T>::Begin()
{
	return GList<T>::Iterator(m_tList.GetFirstNode());
}

template <typename T>
GINLINE typename GList<T>::ConstIterator GList<T>::Begin() const
{
	return GList<T>::ConstIterator(m_tList.GetFirstNode());
}

template <typename T>
GINLINE typename GList<T>::ConstIterator GList<T>::ConstBegin() const
{
	return GList<T>::ConstIterator(m_tList.GetFirstNode());
}

template <typename T>
GINLINE typename GList<T>::Iterator GList<T>::End()
{
	return GList<T>::Iterator();
}

template <typename T>
GINLINE typename GList<T>::ConstIterator GList<T>::End() const
{
	return GList<T>::ConstIterator();
}

template <typename T>
GINLINE typename GList<T>::ConstIterator GList<T>::ConstEnd() const
{
	return GList<T>::ConstIterator();
}

template <typename T>
GINLINE T &GList<T>::First()
{
	return m_tList.GetFirstValue();
}

template <typename T>
GINLINE const T &GList<T>::First() const
{
	return m_tList.GetFirstValue();
}

template <typename T>
GINLINE T &GList<T>::Last()
{
	return m_tList.GetLastValue();
}

template <typename T>
GINLINE const T &GList<T>::Last() const
{
	return m_tList.GetLastValue();
}

template <typename T>
GINLINE gbool GList<T>::StartWith(const T &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename T>
GINLINE gbool GList<T>::EndWith(const T &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

} // namespace gsystem

#endif // _CORE_LIST_INLINE_