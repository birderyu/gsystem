#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

template <typename DataT>
inline cs_bool CsArray<DataT>::Contains(const DataT &data) const
{
	cs_size_t size = Size();
	for (cs_size_t i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return true;
		}
	}
	return false;
}

template <typename DataT>
inline cs_size_t CsArray<DataT>::FirstIndexOf(const DataT &) const
{
	cs_size_t size = Size();
	for (cs_size_t i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return i;
		}
	}
	return NULL_POS;
}

template <typename DataT>
inline cs_size_t CsArray<DataT>::LastIndexOf(const DataT &) const
{
	cs_size_t size = Size();
	for (cs_size_t i = size; i > 0; i--)
	{
		// 注意不能让i减到0
		if (GetAt(i - 1) == data)
		{
			return i - 1;
		}
	}
	return NULL_POS;
}

template <typename DataT>
inline cs_size_t CsArray<DataT>::CountOf(const DataT &) const
{
	cs_size_t size = Size();
	cs_size_t count = 0;
	for (cs_size_t i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			count++;
		}
	}
	return count;
}

template <typename DataT>
inline cs_uint CsArray<DataT>::ClassCode() const
{
	return CsArray<DataT>::CLASS_CODE;
}

#endif // _CORE_ARRAY_INLINE_