#ifndef _CORE_SERIALIZE_INLINE_
#define _CORE_SERIALIZE_INLINE_

#include "gtraits.h"
#include "garchive.h"
#include "gfunctor.h"

namespace gsystem { // gsystem
namespace detail {

// 判断一个类是否有Serialize方法
// gbool b = GHasSerializeFunction<ClassName>::value;
template<typename T>
struct GHasSerializeFunction {

	template<typename U, gbool(U::*)(GArchive &archive) const>
	struct Matcher;

	template<typename U>
	static gint8 Foo(Matcher<U, &U::Serialize> *);

	template<typename U>
	static gint32 Foo(...);

	enum { value = sizeof(Foo<T>(GNULL)) == sizeof(gint8) };
};

// 判断一个类是否有Deserialize方法
// gbool b = GHasDeserializeFunction<ClassName>::value;
template<typename T>
struct GHasDeserializeFunction {

	template<typename U, gbool(U::*)(GArchive &archive)>
	struct Matcher;

	template<typename U>
	static gint8 Foo(Matcher<U, &U::Deserialize> *);

	template<typename U>
	static gint32 Foo(...);

	enum { value = sizeof(Foo<T>(GNULL)) == sizeof(gint8) };
};

// T包含了Serialize方法
template<typename T>
gbool ___GSerialize(GArchive &archive, const T &v, GTrueType)
{
	return v.Serialize(archive);
}

// T未包含Serialize方法
template<typename T>
gbool ___GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// 无法序列化，抛出异常？（TODO）
	return false;
}

// T是GSerializable的子类
template<typename T>
gbool __GSerialize(GArchive &archive, const T &v, GTrueType)
{
	return v.Serialize(archive);
}

// T不是GSerializable的子类
template<typename T>
gbool __GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// 检查T是否包含了Serialize方法
	return ___GSerialize<T>(archive, v,
		GCatBase<GHasSerializeFunction<T>::value>());
}

// T是内置类型
template<typename T>
gbool _GSerialize(GArchive &archive, const T &v, GTrueType)
{
	archive << v;
	return true;
}

// T不是内置类型
template<typename T>
gbool _GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// 检查T是否是GSerializable的子类
	return __GSerialize<T>(archive, v,
		GIsBaseOf<GSerializable, T>());
}

// T包含了Deserialize方法
template<typename T>
gbool ___GDeserialize(GArchive &archive, T &v, GTrueType)
{
	return v.Deserialize(archive);
}

// T未包含Deserialize方法
template<typename T>
gbool ___GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// 无法序列化，抛出异常？（TODO）
	return false;
}

// T是GSerializable的子类
template<typename T>
gbool __GDeserialize(GArchive &archive, T &v, GTrueType)
{
	return v.Deserialize(archive);
}

// T不是GSerializable的子类
template<typename T>
gbool __GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// 检查T是否包含了Deserialize方法
	return ___GDeserialize<T>(archive, v,
		GCatBase<GHasDeserializeFunction<T>::value>());
}

// T是内置类型
template<typename T>
gbool _GDeserialize(GArchive &archive, T &v, GTrueType)
{
	archive >> v;
	return true;
}

// T不是内置类型
template<typename T>
gbool _GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// 检查T是否是GSerializable的子类
	return __GDeserialize<T>(archive, v,
		GIsBaseOf<GSerializable, T>());
}

} // namespace gsystem.detail

template<typename T> GINLINE
gbool GSerialize(GArchive &archive, const T &v)
{
	// 检查T是否是基本类型
	return detail::_GSerialize<T>(archive, v,
		GIsArithmetic<T>());
}

template<typename T> GINLINE
gbool GDeserialize(GArchive &archive, T &v)
{
	// 检查T是否是基本类型
	return detail::_GDeserialize<T>(archive, v,
		GIsArithmetic<T>());
}

} // namespace gsystem

#endif // _CORE_SERIALIZE_INLINE_
