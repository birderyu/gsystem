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

// DataT包含了Serialize方法
template<typename DataT>
gbool ___GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	return v.Serialize(archive);
}

// DataT未包含Serialize方法
template<typename DataT>
gbool ___GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// 无法序列化，抛出异常？（TODO）
	return false;
}

// DataT是GSerializable的子类
template<typename DataT>
gbool __GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	return v.Serialize(archive);
}

// DataT不是GSerializable的子类
template<typename DataT>
gbool __GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// 检查DataT是否包含了Serialize方法
	return ___GSerialize<DataT>(archive, v,
		GCatBase<GHasSerializeFunction<DataT>::value>());
}

// DataT是内置类型
template<typename DataT>
gbool _GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	archive << v;
	return true;
}

// DataT不是内置类型
template<typename DataT>
gbool _GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// 检查DataT是否是GSerializable的子类
	return __GSerialize<DataT>(archive, v,
		GIsBaseOf<GSerializable, DataT>());
}

// DataT包含了Deserialize方法
template<typename DataT>
gbool ___GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	return v.Deserialize(archive);
}

// DataT未包含Deserialize方法
template<typename DataT>
gbool ___GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// 无法序列化，抛出异常？（TODO）
	return false;
}

// DataT是GSerializable的子类
template<typename DataT>
gbool __GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	return v.Deserialize(archive);
}

// DataT不是GSerializable的子类
template<typename DataT>
gbool __GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// 检查DataT是否包含了Deserialize方法
	return ___GDeserialize<DataT>(archive, v,
		GCatBase<GHasDeserializeFunction<DataT>::value>());
}

// DataT是内置类型
template<typename DataT>
gbool _GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	archive >> v;
	return true;
}

// DataT不是内置类型
template<typename DataT>
gbool _GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// 检查DataT是否是GSerializable的子类
	return __GDeserialize<DataT>(archive, v,
		GIsBaseOf<GSerializable, DataT>());
}

} // namespace gsystem.detail

template<typename DataT> GINLINE
gbool GSerialize(GArchive &archive, const DataT &v)
{
	// 检查DataT是否是基本类型
	return detail::_GSerialize<DataT>(archive, v,
		GIsArithmetic<DataT>());
}

template<typename DataT> GINLINE
gbool GDeserialize(GArchive &archive, DataT &v)
{
	// 检查DataT是否是基本类型
	return detail::_GDeserialize<DataT>(archive, v,
		GIsArithmetic<DataT>());
}

} // namespace gsystem

#endif // _CORE_SERIALIZE_INLINE_
