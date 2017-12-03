#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

#include "gmath.h"

namespace gsystem { // gsystem

template<typename T> GINLINE
T &GArray<T>::First()
{
	GASSERT(!IsEmpty());
	return GetAt(0);
}

template<typename T> GINLINE
const T &GArray<T>::First() const
{
	GASSERT(!IsEmpty());
	return GetAt(0);
}

template<typename T> GINLINE
T &GArray<T>::Last()
{
	GASSERT(!IsEmpty());
	return GetAt(Size() - 1);
}

template<typename T> GINLINE
const T &GArray<T>::Last() const
{
	GASSERT(!IsEmpty());
	return GetAt(Size() - 1);
}

template<typename T> GINLINE
T *GArray<T>::FirstCursor()
{
	return CursorAt(0);
}

template<typename T> GINLINE
const T *GArray<T>::FirstCursor() const
{
	return CursorAt(0);
}

template<typename T> GINLINE
T *GArray<T>::LastCursor()
{
	GASSERT(!IsEmpty());
	return CursorAt(Size() - 1);
}

template<typename T> GINLINE
const T *GArray<T>::LastCursor() const
{
	GASSERT(!IsEmpty());
	return CursorAt(Size() - 1);
}

template<typename T>
GINLINE gbool GArray<T>::Contains(const T &value) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == value)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
GINLINE gsize GArray<T>::FirstIndexOf(const T &value) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == value)
		{
			return i;
		}
	}
	return NULL_POS;
}

template<typename T>
GINLINE gsize GArray<T>::LastIndexOf(const T &value) const
{
	gsize size = Size();
	for (gsize i = size; i > 0; i--)
	{
		// 注意不能让i减到0
		if (GetAt(i - 1) == value)
		{
			return i - 1;
		}
	}
	return NULL_POS;
}

template<typename T>
GINLINE gsize GArray<T>::CountOf(const T &value) const
{
	gsize size = Size();
	gsize count = 0;
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == value)
		{
			count++;
		}
	}
	return count;
}

template<typename T>
GINLINE gvoid GArray<T>::Shuffle() 
{
	// Fisher Yates
	if (IsEmpty()) 
	{
		return;
	}
	gsize i = Size();
	while (--i)
	{
		gsize j = GMath::Rand() % (i + 1);
		GSwap(GetAt(i), GetAt(j));
	}
}

template<typename T> GINLINE
T &GArray<T>::operator[](gsize pos)
{
	return GetAt(pos);
}

template<typename T> GINLINE
const T &GArray<T>::operator[](gsize pos) const
{
	return GetAt(pos);
}

}  // namespace gsystem

#endif // _CORE_ARRAY_INLINE_