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
inline DataT & CsStaticArray<DataT, ARRAY_SIZE>::GetAt(cs_size_t i)
{
	CS_ASSERT(i < ARRAY_SIZE);
	return m_pData[i];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline const DataT & CsStaticArray<DataT, ARRAY_SIZE>::GetAt(cs_size_t i) const
{
	CS_ASSERT(i < ARRAY_SIZE);
	return m_pData[i];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline DataT &CsStaticArray<DataT, ARRAY_SIZE>::operator[](cs_size_t i)
{
	CS_ASSERT(i < ARRAY_SIZE);
	return m_pData[i];
}

template <typename DataT, cs_size_t ARRAY_SIZE>
inline const DataT &CsStaticArray<DataT, ARRAY_SIZE>::operator[](cs_size_t i) const
{
	CS_ASSERT(i < ARRAY_SIZE);
	return m_pData[i];
}

#endif // _CORE_STATIC_ARRAY_INLINE_