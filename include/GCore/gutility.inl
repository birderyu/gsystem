#ifndef _CORE_UTILITY_INLINE_
#define _CORE_UTILITY_INLINE_

namespace gnova { // gnova
namespace detail { // gnova.detail
namespace utility { // gnova.detail.utility

/// 算数类型，直接使用值拷贝交换操作
template<typename T>
GINLINE gvoid GSwap(T& a, T& b, GTrueType)
{
	T t(a);
	a = b;
	b = t;
}

/// 非算数类型，优先使用移动操作
template<typename T>
GINLINE gvoid GSwap(T& a, T& b, GFalseType)
{
	T t(GMove(a));
	a = GMove(b);
	b = GMove(t);
}

} // namespace gnova.detail.utility
} // namespace gnova.detail
} // namespace gnova

namespace gnova { // gnova

template<typename T>
GINLINE typename GRemoveReference<T>::Type &&GMove(T &&t)
{
	using rtype = typename GRemoveReference<T>::Type&&;
	return static_cast<rtype>(t);
}

template<typename T>
GINLINE T &&GForward(typename GRemoveReference<T>::Type &t)
{
	return static_cast<T &&>(t);
}

template<typename T>
GINLINE T &&GForward(typename GRemoveReference<T>::Type &&t)
{
	return static_cast<T &&>(t);
}

template<typename T> 
GINLINE gvoid GSwap(T &a, T &b)
{
	detail::utility::GSwap(a, b,
		GTypeTraits<T>::Arithmetic())
}

} // namespace gnova

#endif // _CORE_UTILITY_INLINE_
