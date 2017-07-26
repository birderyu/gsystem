#ifndef _CORE_FUNCTOR_INLINE_
#define _CORE_FUNCTOR_INLINE_

#include "gmemory.h"

namespace gsystem { // gsystem

template<typename T> GINLINE
gbool GEqualToF<T>::operator()(const T &left, const T &right) const
{
	return (left == right);
}

template<typename T> GINLINE
gbool GLessThanF<T>::operator()(const T &left, const T &right) const
{
	return (left < right);
}

template<typename T> GINLINE
gbool GGreaterThanF<T>::operator()(const T &left, const T &right) const
{
	return (left > right);
}

template<typename T> GINLINE
gbool GLessThanOrEqualToF<T>::operator()(const T &left, const T &right) const
{
	return (left <= right);
}

template<typename T> GINLINE
gbool GGreaterThanOrEqualToF<T>::operator()(const T &left, const T &right) const
{
	return (left >= right);
}

template<typename T> GINLINE
gint GCompareToF<T>::operator()(const T &left, const T &right) const
{
	if (left < right)
	{
		return -1;
	}
	else if (left > right)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T> GINLINE
gbool GLeftOpenRightOpenF<T>::operator()(const T &key, const T &left, const T &right) const
{
	return key > left && key < right;
}

template<typename T> GINLINE
gbool GLeftClosedRightClosedF<T>::operator()(const T &key, const T &left, const T &right) const
{
	return key >= left && key <= right;
}

template<typename T> GINLINE
gbool GLeftOpenRightClosedF<T>::operator()(const T &key, const T &left, const T &right) const
{
	return key > left && key <= right;
}

template<typename T> GINLINE
gbool GLeftClosedRightOpenF<T>::operator()(const T &key, const T &left, const T &right) const
{
	return key >= left && key < right;
}

template<typename T, gsize SIZE> GINLINE
gbool GFastEqualToF<T, SIZE>::operator()(const T &left, const T &right) const
{
	return GMemCmp(&left, &right, SIZE) == 0;
}

} // namespace gsystem

#endif // _CORE_FUNCTOR_INLINE_
