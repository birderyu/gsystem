#ifndef _CORE_DYNAMIC_ARRAY_INLINE_
#define _CORE_DYNAMIC_ARRAY_INLINE_

template <typename DataT>
inline gbool GDynamicArray<DataT>::ArrayCopy(const GDynamicArray<DataT> &src, gsize start, gsize len,
	GDynamicArray<DataT> &dst, gsize first)
{
	if (len + start > src.Size())
	{
		return false;
	}
	if (len + first > dst.Size())
	{
		dst.Resize(len + first);
	}
	//return src.CopyMemTo(dst.GetData() + first, start, len);
	for (gsize i = start, gsize j = first;
		i < len + start; i++, j++)
	{
		dst[j] = src[i];
	}
}

template <typename DataT>
inline GDynamicArray<DataT>::GDynamicArray()
: m_pData(NULL), m_nSize(0)
{

}

template <typename DataT>
inline GDynamicArray<DataT>::GDynamicArray(gsize size)
: m_pData(NULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)GMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
}

template <typename DataT>
inline GDynamicArray<DataT>::GDynamicArray(gsize size, const DataT &data)
: m_pData(NULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)GMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (gsize i = 0; i < m_nSize; i++)
	{
		m_pData[i] = data;
	}
}

template <typename DataT>
inline GDynamicArray<DataT>::GDynamicArray(const GDynamicArray<DataT> &tArray)
: m_pData(NULL), m_nSize(tArray.m_nSize)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)GMalloc(m_nSize * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (gsize i = 0; i < m_nSize; i++)
	{
		m_pData[i] = tArray[i];
	}
}

template <typename DataT>
inline GDynamicArray<DataT>::GDynamicArray(const GArray<DataT> &array, gsize start, gsize size)
: m_pData(NULL), m_nSize(size)
{
	if (size <= 0 || start >= array.Size())
	{
		m_nSize = 0;
		return;
	}
	m_pData = (DataT *)GMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (gsize i = 0; i < size; i++)
	{
		m_pData[i] = array[i + start];
	}
}

template <typename DataT>
inline GDynamicArray<DataT>::~GDynamicArray()
{
	Dispose();
}

template <typename DataT>
inline gsize GDynamicArray<DataT>::Size() const
{
	return m_nSize;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::IsEmpty() const
{
	return m_pData == NULL
		|| m_nSize <= 0;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::Resize(gsize size)
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

	if (!m_pData)
	{
		m_pData = (DataT *)GMalloc(size * sizeof(DataT));
	}
	else
	{
		// 重新分配内存
		m_pData = (DataT *)GRealloc(m_pData, size * sizeof(DataT));
	}

	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	m_nSize = size;
	return true;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::Resize(gsize size, const DataT &data)
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

	if (!m_pData)
	{
		m_pData = (DataT *)GMalloc(size * sizeof(DataT));
	}
	else
	{
		// 重新分配内存
		m_pData = (DataT *)GRealloc(m_pData, size * sizeof(DataT));
	}

	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	gsize old_size(m_nSize);
	m_nSize = size;
	for (gsize i = old_size; i < size; i++)
	{
		m_pData[i] = data;
	}
	return true;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start)
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

	gsize old_size(m_nSize);
	DataT *new_arr = (DataT *)GMalloc(new_size * sizeof(DataT));
	if (!new_arr)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	if (m_pData && start < old_size)
	{
		// 拷贝旧内存到新的地址
		gsize real_size(size);
		if (start + real_size > old_size)
		{
			real_size = old_size - start;
		}
		if (new_start + real_size > new_size)
		{
			real_size = new_size - new_start;
		}
		GMemCopy(new_arr + new_start, m_pData + start, real_size * sizeof(DataT));
	}
	if (m_pData)
	{
		GFree(m_pData);
	}
	m_pData = new_arr;
	m_nSize = new_size;
	return true;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::Resize(gsize new_size, gsize start, gsize size, gsize new_start, const DataT &data)
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

	gsize old_size(m_nSize);
	DataT *new_arr = (DataT *)GMalloc(new_size * sizeof(DataT));
	if (!new_arr)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	if (m_pData && start < old_size)
	{
		// 拷贝旧内存到新的地址
		gsize real_size(size);
		if (start + real_size > old_size)
		{
			real_size = old_size - start;
		}
		if (new_start + real_size > new_size)
		{
			real_size = new_size - new_start;
		}
		GMemCopy(new_arr + new_start, m_pData + start, real_size * sizeof(DataT));
	}
	if (m_pData)
	{
		GFree(m_pData);
	}

	m_pData = new_arr;
	m_nSize = new_size;
	for (gsize i = 0; i < new_start; i++)
	{
		m_pData[i] = data;
	}
	for (gsize i = new_start + size; i < new_size; i++)
	{
		m_pData[i] = data;
	}
	return true;
}

template <typename DataT>
inline gvoid GDynamicArray<DataT>::Dispose()
{
	if (m_pData)
	{
		GFree(m_pData);
		m_pData = NULL;
	}
	m_nSize = 0;
}

template <typename DataT>
inline DataT &GDynamicArray<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline const DataT &GDynamicArray<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline DataT &GDynamicArray<DataT>::operator[](gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline const DataT &GDynamicArray<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline DataT *GDynamicArray<DataT>::operator+=(gsize pos)
{
	return m_pData + pos;
}

template <typename DataT>
inline const DataT *GDynamicArray<DataT>::operator+=(gsize pos) const
{
	return m_pData + pos;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::RemoveAt(gsize id)
{
	if (IsEmpty())
	{
		return false;
	}
	gsize len = m_nSize - 1;
	if (len < id)
	{
		return false;
	}
	if (len == 0)
	{
		Dispose();
		return true;
	}
	DataT *pData = (DataT *)GMalloc(len * sizeof(DataT));
	if (!pData)
	{
		return false;
	}
	if (CopyMemoryTo(0, id, pData, 0))
	{
		if (CopyMemoryTo(id + 1, len - id, pData, id))
		{
			Dispose();
			m_pData = pData;
			m_nSize = len;
			return true;
		}
	}
	GFree(pData);
	pData = NULL;
	return false;
}

template <typename DataT>
inline GDynamicArray<DataT> &GDynamicArray<DataT>::operator=(const GDynamicArray<DataT> &arr)
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
	if (m_nSize != arr.m_nSize)
	{
		m_pData = (DataT *)GMalloc(arr.m_nSize * sizeof(DataT));
		if (!m_pData)
		{
			throw std::bad_alloc();
		}
		m_nSize = arr.m_nSize;
	}
	for (gsize i = 0; i < m_nSize; i++)
	{
		m_pData[i] = arr.m_pData[i];
	}
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
inline guint GDynamicArray<DataT>::ClassCode() const
{
	return GDynamicArray<DataT>::CLASS_CODE;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::Serializable() const
{
	return true;
}

template <typename DataT>
template<typename ArchiveT> 
inline gbool GDynamicArray<DataT>::Serialize(ArchiveT &archive) const
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
inline gbool GDynamicArray<DataT>::Deserialize(ArchiveT &archive)
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

template <typename DataT>
inline gbool GDynamicArray<DataT>::CopyMemoryFrom(gsize first, gsize len,
	const DataT *pData, gsize start)
{
	if (!pData || !m_pData
		|| first >= m_nSize || len + first > m_nSize)
	{
		return false;
	}
	GMemCopy(m_pData + first, pData + start, sizeof(DataT)* len);
	return true;
}

template <typename DataT>
inline gbool GDynamicArray<DataT>::CopyMemoryTo(gsize start, gsize len,
	DataT *pData, gsize first = 0) const
{
	if (!pData || !m_pData
		|| start >= m_nSize || len + start > m_nSize)
	{
		return false;
	}
	GMemCopy(pData + first, m_pData + start, sizeof(DataT)* len);
	return true;
}

#endif // _CORE_DYNAMIC_ARRAY_INLINE_