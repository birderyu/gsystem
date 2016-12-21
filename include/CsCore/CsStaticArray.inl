#ifndef _CORE_STATIC_ARRAY_INLINE_
#define _CORE_STATIC_ARRAY_INLINE_

template <typename DataT, cs_size_t ARRAY_SIZE>
inline CsStaticArray<DataT, ARRAY_SIZE>::CsStaticArray()
{

}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline CsStaticArray<DataT, ARRAY_SIZE>::CsStaticArray(const DataT &data)
{
	for (cs_size_t i = 0; i < ARRAY_SIZE; i++)
	{
		m_pData[i] = data;
	}
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline cs_size_t CsStaticArray<DataT, ARRAY_SIZE>::Size() const
{
	return ARRAY_SIZE;
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline DataT & CsStaticArray<DataT, ARRAY_SIZE>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline DataT CsStaticArray<DataT, ARRAY_SIZE>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline DataT &CsStaticArray<DataT, ARRAY_SIZE>::operator[](cs_size_t pos)
{
	CS_ASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline DataT CsStaticArray<DataT, ARRAY_SIZE>::operator[](cs_size_t pos) const
{
	CS_ASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline cs_uint CsStaticArray<DataT, ARRAY_SIZE>::ClassCode() const
{
	return CsStaticArray<DataT, ARRAY_SIZE>::CLASS_CODE;
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline cs_bool CsStaticArray<DataT, ARRAY_SIZE>::Serializable() const
{
	return true;
}

template <typename DataT, cs_size_t ARRAY_SIZE>
template <typename ArchiveT>
inline cs_bool CsStaticArray<DataT, ARRAY_SIZE>::Serialize(ArchiveT &archive) const
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

template <typename DataT, cs_size_t ARRAY_SIZE>
template <typename ArchiveT>
inline cs_bool CsStaticArray<DataT, ARRAY_SIZE>::Deserialize(ArchiveT &archive)
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
	if (size != Size())
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

#endif // _CORE_STATIC_ARRAY_INLINE_