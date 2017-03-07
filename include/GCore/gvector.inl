#ifndef _CORE_VECTOR_INLINE_
#define _CORE_VECTOR_INLINE_

template <typename DataT>
GINLINE GVector<DataT>::GVector()
: m_tArray(0), m_nHead(NULL_POS), m_nTail(0)
{

}

template <typename DataT>
GINLINE GVector<DataT>::GVector(gsize size)
: m_tArray(size), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
GINLINE GVector<DataT>::GVector(gsize size, const DataT &data)
: m_tArray(size, data), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
GINLINE GVector<DataT>::GVector(const GVector<DataT> &datas)
: m_tArray(datas.m_tArray, datas.m_nHead, datas.Size()), m_nHead(0), m_nTail(datas.Size())
{
	if (datas.Size() == 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
GINLINE GVector<DataT>::GVector(GVector<DataT> &&datas)
: m_tArray(GMove(datas.m_tArray))
, m_nHead(datas.m_nHead)
, m_nTail(datas.m_nTail)
{
	datas.m_nHead = NULL_POS;
	datas.m_nTail = 0;
}

template <typename DataT>
GINLINE GVector<DataT> &GVector<DataT>::operator=(const GVector<DataT> &datas)
{
	if (this == &datas)
	{
		return *this;
	}
	// TODO
	return *this;
}

template <typename DataT>
GINLINE GVector<DataT> &GVector<DataT>::operator=(GVector<DataT> &&datas)
{
	if (this == &datas)
	{
		return *this;
	}
	// TODO
	return *this;
}

template <typename DataT>
GINLINE gbool GVector<DataT>::Reserve(gsize capacity)
{
	return Reserve(capacity, 0);
}

template <typename DataT>
GINLINE gbool GVector<DataT>::Reserve(gsize capacity, gsize start)
{
	gsize old_capacity = Capacity();
	if (capacity <= old_capacity)
	{
		if (start == 0)
		{
			// 无需扩容
			return true;
		}
	}

	gsize old_size = Size();
	// 删去前面的无用元素
	if (!m_tArray.Resize(capacity, m_nHead, old_size, start))
	{
		return false;
	}

	if (start == 0)
	{
		m_nHead = NULL_POS;
	}
	else
	{
		m_nHead = start - 1;
	}
	m_nTail = old_size + start;
	return true;
}

template <typename DataT>
GINLINE gbool GVector<DataT>::Resize(gsize size)
{
	if (size > Capacity())
	{
		if (!Reserve(size))
		{
			return false;
		}
	}
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	m_nTail = size - m_nHead;
	return true;
}

template <typename DataT>
GINLINE gsize GVector<DataT>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename DataT>
GINLINE gsize GVector<DataT>::Capacity() const
{
	gsize arr_size = m_tArray.Size();
	if (m_nHead == NULL_POS)
	{
		return arr_size;
	}
	GASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename DataT>
GINLINE gbool GVector<DataT>::IsEmpty() const
{
	return Size() == 0;
}

template <typename DataT>
GINLINE gsize GVector<DataT>::RealPos(gsize pos) const
{
	if (m_nHead == NULL_POS)
	{
		return NULL_POS;
	}
	return m_nHead + pos;
}

template <typename DataT>
GINLINE gbool GVector<DataT>::Valid() const
{
	return m_nHead != NULL_POS
		&& m_nTail != 0
		&& m_nTail > m_nHead
		&& m_nTail <= m_tArray.Size();
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::Clear()
{
	m_tArray.Clear();
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename DataT>
gvoid GVector<DataT>::Dispose()
{
	m_tArray.Dispose();
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename DataT>
GINLINE DataT &GVector<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
GINLINE const DataT &GVector<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
GINLINE DataT *GVector<DataT>::CursorAt(gsize pos)
{
	gsize real_pos = m_nHead + pos;
	return m_tArray.CursorAt(real_pos);
}

template <typename DataT>
GINLINE const DataT *GVector<DataT>::CursorAt(gsize pos) const
{
	gsize real_pos = m_nHead + pos;
	return m_tArray.CursorAt(real_pos);
}

template <typename DataT>
GINLINE DataT &GVector<DataT>::operator[](gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
GINLINE const DataT &GVector<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PushBack(const DataT &data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = data;
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PushBack(DataT &&data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = GForward<DataT>(data);
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PushFront(const DataT &data)
{
	if (m_nHead == NULL_POS)
	{
		// 扩容
		Reserve(G_VECTOR_DEFAULT_CAPACITY);
		m_nHead = 0;
		m_nTail = 1;
		m_tArray[0] = data;
		return;
	}
	else if (m_nHead == 0)
	{
		// 扩容
		gsize old_size = Size();
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1), 1);
	}
	m_tArray[--m_nHead] = data;
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PushFront(DataT &&data)
{
	if (m_nHead == NULL_POS)
	{
		// 扩容
		Reserve(G_VECTOR_DEFAULT_CAPACITY);
		m_nHead = 0;
		m_nTail = 1;
		m_tArray[0] = GForward<DataT>(data);
		return;
	}
	else if (m_nHead == 0)
	{
		// 扩容
		gsize old_size = Size();
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1), 1);
	}
	m_tArray[--m_nHead] = GForward<DataT>(data);
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PopBack(DataT *data)
{
	if (!Valid())
	{
		return;
	}
	
	// 游标前移
	--m_nTail;

	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(m_tArray[m_nTail]);
	}
	// 销毁元素
	GDestruct(&m_tArray[m_nTail]);
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PopBack(gsize size)
{
	while (size > 0)
	{
		PopBack();
		size--;
		if (m_nTail == 0)
		{
			return;
		}
	}
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::PopFront(DataT *data)
{
	if (!Valid())
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

template <typename DataT>
GINLINE gvoid GVector<DataT>::PopFront(gsize size)
{
	while (size > 0)
	{
		PopFront();
		size--;
		if (m_nHead == m_nTail)
		{
			return;
		}
	}
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::Append(const DataT &data)
{
	PushBack(data);
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::Append(DataT &&data)
{
	PushBack(GForward<DataT>(data));
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::Append(const GVector<DataT> &arr)
{
	gsize add_size = arr.Size();
	if (add_size == 0)
	{
		return;
	}

	gsize old_size = Size();
	gsize new_size = old_size + add_size;
	if (new_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		gsize temp = old_size + (old_size / 2 + 1);
		gsize new_capacity = temp > new_size ? temp : new_size;
		Reserve(new_capacity);
	}

	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	for (gsize i = 0; i < add_size; i++)
	{
		m_tArray[m_nTail++] = arr[i];
	}
}

template <typename DataT>
GINLINE gvoid GVector<DataT>::Append(GVector<DataT> &&arr)
{
	gsize add_size = arr.Size();
	if (add_size == 0)
	{
		return;
	}

	gsize old_size = Size();
	gsize new_size = old_size + add_size;
	if (new_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		gsize temp = old_size + (old_size / 2 + 1);
		gsize new_capacity = temp > new_size ? temp : new_size;
		Reserve(new_capacity);
	}

	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	for (gsize i = 0; i < add_size; i++)
	{
		m_tArray[m_nTail++] = GMove(arr[i]);
	}

	// 后续处理，直接将arr销毁
	arr.Dispose();
}

template <typename DataT>
GINLINE typename GVector<DataT>::Iterator GVector<DataT>::Begin()
{
	return GVector<DataT>::Iterator(Head());
}

template <typename DataT>
GINLINE typename GVector<DataT>::ConstIterator GVector<DataT>::Begin() const
{
	return GVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
GINLINE typename GVector<DataT>::ConstIterator GVector<DataT>::ConstBegin() const
{
	return GVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
GINLINE typename GVector<DataT>::Iterator GVector<DataT>::End()
{
	return GVector<DataT>::Iterator(Tail());
}

template <typename DataT>
GINLINE typename GVector<DataT>::ConstIterator GVector<DataT>::End() const
{
	return GVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
GINLINE typename GVector<DataT>::ConstIterator GVector<DataT>::ConstEnd() const
{
	return GVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
GINLINE DataT &GVector<DataT>::First()
{
	GASSERT(Valid());
	return *Head();
}

template <typename DataT>
GINLINE const DataT &GVector<DataT>::First() const
{
	GASSERT(Valid());
	return *Head();
}

template <typename DataT>
GINLINE DataT &GVector<DataT>::Last()
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
GINLINE const DataT &GVector<DataT>::Last() const
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
GINLINE gbool GVector<DataT>::StartWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename DataT>
GINLINE gbool GVector<DataT>::EndWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

template <typename DataT>
GINLINE DataT *GVector<DataT>::Head()
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nHead);
}

template <typename DataT>
GINLINE const DataT *GVector<DataT>::Head() const
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nHead);
}

template <typename DataT>
GINLINE DataT *GVector<DataT>::Tail()
{
	if (m_nTail > m_tArray.Size())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nTail);
}

template <typename DataT>
GINLINE const DataT *GVector<DataT>::Tail() const
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nTail);
}

#endif // _CORE_VECTOR_INLINE_