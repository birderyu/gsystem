#ifndef _CORE_VECTOR_INLINE_
#define _CORE_VECTOR_INLINE_

template <typename DataT>
inline CsVector<DataT>::CsVector()
: m_tArray(0), m_nHead(NULL_POS), m_nTail(0)
{

}

template <typename DataT>
inline CsVector<DataT>::CsVector(cs_size_t size)
: m_tArray(size), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
inline CsVector<DataT>::CsVector(cs_size_t size, const DataT &data)
: m_tArray(size, data), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
CsVector<DataT>::CsVector(const CsVector<DataT> &datas)
: m_tArray(datas.m_tArray, datas.m_nHead, datas.Size()), m_nHead(0), m_nTail(datas.Size())
{
	if (datas.Size() == 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename DataT>
inline cs_bool CsVector<DataT>::Reserve(cs_size_t capacity)
{
	return Reserve(capacity, 0);
}

template <typename DataT>
inline cs_bool CsVector<DataT>::Reserve(cs_size_t capacity, cs_size_t start)
{
	cs_size_t old_capacity = Capacity();
	if (capacity <= old_capacity)
	{
		if (start == 0)
		{
			// 无需扩容
			return true;
		}
	}

	cs_size_t old_size = Size();
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
inline cs_bool CsVector<DataT>::Resize(cs_size_t size)
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
inline cs_size_t CsVector<DataT>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename DataT>
inline cs_size_t CsVector<DataT>::Capacity() const
{
	cs_size_t arr_size = m_tArray.Size();
	if (m_nHead == NULL_POS)
	{
		return arr_size;
	}
	CS_ASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename DataT>
inline cs_bool CsVector<DataT>::IsEmpty() const
{
	return Size() == 0;
}

template <typename DataT>
inline cs_size_t CsVector<DataT>::RealPos(cs_size_t pos) const
{
	if (m_nHead == NULL_POS)
	{
		return NULL_POS;
	}
	return m_nHead + pos;
}

template <typename DataT>
inline cs_bool CsVector<DataT>::Valid() const
{
	return m_nHead != NULL_POS
		&& m_nTail != 0
		&& m_nTail > m_nHead
		&& m_nTail <= m_tArray.Size();
}

template <typename DataT>
inline cs_void CsVector<DataT>::Clear()
{
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename DataT>
cs_void CsVector<DataT>::Dispose()
{
	m_tArray.Dispose();
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename DataT>
inline DataT &CsVector<DataT>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < Size());
	cs_size_t real_pos = RealPos(pos);
	CS_ASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
inline const DataT &CsVector<DataT>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < Size());
	cs_size_t real_pos = RealPos(pos);
	CS_ASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename DataT>
inline DataT &CsVector<DataT>::operator[](cs_size_t pos)
{
	CS_ASSERT(pos < Size());
	cs_size_t real_pos = RealPos(pos);
	CS_ASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
inline const DataT &CsVector<DataT>::operator[](cs_size_t pos) const
{
	CS_ASSERT(pos < Size());
	cs_size_t real_pos = RealPos(pos);
	CS_ASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename DataT>
inline cs_void CsVector<DataT>::PushBack(const DataT &data)
{
	cs_size_t old_size = Size();
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
inline cs_void CsVector<DataT>::PushFront(const DataT &data)
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
		cs_size_t old_size = Size();
		// 按照原来数据的一半进行扩容
		Reserve(old_size + (old_size / 2 + 1), 1);
	}
	m_tArray[--m_nHead] = data;
}

template <typename DataT>
inline cs_void CsVector<DataT>::PopBack(DataT *data)
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
inline cs_void CsVector<DataT>::PopBack(cs_size_t size)
{
	if (!Valid() || m_nTail < size)
	{
		return;
	}
	cs_size_t real_pop_size = size < m_nTail ? size : m_nTail;
	m_nTail -= real_pop_size;
}

template <typename DataT>
inline cs_void CsVector<DataT>::PopFront(DataT *data)
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
inline cs_void CsVector<DataT>::PopFront(cs_size_t size)
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
inline cs_void CsVector<DataT>::Append(const DataT &data)
{
	PushBack(data);
}

template <typename DataT>
inline cs_void CsVector<DataT>::Append(const CsVector<DataT> &datas)
{
	cs_size_t add_size = datas.Size();
	if (add_size == 0)
	{
		return;
	}

	cs_size_t old_size = Size();
	cs_size_t new_size = old_size + add_size;
	if (new_size >= Capacity())
	{
		// 需要扩容
		// 按照原来数据的一半进行扩容
		cs_size_t temp = old_size + (old_size / 2 + 1);
		cs_size_t new_capacity = temp > new_size ? temp : new_size;
		Reserve(new_capacity);
	}

	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	for (cs_size_t i = 0; i < add_size; i++)
	{
		m_tArray[m_nTail++] = datas[i];
	}
}

template <typename DataT>
inline typename CsVector<DataT>::Iterator CsVector<DataT>::Begin()
{
	return CsVector<DataT>::Iterator(Head());
}

template <typename DataT>
inline typename CsVector<DataT>::ConstIterator CsVector<DataT>::Begin() const
{
	return CsVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
inline typename CsVector<DataT>::ConstIterator CsVector<DataT>::ConstBegin() const
{
	return CsVector<DataT>::ConstIterator(Head());
}

template <typename DataT>
inline typename CsVector<DataT>::Iterator CsVector<DataT>::End()
{
	return CsVector<DataT>::Iterator(Tail());
}

template <typename DataT>
inline typename CsVector<DataT>::ConstIterator CsVector<DataT>::End() const
{
	return CsVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
inline typename CsVector<DataT>::ConstIterator CsVector<DataT>::ConstEnd() const
{
	return CsVector<DataT>::ConstIterator(Tail());
}

template <typename DataT>
inline DataT &CsVector<DataT>::First()
{
	CS_ASSERT(Valid());
	return *Head();
}

template <typename DataT>
inline const DataT &CsVector<DataT>::First() const
{
	CS_ASSERT(Valid());
	return *Head();
}

template <typename DataT>
inline DataT &CsVector<DataT>::Last()
{
	CS_ASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
inline const DataT &CsVector<DataT>::Last() const
{
	CS_ASSERT(Valid());
	return *(Tail() - 1);
}

template <typename DataT>
inline cs_bool CsVector<DataT>::StartWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename DataT>
inline cs_bool CsVector<DataT>::EndWith(const DataT &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

template <typename DataT>
inline DataT *CsVector<DataT>::Head()
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nHead;
}

template <typename DataT>
inline const DataT *CsVector<DataT>::Head() const
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nHead;
}

template <typename DataT>
inline DataT *CsVector<DataT>::Tail()
{
	if (m_nTail > m_tArray.Size())
	{
		return NULL;
	}
	return m_tArray += m_nTail;
}

template <typename DataT>
inline const DataT *CsVector<DataT>::Tail() const
{
	if (!Valid())
	{
		return NULL;
	}
	return m_tArray += m_nTail;
}

#endif // _CORE_VECTOR_INLINE_