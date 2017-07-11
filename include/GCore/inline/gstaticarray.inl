#ifndef _CORE_STATIC_ARRAY_INLINE_
#define _CORE_STATIC_ARRAY_INLINE_

namespace gsystem { // gsystem

template <typename DataT, gsize ARRAY_SIZE>
GINLINE GStaticArray<DataT, ARRAY_SIZE>::GStaticArray()
{

}

template <typename DataT, gsize ARRAY_SIZE>
GINLINE GStaticArray<DataT, ARRAY_SIZE>::GStaticArray(const DataT &data)
{
	for (gsize i = 0; i < ARRAY_SIZE; i++)
	{
		// ·ÅÖÃ¹¹Ôì
		new(m_pData + i)DataT(data);
	}
}

template <typename DataT, gsize ARRAY_SIZE>
GINLINE gsize GStaticArray<DataT, ARRAY_SIZE>::Size() const
{
	return ARRAY_SIZE;
}

template <typename DataT, gsize ARRAY_SIZE>
GINLINE gbool GStaticArray<DataT, ARRAY_SIZE>::IsEmpty() const
{
	return ARRAY_SIZE == 0;
}

template <typename DataT, gsize ARRAY_SIZE>
GINLINE DataT &GStaticArray<DataT, ARRAY_SIZE>::GetAt(gsize pos)
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

template <typename DataT, gsize ARRAY_SIZE>
GINLINE const DataT &GStaticArray<DataT, ARRAY_SIZE>::GetAt(gsize pos) const
{
	GASSERT(pos < ARRAY_SIZE);
	return m_pData[pos];
}

} // namespace gsystem

#endif // _CORE_STATIC_ARRAY_INLINE_