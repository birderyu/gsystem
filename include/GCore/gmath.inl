#ifndef _CORE_MATH_INLINE_
#define _CORE_MATH_INLINE_

template<typename ValueT>
GINLINE ValueT GMath::Max(const ValueT &v1, const ValueT &v2)
{
	return v1 > v2 ? v1 : v2;
}

template<typename ValueT>
GINLINE ValueT GMath::Min(const ValueT &v1, const ValueT &v2)
{
	return v1 < v2 ? v1 : v2;
}

#endif // _CORE_MATH_INLINE_