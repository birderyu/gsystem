#ifndef _CORE_DYNAMIC_ARRAY_INLINE_
#define _CORE_DYNAMIC_ARRAY_INLINE_

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray()
: m_pData(GNULL), m_nSize(0)
{

}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArray<DataT>::CreateArray(m_nSize);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(gsize size, const DataT &data)
: m_pData(GNULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArray<DataT>::CreateArray(m_nSize, data);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(const GDynamicArray<DataT> &array)
: m_pData(GNULL), m_nSize(array.m_nSize)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = GArray<DataT>::CreateArray(array.m_pData, 0, array.m_nSize);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(GDynamicArray<DataT> &&arr)
: m_pData(arr.m_pData), m_nSize(arr.m_nSize)
{
	arr.m_pData = GNULL;
	arr.m_nSize = 0;
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::GDynamicArray(const GArray<DataT> &array, gsize start, gsize size)
: m_pData(GNULL), m_nSize(size)
{
	if (size <= 0 || start >= array.Size())
	{
		m_nSize = 0;
		return;
	}
	m_pData = GArray<DataT>::CreateArray(&array[0], start, size);
}

template <typename DataT>
GINLINE GDynamicArray<DataT>::~GDynamicArray()
{
	Dispose();
}

template <typename DataT>
GINLINE gsize GDynamicArray<DataT>::Size() const
{
	return m_nSize;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::IsEmpty() const
{
	return m_pData == GNULL
		|| m_nSize <= 0;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Resize(gsize size)
{
	if (m_nSize == size)
	{
		return true;
	}

	if (size <= 0)
	{
		// 直接清空数组
		Dispose();
		return true;
	}

	// 当数组不存在时，会构建新的数组
	m_pData = GArray<DataT>::ResizeArray(m_pData, m_nSize, size);

	m_nSize = size;
	return true;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Resize(gsize size, const DataT &data)
{
	if (m_nSize == size)
	{
		return true;
	}

	if (size <= 0)
	{
		// 直接清空数组
		Dispose();
		return true;
	}

	m_pData = GArray<DataT>::ResizeArray(m_pData, m_nSize, size, data);

	m_nSize = size;
	return true;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start)
{
	if (new_size == m_nSize && start == 0 && size == m_nSize)
	{
		return true;
	}
	
	if (new_size <= 0)
	{
		// 直接清空数组
		Dispose();
		return true;
	}

	// 重新分配内存
	m_pData = GArray<DataT>::ResizeArray(m_pData, start, size, new_size, new_start);

	m_nSize = new_size;
	return true;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start, const DataT &data)
{
	if (new_size == m_nSize && start == 0 && size == m_nSize)
	{
		return true;
	}

	if (new_size <= 0)
	{
		// 直接清空数组
		Dispose();
		return true;
	}

	if (!m_pData)
	{
		m_pData = GArray<DataT>::CreateArray(new_start, data);
	}
	else
	{
		// 重新分配内存
		m_pData = GArray<DataT>::ResizeArray(m_pData, start, size, new_size, new_start);
	}
	m_nSize = new_size;
	return true;
}

template <typename DataT>
gvoid GDynamicArray<DataT>::Clear()
{
	GArray<DataT>::ClearArray(m_pData, m_nSize);
}

template <typename DataT>
GINLINE gvoid GDynamicArray<DataT>::Dispose()
{
	GArray<DataT>::DestoryArray(m_pData, m_nSize);
	m_pData = GNULL;
	m_nSize = 0;
}

template <typename DataT>
GINLINE DataT &GDynamicArray<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE const DataT &GDynamicArray<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE DataT *GDynamicArray<DataT>::CursorAt(gsize pos)
{
	return m_pData + pos;
}

template <typename DataT>
GINLINE const DataT *GDynamicArray<DataT>::CursorAt(gsize pos) const
{
	return m_pData + pos;
}

template <typename DataT>
GINLINE DataT &GDynamicArray<DataT>::operator[](gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE const DataT &GDynamicArray<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::RemoveAt(gsize pos)
{
	if (0 == m_nSize)
	{
		return false;
	}
	if (1 == m_nSize)
	{
		if (0 == pos)
		{
			Dispose();
			return true;
		}
		return false;
	}
	m_pData = GArray<DataT>::RemoveArrayElementAt(m_pData, m_nSize, pos);
	m_nSize--;
	return false;
}

template <typename DataT>
GINLINE GDynamicArray<DataT> &GDynamicArray<DataT>::operator=(const GDynamicArray<DataT> &arr)
{
	if (this == &arr)
	{
		return *this;
	}
	if (arr.IsEmpty())
	{
		Dispose();
		return *this;
	}
	m_pData = GArray<DataT>::CopyArrayFrom(m_pData, m_nSize, arr.m_pData, arr.m_nSize);
	m_nSize = arr.m_nSize;
	return *this;
}

template <typename DataT>
GINLINE GDynamicArray<DataT> &GDynamicArray<DataT>::operator=(GDynamicArray<DataT> &&arr)
{
	if (this == &arr)
	{
		return *this;
	}
	Dispose();
	m_pData = arr.m_pData;
	m_nSize = arr.m_nSize;
	arr.m_pData = GNULL;
	arr.m_nSize = 0;
	return *this;
}

template <typename DataT>
gbool GDynamicArray<DataT>::operator==(const GDynamicArray<DataT> &arr)
{
	if (this == &arr)
	{
		return true;
	}
	gsize size = Size();
	if (size != arr.Size())
	{
		return false;
	}
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) != arr.GetAt(i))
		{
			return false;
		}
	}
	return true;
}

template <typename DataT>
GINLINE guint GDynamicArray<DataT>::ClassCode() const
{
	return GDynamicArray<DataT>::CLASS_CODE;
}

template <typename DataT>
GINLINE gbool GDynamicArray<DataT>::Serializable() const
{
	return true;
}

template <typename DataT>
template<typename ArchiveT> 
GINLINE gbool GDynamicArray<DataT>::Serialize(ArchiveT &archive) const
{
	if (!archive.Input())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	gsize size = Size();
	archive << size;

	GSerializeF<ArchiveT, DataT> fSerialize;
	for (gsize i = 0; i < size; i++)
	{
		if (!fSerialize(GetAt(i), archive))
		{
			return false;
		}
	}

	return true;
}

template <typename DataT>
template<typename ArchiveT> 
GINLINE gbool GDynamicArray<DataT>::Deserialize(ArchiveT &archive)
{
	if (!archive.Output())
	{
		return false;
	}
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	gsize size = 0;
	archive >> size;
	Dispose(); // 清空所有数据
	if (!Resize(size))
	{
		return false;
	}

	GDeserializeF<ArchiveT, DataT> fDeserialize;
	for (gsize i = 0; i < size; i++)
	{
		if (!fDeserialize(GetAt(i), archive))
		{
			return false;
		}
	}

	return true;
}

#endif // _CORE_DYNAMIC_ARRAY_INLINE_