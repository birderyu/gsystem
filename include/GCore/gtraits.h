/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gtraits.h
** @brief	萃取器
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-12-31
** @version	1.0
**
** 萃取器用于在编译期间获取类型信息，在GSystem提供了许多不同功能的萃取器，它们可以用来：
** 1）移除类型信息（Remove Traits），如移除const修饰符、移除引用等，这些萃取器往往以
** GRemove作为前缀；2）添加类型信息（Add Traits），如添加const修饰符、添加（左值或右
** 值）引用等，这些萃取器往往以GAdd作为前缀；3）判断类型信息（If Traits），如判断一个类
** 型是否是数组类型等，这些萃取器往往以GIf作为前缀；4）其他萃取器，包括标准库中的重新实现
** 和一些自定义的萃取器。
**
****************************************************************************/

#ifndef _CORE_TRAITS_H_
#define _CORE_TRAITS_H_

#include "gtype.h"
#include <type_traits>

#define G_NON_MEMBER_CALL(FUNC, CV_REF_OPT, WEIRD_OPT) \
	_EMIT_CDECL(FUNC, CV_REF_OPT, WEIRD_OPT) \
	_EMIT_CLRCALL(FUNC, CV_REF_OPT, WEIRD_OPT) \
	_EMIT_FASTCALL(FUNC, CV_REF_OPT, WEIRD_OPT) \
	_EMIT_STDCALL(FUNC, CV_REF_OPT, WEIRD_OPT) \
	_EMIT_VECTORCALL(FUNC, CV_REF_OPT, WEIRD_OPT)

#define G_NON_MEMBER_CALL_CV(FUNC, REF_OPT, WEIRD_OPT) \
	G_NON_MEMBER_CALL(FUNC, REF_OPT, WEIRD_OPT) \
	G_NON_MEMBER_CALL(FUNC, const REF_OPT, true) \
	G_NON_MEMBER_CALL(FUNC, volatile REF_OPT, true) \
	G_NON_MEMBER_CALL(FUNC, const volatile REF_OPT, true)

#define G_NON_MEMBER_CALL_CV_REF(FUNC) \
	G_NON_MEMBER_CALL_CV(FUNC, , false) \
	G_NON_MEMBER_CALL_CV(FUNC, &, true) \
	G_NON_MEMBER_CALL_CV(FUNC, &&, true)

#define G_MEMBER_CALL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_CDECL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_CLRCALL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_FASTCALL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_STDCALL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_THISCALL(FUNC, CV_OPT, REF_OPT) \
	_EMIT_VECTORCALL(FUNC, CV_OPT, REF_OPT)

#define G_MEMBER_CALL_CV(FUNC, REF_OPT) \
	G_MEMBER_CALL(FUNC, , REF_OPT) \
	G_MEMBER_CALL(FUNC, const, REF_OPT) \
	G_MEMBER_CALL(FUNC, volatile, REF_OPT) \
	G_MEMBER_CALL(FUNC, const volatile, REF_OPT)

#define G_MEMBER_CALL_CV_REF(FUNC) \
	G_MEMBER_CALL_CV(FUNC, ) \
	G_MEMBER_CALL_CV(FUNC, &) \
	G_MEMBER_CALL_CV(FUNC, &&)

#define G_CLASS_DEFINE_CV_REF(CLASS) \
	CLASS( , false) \
	CLASS(const, true) \
	CLASS(volatile, true) \
	CLASS(const volatile, true) \
	CLASS(&, true) \
	CLASS(const &, true) \
	CLASS(volatile &, true) \
	CLASS(const volatile &, true) \
	CLASS(&&, true) \
	CLASS(const &&, true) \
	CLASS(volatile &&, true) \
	CLASS(const volatile &&, true)

namespace gsystem { // gsystem
					// 在这个代码片段内的萃取器，主要用于“移除类型信息”

// GRemoveConst：移除类型中的const
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

// GRemoveVolatile：移除类型中的volatile
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

// GRemoveConstVolatile：移除类型中的const和volatile
template<typename T>
struct GRemoveConstVolatile
{
	typedef typename GRemoveConst<typename GRemoveVolatile<T>::Type>::Type Type;
};

// GRemoveReference：移除类型中的引用
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

// GRemovePointer：移除类型中的指针
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

// GRemoveExtent：移除数组，仅保留类型
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

} // namespace gsystem

namespace gsystem { // gsystem
					// 在这个代码片段内的萃取器，主要用于“添加类型信息”

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
	typedef T& Type;
};

template<typename T>
struct GAddRvalueReference
{
	typedef T&& Type;
};

template<typename T>
typename GAddRvalueReference<T>::Type GDeclval() noexcept;
/*
{
return std::declval<T>();
}
*/

template<typename T>
struct GAddPointer
{
	typedef typename GRemoveReference<T>::Type *Type;
};
}

namespace gsystem { // gsystem
					// 在这个代码片段内的萃取器，主要用于“判断类型信息”

template<typename ClassT, ClassT DefValue>
struct GIntegralConstant
{
	static constexpr ClassT value = DefValue;

	typedef ClassT ValueType;
	typedef GIntegralConstant<ClassT, DefValue> Type;

	constexpr operator ValueType() const
	{
		return (value);
	}

	constexpr ValueType operator()() const noexcept
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

// GIsSame：判断两个类型是否是同一种类型
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

// GIsArray：是否是数组
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

namespace detail { // gsystem.detail
namespace traits { // gsystem.detail.traits

template<typename... ArgTs>
struct GArgTypes
{
};

template<typename T>
struct GArgTypes<T>
{
	typedef T ArgumentType;
};

template<typename T1, typename T2>
struct GArgTypes<T1, T2>
{
	typedef T1 FirstArgumentType;
	typedef T2 SecondArgumentType;
};

template<typename T>
struct _GIsMemberFunctionPointer
{
	typedef GFalseType BoolType;
};

#define G_IS_MEMFUNPTR(CALL_OPT, CV_OPT, REF_OPT) \
template<typename RetT, typename Arg0T, typename... ArgTs> \
	struct _GIsMemberFunctionPointer<RetT (CALL_OPT Arg0T::*)(ArgTs...) CV_OPT REF_OPT> \
		: GArgTypes<CV_OPT Arg0T *, ArgTs...> \
	{ \
	typedef GTrueType BoolType; \
	typedef RetT ResultType; \
	typedef Arg0T ClassType; \
	};

G_MEMBER_CALL_CV_REF(G_IS_MEMFUNPTR)
#undef G_IS_MEMFUNPTR

#define G_IS_MEMFUNPTR_ELLIPSIS(CV_REF_OPT, X1) \
template<typename RetT, typename Arg0T, typename... ArgTs> \
	struct _GIsMemberFunctionPointer<RetT (Arg0T::*)(ArgTs..., ...) CV_REF_OPT> \
	{ \
	typedef GTrueType BoolType; \
	typedef RetT ResultType; \
	typedef Arg0T ClassType; \
	};

G_CLASS_DEFINE_CV_REF(G_IS_MEMFUNPTR_ELLIPSIS)
#undef G_IS_MEMFUNPTR_ELLIPSIS

template<typename T, 
	gbool PmfT = _GIsMemberFunctionPointer<T>::BoolType::value>
struct _GIsMemberObjectPointer
	: GFalseType
{
};

template<typename T1, typename T2>
struct _GIsMemberObjectPointer<T1 T2::*, false>
	: GTrueType
{
	typedef T2 ClassType;
};

} // namespace gsystem.detail
} // namespace gsystem.detail.traits

template<typename T>
struct GIsMemberObjectPointer
	: detail::traits::_GIsMemberObjectPointer<typename GRemoveConstVolatile<T>::Type>::Type
{
};

template<typename T>
struct GIsMemberFunctionPointer
	: detail::traits::_GIsMemberObjectPointer<typename GRemoveConstVolatile<T>::Type>::BoolType
{
};

namespace detail { // gsystem.detail
namespace traits { // gsystem.detail.traits

	/// 是否是整型
template<typename T>
struct _GIsIntegral
	: GFalseType{};

template<>
struct _GIsIntegral<gbool>
	: GTrueType{};

template<>
struct _GIsIntegral<gchar>
	: GTrueType{};

template<>
struct _GIsIntegral<gschar>
	: GTrueType{};

template<>
struct _GIsIntegral<guchar>
	: GTrueType{};

template<>
struct _GIsIntegral<gwchar>
	: GTrueType{};

template<>
struct _GIsIntegral<gshort>
	: GTrueType{};

template<>
struct _GIsIntegral<gushort>
	: GTrueType{};

template<>
struct _GIsIntegral<gint>
	: GTrueType{};

template<>
struct _GIsIntegral<guint>
	: GTrueType{};

template<>
struct _GIsIntegral<glong>
	: GTrueType{};

template<>
struct _GIsIntegral<gulong>
	: GTrueType{};

template<>
struct _GIsIntegral<glonglong>
	: GTrueType{};

template<>
struct _GIsIntegral<gulonglong>
	: GTrueType{};

/// 是否是浮点型
template<class T>
struct _GIsFloatingPoint
	: GFalseType {};

template<>
struct _GIsFloatingPoint<gfloat>
	: GTrueType {};

template<>
struct _GIsFloatingPoint<gdouble>
	: GTrueType {};

template<>
struct _GIsFloatingPoint<glongdouble>
	: GTrueType {};

template<typename T>
struct _GIsPointer
	: GFalseType
{
};

template<typename T>
struct _GIsPointer<T *>
	: GCatBase<!GIsMemberObjectPointer<T *>::value
	&& !GIsMemberFunctionPointer<T *>::value>
{
};

} // namespace gsystem.detail
} // namespace gsystem.detail.traits

template<typename T>
struct GIsIntegral
	: detail::traits::_GIsIntegral<typename GRemoveConstVolatile<T>::Type>{};

template<typename T>
struct GIsFloatingPoint
	: detail::traits::_GIsFloatingPoint<typename GRemoveConstVolatile<T>::Type>{};

/// 是否是数字类型
template<typename T>
struct GIsNumeric
	: GCatBase<GIsIntegral<T>::value || GIsFloatingPoint<T>::value>{};

/// 是否是算数类型
template<typename T>
struct GIsArithmetic
	: GCatBase<GIsIntegral<T>::value || GIsFloatingPoint<T>::value>{};

template<typename T>
struct GIsPointer
	: detail::traits::_GIsPointer<typename GRemoveConstVolatile<T>::Type>
{
};

template<typename FromT, typename ToT>
struct GIsConvertible
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

namespace detail { // gsystem.detail
namespace traits { // gsystem.detail.traits

template<typename ToT, typename FromT>
struct _GIsAssignable
{
	template<class DestT, class SrcT>
	static decltype((gvoid)(GDeclval<DestT>() = GDeclval<SrcT>()), GTrueType()) Foo(gint);

	template<typename DestT, typename SrcT>
	static GFalseType Foo(gint);

	typedef decltype(Foo<ToT, FromT>(0)) Type;
};

} // namespace gsystem.detail.traits
} // namespace gsystem.detail

template<typename ToT, typename FromT>
struct GIsAssignable
	: detail::traits::_GIsAssignable<ToT, FromT>::Type
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
		typename GAddLvalueReference<T>::Type,
		typename GAddRvalueReference<T>::Type
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

namespace detail { // gsystem.detail
namespace traits { // gsystem.detail.traits

template<typename T>
struct _GIsFunction
{
	typedef GFalseType BoolType;
};

#define G_IS_FUNCTION(CALL_OPT) \
template<typename RetT, typename... ArgTs> \
	struct _GIsFunction<RetT CALL_OPT (ArgTs...)> \
		: GArgTypes<ArgTs...> \
	{ \
	typedef GTrueType BoolType; \
	typedef RetT ResultType; \
	};

G_NON_MEMBER_CALL(G_IS_FUNCTION)
#undef G_IS_FUNCTION

template<typename RetT, typename... ArgTs>
struct _GIsFunction<RetT(ArgTs..., ...)>
{
	typedef GTrueType BoolType;
	typedef RetT ResultType;
};

} // namespace gsystem.detail.traits
} // namespace gsystem.detail

template<typename T>
struct GIsFunction
	: detail::traits::_GIsFunction<T>::BoolType
{
};

} // namespace gsystem

namespace gsystem { // gsystem
					// 在这个代码片段内的萃取器，主要包括一些常用的判断方法

template<gbool TEST, typename T = gvoid>
struct GEnableIf
{
};

template<typename T>
struct GEnableIf<true, T>
{
	typedef T Type;
};

// GConditional：条件判断
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

template<typename T>
struct GDecay {
private:
	typedef typename GRemoveReference<T>::Type U;
public:
	typedef typename GConditional<
		GIsArray<U>::value,
		typename GRemoveExtent<U>::Type*,
		typename GConditional<
		GIsFunction<U>::value,
		typename GAddPointer<U>::type,
		typename GRemoveConstVolatile<U>::Type
		>::Type
	>::Type Type;
};

} // namespace gsystem

namespace gsystem { // gsystem
					// 在这个代码片段内的萃取器，主要包括一些标准库中没有对应类型的自定义萃取器

template <gsize>	struct GIntegerForSize;
template <>			struct GIntegerForSize<1> { typedef guint8  Unsigned; typedef gint8  Signed; };
template <>			struct GIntegerForSize<2> { typedef guint16 Unsigned; typedef gint16 Signed; };
template <>			struct GIntegerForSize<4> { typedef guint32 Unsigned; typedef gint32 Signed; };
template <>			struct GIntegerForSize<8> { typedef guint64 Unsigned; typedef gint64 Signed; };

template <typename T> struct GIntegerForSizeof : GIntegerForSize<sizeof(T)> { };
typedef GIntegerForSizeof<gptr>::Unsigned guintptr;
typedef GIntegerForSizeof<gptr>::Signed gptrdiff;

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

} // namespace gsystem

#endif // _CORE_TRAITS_H_