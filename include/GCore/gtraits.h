/// 萃取器
/// 参考<type_traits.h>中的定义和写法

#ifndef _CORE_TRAITS_H_
#define _CORE_TRAITS_H_

#include "gtype.h"
#include <type_traits>

template<typename ClassT, ClassT DefValue>
struct GIntegralConstant
{
	static const ClassT value = DefValue;

	typedef ClassT ValueType;
	typedef GIntegralConstant<ClassT, DefValue> Type;

	operator ValueType() const
	{
		return (value);
	}
};

typedef GIntegralConstant<gbool, true>	GTrueType;
typedef GIntegralConstant<gbool, false> GFalseType;

template<gbool>
struct GCatBase
	: GFalseType{};

template<>
struct GCatBase<true>
	: GTrueType{};

template<typename T>
struct GTypeTraits
{
	typedef const T &ParameterType;
	typedef GFalseType TrivialDefaultConstructible;
	typedef GFalseType TrivialCopyConstructible;
	typedef GFalseType TrivialMoveConstructible;
	typedef GFalseType TrivialDestructible;
	typedef GFalseType Arithmetic;
};

template<>
struct GTypeTraits<gbool>
{
	typedef gbool ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gchar>
{
	typedef gchar ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gschar>
{
	typedef gschar ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<guchar>
{
	typedef guchar ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gwchar>
{
	typedef gwchar ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gshort>
{
	typedef gshort ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gushort>
{
	typedef gushort ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gint>
{
	typedef gint ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<guint>
{
	typedef guint ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<glong>
{
	typedef glong ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gulong>
{
	typedef gulong ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<glonglong>
{
	typedef glonglong ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gulonglong>
{
	typedef gulonglong ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gfloat>
{
	typedef gfloat ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<gdouble>
{
	typedef gdouble ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<>
struct GTypeTraits<glongdouble>
{
	typedef glongdouble ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

// 若T为原生指针，则采用下面的实现
template<typename T>
struct GTypeTraits<T*>
{
	typedef T* ParameterType;
	typedef GTrueType TrivialDefaultConstructible;
	typedef GTrueType TrivialCopyConstructible;
	typedef GTrueType TrivialMoveConstructible;
	typedef GTrueType TrivialDestructible;
	typedef GTrueType Arithmetic;
};

template<typename T1, typename T2>
struct GIsSame
	: GFalseType
{
};

template<typename T1>
struct GIsSame<T1, T1>
	: GTrueType
{
};

/// 移除类型中的const
template<typename T>
struct GRemoveConst
{
	typedef T Type;
};

template<typename T>
struct GRemoveConst<const T>
{	
	typedef T Type;
};

template<typename T>
struct GRemoveConst<const T[]>
{
	typedef T Type[];
};

template<typename T, gsize N>
struct GRemoveConst<const T[N]>
{
	typedef T Type[N];
};

/// 移除类型中的volatile
template<typename T>
struct GRemoveVolatile
{
	typedef T Type;
};

template<typename T>
struct GRemoveVolatile<volatile T>
{
	typedef T Type;
};

template<typename T>
struct GRemoveVolatile<volatile T[]>
{
	typedef T Type[];
};

template<typename T, gsize N>
struct GRemoveVolatile<volatile T[N]>
{
	typedef T Type[N];
};

/// 移除类型中的const和volatile
template<typename T>
struct GRemoveConstVolatile
{
	typedef typename GRemoveConst<typename GRemoveVolatile<T>::Type>::Type Type;
};

/// 移除类型中的引用
template<typename T>
struct GRemoveReference
{
	typedef T Type;
};

template<typename T>
struct GRemoveReference<T&>
{
	typedef T Type;
};

template<typename T>
struct GRemoveReference<T&&>
{
	typedef T Type;
};

/// 移除类型中的指针
template<typename T>
struct GRemovePointer
{
	typedef T Type;
};

template<typename T>
struct GRemovePointer<T*>
{
	typedef T Type;
};

/// 移除数组，仅保留类型
template<typename T>
struct GRemoveExtent
{
	typedef T Type;
};

template<typename T, gsize N>
struct GRemoveExtent<T[N]>
{
	typedef T Type;
};

template<typename T>
struct GRemoveExtent<T[]>
{	
	typedef T Type;
};

/// 条件判断
template<gbool TEST,
	typename T1, typename T2>
struct GConditional
{
	typedef T2 Type;
};

template<typename T1, typename T2>
struct GConditional<true, T1, T2>
{
	typedef T1 Type;
};

/// 是否是数组
template<typename T>
struct GIsArray
	: GFalseType
{
};

template<typename T, gsize N>
struct GIsArray<T[N]>
	: GTrueType
{
};

template<typename T>
struct GIsArray<T[]>
	: GTrueType
{
};

/// 是否是整型
template<typename T>
struct GIsIntegralT
	: GFalseType{};

template<>
struct GIsIntegralT<gbool>
	: GTrueType{};

template<>
struct GIsIntegralT<gchar>
	: GTrueType{};

template<>
struct GIsIntegralT<gschar>
	: GTrueType{};

template<>
struct GIsIntegralT<guchar>
	: GTrueType{};

#ifdef G_HAS_WCHAR
template<>
struct GIsIntegralT<gwchar>
	: GTrueType{};
#endif // G_HAS_WCHAR

template<>
struct GIsIntegralT<gshort>
	: GTrueType{};

template<>
struct GIsIntegralT<gushort>
	: GTrueType{};

template<>
struct GIsIntegralT<gint>
	: GTrueType{};

template<>
struct GIsIntegralT<guint>
	: GTrueType{};

template<>
struct GIsIntegralT<glong>
	: GTrueType{};

template<>
struct GIsIntegralT<gulong>
	: GTrueType{};

template<>
struct GIsIntegralT<glonglong>
	: GTrueType{};

template<>
struct GIsIntegralT<gulonglong>
	: GTrueType{};

template<typename T>
struct GIsIntegral
	: GIsIntegralT<typename GRemoveConstVolatile<T>::Type>{};

/// 是否是浮点型
template<class T>
struct GIsFloatingPointT
	: GFalseType{};

template<>
struct GIsFloatingPointT<gfloat>
	: GTrueType{};

template<>
struct GIsFloatingPointT<gdouble>
	: GTrueType{};

template<>
struct GIsFloatingPointT<glongdouble>
	: GTrueType{};

template<typename T>
struct GIsFloatingPoint
	: GIsFloatingPointT<typename GRemoveConstVolatile<T>::Type>{};

/// 是否是数字类型
template<typename T>
struct GIsNumeric
	: GCatBase<GIsIntegral<T>::value || GIsFloatingPoint<T>::value>{};

/// 是否是算数类型
template<typename T>
struct GIsArithmetic
	: GCatBase<GIsIntegral<T>::value || GIsFloatingPoint<T>::value>{};

template<typename T>
struct GIsPointerT
	: GFalseType
{
};

template<typename T>
struct GIsPointerT<T *>
	: GCatBase<!std::is_member_object_pointer<T *>::value
	&& !std::is_member_function_pointer<T *>::value>
{
};

template<typename T>
struct GIsPointer
	: GIsPointerT<typename GRemoveConstVolatile<T>::Type>
{
};

template<typename T>
struct GAddConst
{
	typedef const T Type;
};

template<typename T>
struct GAddVolatile
{
	typedef volatile T Type;
};

template<typename T>
struct GAddConstVolatile
{
	typedef const volatile T Type;
};

template<typename T>
struct GAddLvalueReference
{
	typedef typename std::_Add_reference<T>::_Lvalue Type;
};

template<typename T>
struct GAddRvalueReference
{
	typedef typename std::_Add_reference<T>::_Rvalue Type;
};

template<typename FromT, typename ToT>
struct GConvertible
	: GCatBase<__is_convertible_to(FromT, ToT)>
{
};

template<typename T, typename... TS>
struct GIsConstructible
	: GCatBase<__is_constructible(T, TS...)>
{
};

template<typename T>
struct GIsDefaultConstructible
	: GIsConstructible<T>::Type
{
};

template<typename T>
struct GIsCopyConstructible
	: GIsConstructible<
		T,
		typename GAddLvalueReference<
			typename GAddConst<T>::Type
		>::Type
	>::Type
{
};

template<typename T>
struct GIsMoveConstructible
	: GIsConstructible<
	T,
	typename GAddRvalueReference<T>::Type
	>::Type
{
};

template<typename ToT, typename FromT>
struct GIsAssignable
	: GCatBase<__is_assignable(ToT, FromT)>
{
};

template<typename T>
struct GIsCopyAssignable
	: GIsAssignable<
		typename GAddLvalueReference<T>::Type,
		typename GAddLvalueReference<
			typename GAddConst<T>::Type
		>::Type
	>::Type
{
};

template<typename T>
struct GIsMoveAssignable
	: GIsAssignable<
		typename std::add_lvalue_reference<T>::type,
		typename std::add_rvalue_reference<T>::type
	>::Type
{
};

template<typename T>
struct GIsVoid
	: GFalseType
{
};

template<>
struct GIsVoid<gvoid>
	: GTrueType
{
};

template<typename T>
struct GIsLvalueReference
	: GFalseType
{
};

template<typename T>
struct GIsLvalueReference<T&>
	: GTrueType
{
};

template<typename T>
struct GIsRvalueReference
	: GFalseType
{
};

template<typename T>
struct GIsRvalueReference<T&&>
	: GTrueType
{
};

template<typename T, typename ...TS>
struct GIsNothrowConstructible
	: GCatBase<__is_nothrow_constructible(T, TS...)>
{
};

template<typename T>
struct GIsNothrowDefaultConstructible
	: GIsNothrowConstructible<T>::Type
{
};

template<typename T>
struct GIsNothrowCopyConstructible
	: GIsNothrowConstructible<
		T,
		typename GAddLvalueReference<
			typename GAddConst<T>::Type
		>::Type
	>::Type
{
};

template<typename T>
struct GIsNothrowMoveConstructible
	: GIsNothrowConstructible<
		T,
		typename GAddRvalueReference<T>::Type
	>::Type
{
};

template<typename T>
struct GIsNothrowDestructible
	: GCatBase<__is_nothrow_destructible(T)>
{
};

template<typename ToT, typename FromT>
struct GIsNothrowAssignable
	: GCatBase<__is_nothrow_assignable(ToT, FromT)>
{
};

template<typename T>
struct GIsNothrowCopyAssignable
	: GIsNothrowAssignable<
		typename GAddLvalueReference<T>::Type,
		typename GAddLvalueReference<
			typename GAddConst<T>::Type
		>::Type
	>::Type
{
};

template<typename T>
struct GIsNothrowMoveAssignable
	: GIsNothrowAssignable<
	typename GAddLvalueReference<T>::Type,
	typename GAddRvalueReference<T>::Type
	>::Type
{
};

template<gbool TEST, typename T = gvoid>
struct GEnableIf
{
};

template<typename T>
struct GEnableIf<true, T>
{
	typedef T Type;
};

template<typename T>
struct GDecay {
private:
	typedef typename GRemoveReference<T>::Type U;
public:
	typedef typename GConditional<
		GIsArray<U>::value,
		typename GRemoveExtent<U>::Type*,
		typename GConditional<
		std::is_function<U>::value,
		typename std::add_pointer<U>::type,
		typename GRemoveConstVolatile<U>::Type
		>::Type
	>::Type Type;
};

template<typename T>
typename GAddRvalueReference<T>::Type GDeclval() noexcept
{
	return std::declval<T>();
}

template <gsize>	struct GIntegerForSize;
template <>			struct GIntegerForSize<1> { typedef guint8  Unsigned; typedef gint8  Signed; };
template <>			struct GIntegerForSize<2> { typedef guint16 Unsigned; typedef gint16 Signed; };
template <>			struct GIntegerForSize<4> { typedef guint32 Unsigned; typedef gint32 Signed; };
template <>			struct GIntegerForSize<8> { typedef guint64 Unsigned; typedef gint64 Signed; };

template <typename T> struct GIntegerForSizeof : GIntegerForSize<sizeof(T)> { };
typedef GIntegerForSizeof<gpointer>::Unsigned guintptr;
typedef GIntegerForSizeof<gpointer>::Signed gptrdiff;

template <typename ...TS>
struct GTypesTraits
{

};

template <>
struct GTypesTraits<>
{
	static constexpr gsize count = 0;
	static constexpr gsize total_size = 0;
	static constexpr gsize max_size = 0;
	static constexpr gsize min_size = 0;
	static constexpr gsize align = 0;
};

template <typename T, typename ...TS>
struct GTypesTraits<T, TS...>
{
private:
	static constexpr gsize cur_size = sizeof(T);
	static constexpr gsize next_max_size = GTypesTraits<TS...>::max_size;
	static constexpr gsize next_min_size = GTypesTraits<TS...>::min_size;
	static constexpr gsize cur_align = alignof(T);
	static constexpr gsize next_align = GTypesTraits<TS...>::align;

public:
	static constexpr gsize count = 1 + GTypesTraits<TS...>::count;
	static constexpr gsize total_size = cur_size + GTypesTraits<TS...>::total_size;
	static constexpr gsize max_size = cur_size > next_max_size ? cur_size : next_max_size;
	static constexpr gsize min_size = cur_size < next_min_size ? cur_size : next_min_size;
	static constexpr gsize align = cur_align > next_align ? cur_align : next_align;
};

/// 判断类型T是否存在于类型列表TS中
/// id表示T在TS中的位置（从1开始计数，0表示不存在）
template <typename T, typename ...TS>
struct GTypeExist
{

};

template <typename T>
struct GTypeExist<T>
{
	static const gbool exist = false;
	static constexpr gsize id = 0;
};

template <typename T, typename T2, typename ...TS>
struct GTypeExist<T, T2, TS...>
{
	static const gbool exist = GIsSame<T, T2>::value || GTypeExist<T, TS...>::exist;
	static constexpr gsize id = GIsSame<T, T2>::value ? 1 : 1 + GTypeExist<T, TS...>::id;
};

#endif // _CORE_TRAITS_H_