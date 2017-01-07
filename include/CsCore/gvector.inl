#ifndef _CORE_VECTOR_INLINE_
#define _CORE_VECTOR_INLINE_

template <typename DataT>
inline GVector<DataT>::GVector()
: m_tArray(0), m_nHead(NULL_POS), m_nTail(0)
{

}

template <typename DataT>
inline GVector<DataT>::GVector(gsize size)
: m_tArray(size), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
inline GVector<DataT>::GVector(gsize size, const DataT &data)
: m_tArray(size, data), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
GVector<DataT>::GVector(const GVector<DataT> &datas)
: m_tArray(datas.m_tArray, datas.m_nHead, datas.Size()), m_nHead(0), m_nTail(datas.Size())
{
	if (datas.Size() == 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
inline gbool GVector<DataT>::Reserve(gsize capacity)
{
	return Reserve(capacity, 0);
}

template <typename DataT>
inline gbool GVector<DataT>::Reserve(gsize capacity, gsize start)
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
inline gbool GVector<DataT>::Resize(gsize size)
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
inline gsize GVector<DataT>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename DataT>
inline gsize GVector<DataT>::Capacity() const
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
inline gbool GVector<DataT>::IsEmpty() const
{
	return Size() == 0;
}

template <typename DataT>
inline gsize GVector<DataT>::RealPos(gsize pos) const
{
	if (m_nHead == NULL_POS)
	{
		return NULL_POS;
	}
	return m_nHead + pos;
}

template <typename DataT>
inline gbool GVector<DataT>::Valid() const
{
	return m_nHead != NULL_POS
		&& m_nTail != 0
		&& m_nTail > m_nHead
		&& m_nTail <= m_tArray.Size();
}

template <typename DataT>
inline gvoid GVector<DataT>::Clear()
{
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
inline DataT &GVector<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
inline const DataT &GVector<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
inline DataT &GVector<DataT>::operator[](gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
inline const DataT &GVector<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
inline gvoid GVector<DataT>::PushBack(const DataT &data)
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
inline gvoid GVector<DataT>::PushFront(const DataT &data)
{
	if (m_nHead == NULL_POS)
	{
		// 扩容
		Reserve(CS_VECTOR_DEFAULT_CAPACITY);
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
inline gvoid GVector<DataT>::PopBack(DataT *data)
{
	if (!Valid())
	{
		return;
	}
	--m_nTail;
	if (data)
	{
		*data = m_tArray[m_nTail];
	}
}

template <typename DataT>
inline gvoid GVector<DataT>::PopBack(gsize size)
{
	if (!Valid() || m_nTail < size)
	{
		return;
	}
	gsize real_pop_size = size < m_nTail ? size : m_nTail;
	m_nTail -= real_pop_size;
}

template <typename DataT>
inline gvoid GVector<DataT>::PopFront(DataT *data)
{
	if (!Valid())
	{
		return;
	}
	if (data)
	{
		*data = m_tArray[m_nHead];
	}
	++m_nHead;
}

template <typename DataT>
inline gvoid GVector<DataT>::PopFront(gsize size)
{
	if (!Valid())
	{
		return;
	}
	m_nHead += size;
	if (m_nHead > m_nTail)
	{
		m_nHead = m_nTail;
	}
}

template <typename DataT>
inline gvoid GVector<DataT>::Append(const DataT &data)
{
	PushBack(data);
}

template <typename DataT>
inline gvoid GVector<DataT>::Append(const GVector<DataT> &datas)
{
	gsize add_size = datas.Size();
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
		m_tArray[m_nTail++] = datas[i];
	}
}

template <typename DataT>
inline typename GVector<DataT>::Iterator GVector<DataT>::Begin()
{
	return GVector<DataT>::Iterator(Head());
}

template <typename DataT>
inline typename GVector<DataT>::ConstIterator GVector<DataT>::Begin() const
{
	return GVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
inline typename GVector<DataT>::ConstIterator GVector<DataT>::ConstBegin() const
{
	return GVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
inline typename GVector<DataT>::Iterator GVector<DataT>::End()
{
	return GVector<DataT>::Iterator(Tail());
}

template <typename DataT>
inline typename GVector<DataT>::ConstIterator GVector<DataT>::End() const
{
	return GVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
inline typename GVector<DataT>::ConstIterator GVector<DataT>::ConstEnd() const
{
	return GVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
inline DataT &GVector<DataT>::First()
{
	GASSERT(Valid());
	return *Head();
}

template <typename DataT>
inline const DataT &GVector<DataT>::First() const
{
	GASSERT(Valid());
	return *Head();
}

template <typename DataT>
inline DataT &GVector<DataT>::Last()
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
inline const DataT &GVector<DataT>::Last() const
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
inline gbool GVector<DataT>::StartWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename DataT>
inline gbool GVector<DataT>::EndWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

template <typename DataT>
inline DataT *GVector<DataT>::Head()
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nHead;
}

template <typename DataT>
inline const DataT *GVector<DataT>::Head() const
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nHead;
}

template <typename DataT>
inline DataT *GVector<DataT>::Tail()
{
	if (m_nTail > m_tArray.Size())
	{
		return NULL;
	}
	return m_tArray += m_nTail;
}

template <typename DataT>
inline const DataT *GVector<DataT>::Tail() const
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nTail;
}

#endif // _CORE_VECTOR_INLINE_