#ifndef _CORE_DYNAMIC_ARRAY_INLINE_
#define _CORE_DYNAMIC_ARRAY_INLINE_

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::ArrayCopy(const CsDynamicArray<DataT> &src, cs_size_t start, cs_size_t len,
	CsDynamicArray<DataT> &dst, cs_size_t first)
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
	for (cs_size_t i = start, cs_size_t j = first;
		i < len + start; i++, j++)
	{
		dst[j] = src[i];
	}
}

template <typename DataT>
inline CsDynamicArray<DataT>::CsDynamicArray()
: m_pData(NULL), m_nSize(0)
{

}

template <typename DataT>
inline CsDynamicArray<DataT>::CsDynamicArray(cs_size_t size)
: m_pData(NULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)CsMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
}

template <typename DataT>
inline CsDynamicArray<DataT>::CsDynamicArray(cs_size_t size, const DataT &data)
: m_pData(NULL), m_nSize(size)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)CsMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (cs_size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i] = data;
	}
}

template <typename DataT>
inline CsDynamicArray<DataT>::CsDynamicArray(const CsDynamicArray<DataT> &tArray)
: m_pData(NULL), m_nSize(tArray.m_nSize)
{
	if (m_nSize <= 0)
	{
		return;
	}
	m_pData = (DataT *)CsMalloc(m_nSize * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (cs_size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i] = tArray[i];
	}
}

template <typename DataT>
inline CsDynamicArray<DataT>::CsDynamicArray(const CsArray<DataT> &array, cs_size_t start, cs_size_t size)
: m_pData(NULL), m_nSize(size)
{
	if (size <= 0 || start >= array.Size())
	{
		m_nSize = 0;
		return;
	}
	m_pData = (DataT *)CsMalloc(size * sizeof(DataT));
	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}
	for (cs_size_t i = 0; i < size; i++)
	{
		m_pData[i] = array[i + start];
	}
}

template <typename DataT>
inline CsDynamicArray<DataT>::~CsDynamicArray()
{
	Dispose();
}

template <typename DataT>
inline cs_size_t CsDynamicArray<DataT>::Size() const
{
	return m_nSize;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::IsEmpty() const
{
	return m_pData == NULL
		|| m_nSize <= 0;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::Resize(cs_size_t size)
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
		m_pData = (DataT *)CsMalloc(size * sizeof(DataT));
	}
	else
	{
		// 重新分配内存
		m_pData = (DataT *)CsRealloc(m_pData, size * sizeof(DataT));
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
inline cs_bool CsDynamicArray<DataT>::Resize(cs_size_t size, const DataT &data)
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
		m_pData = (DataT *)CsMalloc(size * sizeof(DataT));
	}
	else
	{
		// 重新分配内存
		m_pData = (DataT *)CsRealloc(m_pData, size * sizeof(DataT));
	}

	if (!m_pData)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	cs_size_t old_size(m_nSize);
	m_nSize = size;
	for (cs_size_t i = old_size; i < size; i++)
	{
		m_pData[i] = data;
	}
	return true;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::Resize(cs_size_t new_size, cs_size_t start, cs_size_t size, cs_size_t new_start)
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

	cs_size_t old_size(m_nSize);
	DataT *new_arr = (DataT *)CsMalloc(new_size * sizeof(DataT));
	if (!new_arr)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	if (m_pData && start < old_size)
	{
		// 拷贝旧内存到新的地址
		cs_size_t real_size(size);
		if (start + real_size > old_size)
		{
			real_size = old_size - start;
		}
		if (new_start + real_size > new_size)
		{
			real_size = new_size - new_start;
		}
		CsMemCopy(new_arr + new_start, m_pData + start, real_size * sizeof(DataT));
	}
	if (m_pData)
	{
		CsFree(m_pData);
	}
	m_pData = new_arr;
	m_nSize = new_size;
	return true;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::Resize(cs_size_t new_size, cs_size_t start, cs_size_t size, cs_size_t new_start, const DataT &data)
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

	cs_size_t old_size(m_nSize);
	DataT *new_arr = (DataT *)CsMalloc(new_size * sizeof(DataT));
	if (!new_arr)
	{
		m_nSize = 0;
		throw std::bad_alloc();
	}

	if (m_pData && start < old_size)
	{
		// 拷贝旧内存到新的地址
		cs_size_t real_size(size);
		if (start + real_size > old_size)
		{
			real_size = old_size - start;
		}
		if (new_start + real_size > new_size)
		{
			real_size = new_size - new_start;
		}
		CsMemCopy(new_arr + new_start, m_pData + start, real_size * sizeof(DataT));
	}
	if (m_pData)
	{
		CsFree(m_pData);
	}

	m_pData = new_arr;
	m_nSize = new_size;
	for (cs_size_t i = 0; i < new_start; i++)
	{
		m_pData[i] = data;
	}
	for (cs_size_t i = new_start + size; i < new_size; i++)
	{
		m_pData[i] = data;
	}
	return true;
}

template <typename DataT>
inline cs_void CsDynamicArray<DataT>::Dispose()
{
	if (m_pData)
	{
		CsFree(m_pData);
		m_pData = NULL;
	}
	m_nSize = 0;
}

template <typename DataT>
inline DataT &CsDynamicArray<DataT>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline const DataT &CsDynamicArray<DataT>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline DataT &CsDynamicArray<DataT>::operator[](cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline const DataT &CsDynamicArray<DataT>::operator[](cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pData + pos);
}

template <typename DataT>
inline DataT *CsDynamicArray<DataT>::operator+=(cs_size_t pos)
{
	return m_pData + pos;
}

template <typename DataT>
inline const DataT *CsDynamicArray<DataT>::operator+=(cs_size_t pos) const
{
	return m_pData + pos;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::RemoveAt(cs_size_t id)
{
	if (IsEmpty())
	{
		return false;
	}
	cs_size_t len = m_nSize - 1;
	if (len < id)
	{
		return false;
	}
	if (len == 0)
	{
		Dispose();
		return true;
	}
	DataT *pData = (DataT *)CsMalloc(len * sizeof(DataT));
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
	CsFree(pData);
	pData = NULL;
	return false;
}

template <typename DataT>
inline CsDynamicArray<DataT> &CsDynamicArray<DataT>::operator=(const CsDynamicArray<DataT> &arr)
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
		m_pData = (DataT *)CsMalloc(arr.m_nSize * sizeof(DataT));
		if (!m_pData)
		{
			throw std::bad_alloc();
		}
		m_nSize = arr.m_nSize;
	}
	for (cs_size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i] = arr.m_pData[i];
	}
	return *this;
}

template <typename DataT>
cs_bool CsDynamicArray<DataT>::operator==(const CsDynamicArray<DataT> &arr)
{
	if (this == &arr)
	{
		return true;
	}
	cs_size_t size = Size();
	if (size != arr.Size())
	{
		return false;
	}
	for (cs_size_t i = 0; i < size; i++)
	{
		if (GetAt(i) != arr.GetAt(i))
		{
			return false;
		}
	}
	return true;
}

template <typename DataT>
inline cs_uint CsDynamicArray<DataT>::ClassCode() const
{
	return CsDynamicArray<DataT>::CLASS_CODE;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::Serializable() const
{
	return true;
}

template <typename DataT>
template<typename ArchiveT> 
inline cs_bool CsDynamicArray<DataT>::Serialize(ArchiveT &archive) const
{
	if (!archive.Input())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	cs_size_t size = Size();
	archive << size;

	CsSerializeF<ArchiveT, DataT> fSerialize;
	for (cs_size_t i = 0; i < size; i++)
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
inline cs_bool CsDynamicArray<DataT>::Deserialize(ArchiveT &archive)
{
	if (!archive.Output())
	{
		return false;
	}
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	cs_size_t size = 0;
	archive >> size;
	Dispose(); // 清空所有数据
	if (!Resize(size))
	{
		return false;
	}

	CsDeserializeF<ArchiveT, DataT> fDeserialize;
	for (cs_size_t i = 0; i < size; i++)
	{
		if (!fDeserialize(GetAt(i), archive))
		{
			return false;
		}
	}

	return true;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::CopyMemoryFrom(cs_size_t first, cs_size_t len,
	const DataT *pData, cs_size_t start)
{
	if (!pData || !m_pData
		|| first >= m_nSize || len + first > m_nSize)
	{
		return false;
	}
	CsMemCopy(m_pData + first, pData + start, sizeof(DataT)* len);
	return true;
}

template <typename DataT>
inline cs_bool CsDynamicArray<DataT>::CopyMemoryTo(cs_size_t start, cs_size_t len,
	DataT *pData, cs_size_t first = 0) const
{
	if (!pData || !m_pData
		|| start >= m_nSize || len + start > m_nSize)
	{
		return false;
	}
	CsMemCopy(pData + first, m_pData + start, sizeof(DataT)* len);
	return true;
}

#endif // _CORE_DYNAMIC_ARRAY_INLINE_