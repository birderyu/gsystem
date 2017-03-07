#ifndef _CORE_STATIC_ARRAY_INLINE_
#define _CORE_STATIC_ARRAY_INLINE_

template <typename DataT, gsize ARRAY_SIZE>
inline GStaticArray<DataT, ARRAY_SIZE>::GStaticArray()
{

}

template <typename DataT, gsize ARRAY_SIZE>
inline GStaticArray<DataT, ARRAY_SIZE>::GStaticArray(const DataT &data)
{
	for (gsize i = 0; i < ARRAY_SIZE; i++)
	{
		// ·ÅÖÃ¹¹Ôì
		new(m_pData + i)DataT(data);
	}
}

template <typename DataT, gsize ARRAY_SIZE>
inline gsize GStaticArray<DataT, ARRAY_SIZE>::Size() const
{
	return ARRAY_SIZE;
}

template <typename DataT, gsize ARRAY_SIZE>
inline gbool GStaticArray<DataT, ARRAY_SIZE>::IsEmpty() const
{
	return ARRAY_SIZE == 0;
}

template <typename DataT, gsize ARRAY_SIZE>
inline DataT &GStaticArray<DataT, ARRAY_SIZE>::GetAt(gsize pos)
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, gsize ARRAY_SIZE>
inline const DataT &GStaticArray<DataT, ARRAY_SIZE>::GetAt(gsize pos) const
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, gsize ARRAY_SIZE>
inline DataT &GStaticArray<DataT, ARRAY_SIZE>::operator[](gsize pos)
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, gsize ARRAY_SIZE>
inline const DataT &GStaticArray<DataT, ARRAY_SIZE>::operator[](gsize pos) const
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, gsize ARRAY_SIZE>
inline DataT *GStaticArray<DataT, ARRAY_SIZE>::operator+=(gsize pos)
{
	return m_pData + pos;
}

template <typename DataT, gsize ARRAY_SIZE>
inline const DataT *GStaticArray<DataT, ARRAY_SIZE>::operator+=(gsize pos) const
{
	return m_pData + pos;
}

template <typename DataT, gsize ARRAY_SIZE>
inline guint GStaticArray<DataT, ARRAY_SIZE>::ClassCode() const
{
	return GStaticArray<DataT, ARRAY_SIZE>::CLASS_CODE;
}

template <typename DataT, gsize ARRAY_SIZE>
inline gbool GStaticArray<DataT, ARRAY_SIZE>::Serializable() const
{
	return true;
}

template <typename DataT, gsize ARRAY_SIZE>
template <typename ArchiveT>
inline gbool GStaticArray<DataT, ARRAY_SIZE>::Serialize(ArchiveT &archive) const
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

template <typename DataT, gsize ARRAY_SIZE>
template <typename ArchiveT>
inline gbool GStaticArray<DataT, ARRAY_SIZE>::Deserialize(ArchiveT &archive)
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
	if (size != Size())
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

#endif // _CORE_STATIC_ARRAY_INLINE_