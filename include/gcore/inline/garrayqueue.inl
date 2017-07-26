#ifndef _CORE_ARRAY_QUEUE_INLINE_
#define _CORE_ARRAY_QUEUE_INLINE_

namespace gsystem { // gsystem

template <typename T> GINLINE
GArrayQueue<T>::GArrayQueue(gsize capacity)
	: m_nHead(GDynamicArray<T>::NULL_POS), m_nTail(0), m_tArray(capacity)
{

}

template <typename T> GINLINE
GArrayQueue<T>::GArrayQueue(const GArrayQueue<T> &queue)
	: m_nHead(queue.m_nHead)
	, m_nTail(queue.m_nTail)
	, m_tArray(queue.m_tArray)
{

}

template <typename T> GINLINE
GArrayQueue<T>::GArrayQueue(GArrayQueue<T> &&queue)
	: m_nHead(queue.m_nHead)
	, m_nTail(queue.m_nTail)
	, m_tArray(GMove(queue.m_tArray))
{
	queue.m_nHead = GDynamicArray<T>::NULL_POS;
	queue.m_nTail = 0;
}

template <typename T> GINLINE
GArrayQueue<T>& GArrayQueue<T>::operator=(const GArrayQueue<T> &queue)
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

template <typename T> GINLINE
GArrayQueue<T>& GArrayQueue<T>::operator=(GArrayQueue<T> &&queue)
{
	if (this == &queue)
	{
		return *this;
	}
	m_tArray = GMove(queue.m_tArray);
	m_nHead = queue.m_nHead;
	m_nTail = queue.m_nTail;
	queue.m_nHead = GDynamicArray<T>::NULL_POS;
	queue.m_nTail = 0;
	return *this;
}

template <typename T> GINLINE
gbool GArrayQueue<T>::IsEmpty() const
{
	return Size() == 0;
}

template <typename T> GINLINE
gsize GArrayQueue<T>::Size() const
{
	if (m_nHead == GDynamicArray<T>::NULL_POS || m_nTail == 0)
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename T> GINLINE
gvoid GArrayQueue<T>::Clear()
{
	m_tArray.Clear();
	m_nHead = GDynamicArray<T>::NULL_POS;
	m_nTail = 0;
}

template <typename T> GINLINE
gvoid GArrayQueue<T>::Destroy()
{
	m_tArray.Destroy();
	m_nHead = GDynamicArray<T>::NULL_POS;
	m_nTail = 0;
}

template <typename T> GINLINE
gvoid GArrayQueue<T>::EnQueue(const T &value)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = value;
	if (m_nHead == GDynamicArray<T>::NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename T> GINLINE
gvoid GArrayQueue<T>::EnQueue(T &&value)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = GForward<T>(value);
	if (m_nHead == GDynamicArray<T>::NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename T> GINLINE
gbool GArrayQueue<T>::DeQueue(T *value)
{
	if (IsEmpty())
	{
		return false;
	}
	if (value)
	{
		// 将元素移走，而非拷贝
		*value = GMove(m_tArray[m_nHead]);
	}
	// 销毁元素
	GDestruct(&m_tArray[m_nHead]);

	// 游标后移
	++m_nHead;

	return true;
}

template <typename T> GINLINE
const T &GArrayQueue<T>::Head() const
{
	GASSERT(m_nHead != GDynamicArray<T>::NULL_POS);
	return m_tArray[m_nHead];
}

template <typename T> GINLINE
T &GArrayQueue<T>::Head()
{
	GASSERT(m_nHead != GDynamicArray<T>::NULL_POS);
	return m_tArray[m_nHead];
}

template <typename T> GINLINE
gsize GArrayQueue<T>::Capacity() const
{
	gsize arr_size = m_tArray.Size();
	if (m_nHead == GDynamicArray<T>::NULL_POS)
	{
		return arr_size;
	}
	GASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename T> GINLINE
gvoid GArrayQueue<T>::Reserve(gsize capacity)
{
	gsize old_capacity = Capacity();
	if (capacity <= old_capacity)
	{
		// 无需扩容
		return;
	}

	gsize old_size = Size();
	if (m_nHead == GDynamicArray<T>::NULL_POS)
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