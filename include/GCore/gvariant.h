#ifndef _CORE_VARIANT_H_
#define _CORE_VARIANT_H_

#include "gglobal.h"
#include "gnew.h"

namespace GNova {
	namespace Variant {
		namespace Private {

			template<typename T, typename ...TS>
			struct GSelectConvertible
			{
				enum { exist = false };
				using Type = gvoid;
			};

			template<typename T, typename T1, typename ...TS>
			struct GSelectConvertible<T, T1, TS...>
			{
				enum { exist = GConvertible<T, T1>::value || GSelectConvertible<T, TS...>::exist };
				using Type = typename GConditional<GConvertible<T, T1>::value, T1, typename GSelectConvertible<T, TS...>::Type>::Type;
			};

			/// 从类型列表TS中选出类型T，若不存在则返回T本身
			template<typename T, typename ...TS>
			struct GSelectType
			{
				using Type = typename GConditional<GTypeExist<T, TS...>::exist, T, typename GSelectConvertible<T, TS...>::Type>::Type;
			};

			using construct_func_t = gvoid(*)(gbyte *);
			using copy_func_t = gvoid(*)(gbyte *, const gbyte *);
			using move_func_t = gvoid(*)(gbyte *, gbyte *);
			using destruct_func_t = gvoid(*)(gbyte *);

			template <typename T>
			gvoid DefaultConstruct(gbyte *ptr)
			{
				GDefaultConstruct<T>(reinterpret_cast<T*>(ptr));
			}

			template <typename T>
			gvoid CopyConstruct(gbyte *ptr, const gbyte *copyable)
			{
				GCopyConstruct<T>(reinterpret_cast<T*>(ptr),
					*reinterpret_cast<const T*>(copyable));
			}

			template <typename T>
			gvoid MoveConstruct(gbyte *ptr, gbyte *moveable)
			{
				GMoveConstruct<T>(reinterpret_cast<T *>(ptr),
					GMove(*reinterpret_cast<T *>(moveable)));
			}

			template <typename T>
			gvoid CopyAssign(gbyte *ptr, const gbyte *copyable)
			{
				T* dst = reinterpret_cast<T *>(ptr);
				const T* src = reinterpret_cast<const T *>(copyable);
				*dst = *src;
			}

			template <typename T>
			gvoid MoveAssign(gbyte *ptr, gbyte *moveable)
			{
				T* dst = reinterpret_cast<T *>(ptr);
				T* src = reinterpret_cast<T *>(moveable);
				*dst = GMove(*src);
			}

			template <typename T>
			gvoid Destruct(gbyte *ptr)
			{
				GDestruct<T>(reinterpret_cast<T*>(ptr));
			}

			template<>
			GINLINE gvoid CopyConstruct<gvoid>(gbyte *ptr, const gbyte *copyable)
			{
				throw "try to copy variant object containing non-copyable type.";
			}

			template<>
			GINLINE gvoid MoveConstruct<gvoid>(gbyte *ptr, gbyte *moveable)
			{
				throw "try to move variant object containing non-moveable type.";
			}

			template<>
			GINLINE gvoid CopyAssign<gvoid>(gbyte *ptr, const gbyte *copyable)
			{
				throw "try to copy assign variant object containing non-assignable type.";
			}

			template<>
			GINLINE gvoid MoveAssign<gvoid>(gbyte *ptr, gbyte *moveable)
			{
				throw "try to move assign variant object containing non-assignable type.";
			}

			template<typename T>
			struct GSelectCopy
			{
				using Type = typename GConditional<GIsCopyConstructible<T>::Value, T, gvoid>::Type;
				constexpr static copy_func_t fun = CopyConstruct<Type>;
			};

			template<typename T>
			struct GSelectMove
			{
				using Type = typename GConditional<GIsMoveConstructible<T>::Value, T, gvoid>::Type;
				constexpr static move_func_t fun = MoveConstruct<Type>;
			};

			template<typename T>
			struct GSelectCopyAssign
			{
				using Type = typename GConditional<GIsCopyAssignable<T>::Value, T, gvoid>::Type;
				constexpr static copy_func_t fun = CopyAssign<Type>;
			};

			template<typename T>
			struct GSelectMoveAssign
			{
				using Type = typename GConditional<GIsMoveAssignable<T>::Value, T, gvoid>::Type;
				constexpr static move_func_t fun = MoveAssign<Type>;
			};

			template<gbool lvalue, typename T>
			struct GCheckConstructible
			{
				enum { value = GIsCopyConstructible<T>::value };
			};

			template<typename T>
			struct GCheckConstructible<false, T>
			{
				enum { value = GIsMoveConstructible<T>::value };
			};

			template<template<typename> class CHECK, typename ...TS>
			struct GCheckTypeList
			{
				enum { value = 1 };
			};

			template<template<typename> class CHECK, typename T, typename ...TS>
			struct GCheckTypeList<CHECK, T, TS...>
			{
				enum { value = CHECK<T>::value && GCheckTypeList<CHECK, TS...>::value };
			};

			template <typename T, typename R = gvoid>
			struct GGetVisitorResultType
			{
				template <typename T2> static R Foo(...);
				template <typename T2> static typename T2::result_type Foo(typename T2::result_type *v);

				using Type = decltype(Foo<T>(GNULL));
			};

			template<typename V, typename ...TS>
			struct g_check_visitor_func
			{
				enum { value = 1 };
			};

			template<typename V, typename T, typename ...TS>
			struct g_check_visitor_func<V, T, TS...>
			{
				using ret_t = typename GGetVisitorResultType<V>::Type;

				static T &GetFakeValRef();
				using func_t = decltype(GDeclval<V>()(GetFakeValRef()));

				enum { value = GConvertible<ret_t, func_t>::value && g_check_visitor_func<V, TS...>::value };
			};

			template<typename T, typename V>
			struct g_variant_cast
			{
				operator T &() { return static_cast<V &>(*this).template GetReference<T>(); }
			};
		}
	}
}

template<typename ...TS>
class GVariant
	: public GNewT<GVariant<TS...>>
{ 
public:
	GVariant()
		: type_(0)
	{

	}

	template<typename T,
		typename D = 
			typename GEnableIf<
				!GIsSame<
					typename GRemoveReference<T>::Type, 
					Variant<TS...>
				>::value
			>::Type,
		typename CT =
			typename GNova::Variant::Private::GSelectType<
				typename GRemoveReference<T>::Type, TS...
			>::Type
		>
	GVariant(const T &v)
		: type_(GTypeExist<CT, TS...>::id)
	{
		static_assert(GTypeExist<CT, TS...>::exist,
			"invalid type for the variant.");

		static_assert(GNova::Variant::Private::GCheckConstructible<GIsRvalueReference<T>::value, CT>::value,
			"try to copy or move an object that is not copyable or movable.");

		GCopyConstruct<CT>((CT *)data_, v);
	}

	template<typename T,
		typename D =
			typename GEnableIf<
				!GIsSame<
					typename GRemoveReference<T>::Type,
					Variant<TS...>
				>::value
			>::Type,
		typename CT = 
			typename GNova::Variant::Private::GSelectType<
				typename GRemoveReference<T>::Type, TS...
			>::Type
		>
	GVariant(T &&v) 
		: type_(GTypeExist<CT, TS...>::id)
	{ 
		static_assert(GTypeExist<CT, TS...>::exist, 
			"invalid type for the variant.");

		static_assert(GNova::Variant::Private::GCheckConstructible<GIsLvalueReference<T>::value, CT>::value,
			"try to copy or move an object that is not copyable or movable.");

		GMoveConstruct<CT>((CT *)data_, GForward<T>(v));
	}

	GVariant(const GVariant<TS...> &v) noexcept(
		GNova::Variant::Private::GCheckTypeList<GIsNothrowCopyConstructible, TS...>::value)
	{
		if (v.type_ == 0) return;
		m_copy_construct[v.type_ - 1](data_, v.data_);
		type_ = v.type_;
	}

	GVariant(GVariant<TS...> &&v) noexcept(
		GNova::Variant::Private::GCheckTypeList<GIsNothrowMoveConstructible, TS...>::value)
	{
		if (v.type_ == 0) return; 
		m_move_construct[v.type_ - 1](data_, v.data_);
		type_ = v.type_;
	}

	template<typename T,
		typename D = typename GEnableIf<
			!GIsSame< typename GRemoveReference<T>::Type, Variant<TS...>>::value>::Type,
		typename CT = typename GNova::Variant::Private::GSelectType<
			typename GRemoveReference<T>::Type, TS...>::Type>
	GVariant &operator=(const T &v)
	{
		static_assert(GTypeExist<CT, TS...>::exist,
			"invalid type for the variant.");

		static_assert(GNova::Variant::Private::GCheckConstructible<GIsRvalueReference<T>::value, CT>::value,
			"try to copy or move an object that is not copyable or movable.");

		if (type_ != GTypeExist<CT, TS...>::id)
		{
			Release();
			GCopyConstruct<CT>((CT *)data_, v);
			type_ = GTypeExist<CT, TS...>::id;
		}
		else if (type_)
		{
			const gsize type = type_;
			type_ = 0;
			*reinterpret_cast<CT*>(data_) = v;
			type_ = type;
		}
		else
		{
			GCopyConstruct<CT>((CT *)data_, v);
			type_ = GTypeExist<CT, TS...>::id;
		}
	}

	template<typename T,
		typename D = typename GEnableIf<
			!GIsSame< typename GRemoveReference<T>::Type, Variant<TS...>>::value>::Type,
		typename CT = typename GNova::Variant::Private::GSelectType<
			typename GRemoveReference<T>::Type, TS...>::Type>
	GVariant &operator=(T &&v)
	{
		static_assert(GTypeExist<CT, TS...>::exist,
			"invalid type for the variant.");

		static_assert(GNova::Variant::Private::GCheckConstructible<GIsLvalueReference<T>::value, CT>::value,
			"try to copy or move an object that is not copyable or movable.");

		if (type_ != GTypeExist<CT, TS...>::id)
		{
			Release();
			GMoveConstruct<CT>((CT *)data_, GForward<T>(v));
			type_ = GTypeExist<CT, TS...>::id;
		}
		else if (type_)
		{
			const gsize type = type_;
			type_ = 0;
			*reinterpret_cast<CT*>(data_) = GForward<T>(v);
			type_ = type;
		}
		else
		{
			GMoveConstruct<CT>((CT *)data_, GForward<T>(v));
			type_ = GTypeExist<CT, TS...>::id;
		}

		return *this;
	}

	GVariant &operator=(const GVariant<TS...> &v)
	{
		if (this == &v)
		{
			return *this;
		}

		if (type_ != v.type_)
		{
			Release();
			if (!v.type_) return *this;

			m_copy_construct[v.type_ - 1](data_, v.data_);
			type_ = v.type_;
		}
		else if (type_)
		{
			const gsize type = type_;
			type_ = 0;
			m_copy_assign[type - 1](data_, v.data_);
			type_ = type;
		}

		return *this;
	}
	
	GVariant &operator=(GVariant<TS...> &&v) noexcept(
		GNova::Variant::Private::GCheckTypeList<GIsNothrowMoveConstructible, TS...>::value &&
		GNova::Variant::Private::GCheckTypeList<GIsNothrowMoveAssignable, TS...>::value)
	{
		if (this == &v)
		{
			return *this;
		}

		if (type_ != v.type_)
		{
			Release();
			if (!v.type_) return *this;

			m_move_construct[v.type_ - 1](data_, v.data_);
			type_ = v.type_;
		}
		else if (type_)
		{
			const gsize type = type_;
			type_ = 0;
			m_move_assign[type - 1](data_, v.data_);
			type_ = type;
		}

		return *this;
	}

	~GVariant() 
	{ 
		Release(); 
	}

	template <typename T, typename ...TS2>
	gvoid Emplace(TS2&& ...arg)
	{
		static_assert(GTypeExist<T, TS...>::exist, 
			"invalid type for the variant.");

		Release();

		// TODO，封装了变长的构造函数
		new(data_) T(GForward<TS2>(arg)...);
		type_ = GTypeExist<T, TS...>::id;
	}

	template <typename T> 
	T *GetPointer() noexcept
	{
		static_assert(GTypeExist<T, TS...>::exist, 
			"invalid type for the variant.");

		if (type_ != GTypeExist<T, TS...>::id) return GNULL;

		return reinterpret_cast<T*>(data_);
	}

	template <typename T> 
	const T *GetConstPointer() const noexcept
	{
		static_assert(GTypeExist<T, TS...>::exist,
			"invalid type for the variant.");

		if (type_ != GTypeExist<T, TS...>::id) return GNULL;

		return reinterpret_cast<const T*>(data_);
	}

	template <typename T> 
	T GetValue() const noexcept
	{
		return *GetConstPointer<T>();
	}

	template <typename T> 
	T &GetReference()
	{
		T* p = GetPointer<T>();
		if (!p) throw "invalid type for GetReference";
		return *p;
	}

	template <typename T> 
	const T &GetConstReference() const
	{
		const T* p = GetConstPointer<T>();
		if (!p) throw "invalid type for variant::Get<>()";

		return *p;
	}

	gsize GetType() const
	{
		return type_;
	}

private:
	gvoid Release() 
	{ 
		if (type_ == 0) return; 
		m_destruct[type_ - 1](data_);
	}

private: 
	constexpr static gsize Alignment() 
	{ 
		return GTypesTraits<TS...>::align;
	} 
	constexpr static gsize TypeSize() 
	{ 
		return GTypesTraits<TS...>::max_size;
	} 

private:
	gsize type_ = 0;
	alignas(Alignment()) gbyte data_[TypeSize()];

private:
	// 只是声明，需在结构体外再定义。 
	constexpr static GNova::Variant::Private::construct_func_t m_default_construct[] = { GNova::Variant::Private::DefaultConstruct<TS>... };
	constexpr static GNova::Variant::Private::copy_func_t m_copy_construct[] = { GNova::Variant::Private::CopyConstruct<TS>... };
	constexpr static GNova::Variant::Private::move_func_t m_move_construct[] = { GNova::Variant::Private::MoveConstruct<TS>... };
	constexpr static GNova::Variant::Private::destruct_func_t m_destruct[] = { GNova::Variant::Private::Destruct<TS>...};
	constexpr static GNova::Variant::Private::copy_func_t m_copy_assign[] = { GNova::Variant::Private::CopyAssign<TS>... };
	constexpr static GNova::Variant::Private::move_func_t m_move_assign[] = { GNova::Variant::Private::MoveAssign<TS>... };
};

// 定义 constexpr 数组。 
template<typename ...TS>
constexpr GNova::Variant::Private::construct_func_t GVariant<TS...>::m_default_construct[];
template<typename ...TS>
constexpr GNova::Variant::Private::copy_func_t GVariant<TS...>::m_copy_construct[];
template<typename ...TS>
constexpr GNova::Variant::Private::move_func_t GVariant<TS...>::m_move_construct[];
template<typename ...TS>
constexpr GNova::Variant::Private::destruct_func_t GVariant<TS...>::m_destruct[];
template<typename ...TS>
constexpr GNova::Variant::Private::copy_func_t GVariant<TS...>::m_copy_assign[];
template<typename ...TS>
constexpr GNova::Variant::Private::move_func_t GVariant<TS...>::m_move_assign[];

#include "gvariant.inl"

#endif // _CORE_VARIANT_H_
