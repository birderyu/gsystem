#ifndef _CORE_ARRAY_QUEUE_INLINE_
#define _CORE_ARRAY_QUEUE_INLINE_

namespace gsystem { // gsystem

template <typename DataT> GINLINE
GArrayQueue<DataT>::GArrayQueue(gsize capacity)
	: m_nHead(GDynamicArray<DataT>::NULL_POS), m_nTail(0), m_tArray(capacity)
{

}

template <typename DataT> GINLINE
GArrayQueue<DataT>::GArrayQueue(const GArrayQueue<DataT> &queue)
	: m_nHead(queue.m_nHead)
	, m_nTail(queue.m_nTail)
	, m_tArray(queue.m_tArray)
{

}

template <typename DataT> GINLINE
GArrayQueue<DataT>::GArrayQueue(GArrayQueue<DataT> &&queue)
	: m_nHead(queue.m_nHead)
	, m_nTail(queue.m_nTail)
	, m_tArray(GMove(queue.m_tArray))
{
	queue.m_nHead = GDynamicArray<DataT>::NULL_POS;
	queue.m_nTail = 0;
}

template <typename DataT> GINLINE
GArrayQueue<DataT>& GArrayQueue<DataT>::operator=(const GArrayQueue<DataT> &queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tArray = queue.m_tArray;
	m_nHead = queue.m_nHead;
	m_nTail = queue.m_nTail;
	return *this;
}

template <typename DataT> GINLINE
GArrayQueue<DataT>& GArrayQueue<DataT>::operator=(GArrayQueue<DataT> &&queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tArray = GMove(queue.m_tArray);
	m_nHead = queue.m_nHead;
	m_nTail = queue.m_nTail;
	queue.m_nHead = GDynamicArray<DataT>::NULL_POS;
	queue.m_nTail = 0;
	return *this;
}

template <typename DataT> GINLINE
gbool GArrayQueue<DataT>::IsEmpty() const
{
	return Size() == 0;
}

template <typename DataT> GINLINE
gsize GArrayQueue<DataT>::Size() const
{
	if (m_nHead == GDynamicArray<DataT>::NULL_POS || m_nTail == 0)
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::Clear()
{
	m_tArray.Clear();
	m_nHead = GDynamicArray<DataT>::NULL_POS;
	m_nTail = 0;
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::Destroy()
{
	m_tArray.Destroy();
	m_nHead = GDynamicArray<DataT>::NULL_POS;
	m_nTail = 0;
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::EnQueue(const DataT &data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = data;
	if (m_nHead == GDynamicArray<DataT>::NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::EnQueue(DataT &&data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = GForward<DataT>(data);
	if (m_nHead == GDynamicArray<DataT>::NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::DeQueue(DataT *data)
{
	if (IsEmpty())
	{
		return;
	}
	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(m_tArray[m_nHead]);
	}
	// 销毁元素
	GDestruct(&m_tArray[m_nHead]);

	// 游标后移
	++m_nHead;
}

template <typename DataT> GINLINE
const DataT &GArrayQueue<DataT>::Head() const
{
	GASSERT(m_nHead != GDynamicArray<DataT>::NULL_POS);
	return m_tArray[m_nHead];
}

template <typename DataT> GINLINE
DataT &GArrayQueue<DataT>::Head()
{
	GASSERT(m_nHead != GDynamicArray<DataT>::NULL_POS);
	return m_tArray[m_nHead];
}

template <typename DataT> GINLINE
gsize GArrayQueue<DataT>::Capacity() const
{
	gsize arr_size = m_tArray.Size();
	if (m_nHead == GDynamicArray<DataT>::NULL_POS)
	{
		return arr_size;
	}
	GASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename DataT> GINLINE
gvoid GArrayQueue<DataT>::Reserve(gsize capacity)
{
	gsize old_capacity = Capacity();
	if (capacity <= old_capacity)
	{
		// 无需扩容
		return;
	}

	gsize old_size = Size();
	if (m_nHead == GDynamicArray<DataT>::NULL_POS)
	{
		m_tArray.Resize(capacity);
	}
	else
	{
		// 删去前面的无用元素
		m_tArray.Resize(capacity, m_nHead, old_size, 0);
		m_nHead = 0;
		m_nTail = old_size;
	}
}

} // namespace gsystem

#endif // _CORE_ARRAY_QUEUE_INLINE_