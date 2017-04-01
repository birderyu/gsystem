#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

namespace gsystem { // gsystem

template <typename DataT> GINLINE
DataT &GArray<DataT>::First()
{
	GASSERT(!IsEmpty());
	return GetAt(0);
}

template <typename DataT> GINLINE
const DataT &GArray<DataT>::First() const
{
	GASSERT(!IsEmpty());
	return GetAt(0);
}

template <typename DataT> GINLINE
DataT &GArray<DataT>::Last()
{
	GASSERT(!IsEmpty());
	return GetAt(Size() - 1);
}

template <typename DataT> GINLINE
const DataT &GArray<DataT>::Last() const
{
	GASSERT(!IsEmpty());
	return GetAt(Size() - 1);
}

template <typename DataT> GINLINE
DataT *GArray<DataT>::FirstCursor()
{
	return CursorAt(0);
}

template <typename DataT> GINLINE
const DataT *GArray<DataT>::FirstCursor() const
{
	return CursorAt(0);
}

template <typename DataT> GINLINE
DataT *GArray<DataT>::LastCursor()
{
	GASSERT(!IsEmpty());
	return CursorAt(Size() - 1);
}

template <typename DataT> GINLINE
const DataT *GArray<DataT>::LastCursor() const
{
	GASSERT(!IsEmpty());
	return CursorAt(Size() - 1);
}

template <typename DataT>
GINLINE gbool GArray<DataT>::Contains(const DataT &data) const
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
GINLINE gsize GArray<DataT>::FirstIndexOf(const DataT &data) const
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
GINLINE gsize GArray<DataT>::LastIndexOf(const DataT &data) const
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
GINLINE gsize GArray<DataT>::CountOf(const DataT &data) const
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
GINLINE guint GArray<DataT>::ClassCode() const
{
	return GArray<DataT>::CLASS_CODE;
}

}  // namespace gsystem

#endif // _CORE_ARRAY_INLINE_