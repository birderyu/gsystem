#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

template <typename DataT>
inline gbool GArray<DataT>::Contains(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return true;
		}
	}
	return false;
}

template <typename DataT>
inline gsize GArray<DataT>::FirstIndexOf(const DataT &) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return i;
		}
	}
	return NULL_POS;
}

template <typename DataT>
inline gsize GArray<DataT>::LastIndexOf(const DataT &) const
{
	gsize size = Size();
	for (gsize i = size; i > 0; i--)
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
inline gsize GArray<DataT>::CountOf(const DataT &) const
{
	gsize size = Size();
	gsize count = 0;
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			count++;
		}
	}
	return count;
}

template <typename DataT>
inline guint GArray<DataT>::ClassCode() const
{
	return GArray<DataT>::CLASS_CODE;
}

#endif // _CORE_ARRAY_INLINE_