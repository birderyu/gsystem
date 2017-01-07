#include "gstring.h"

gvoid GString::Free()
{
	GStringStore::Free(m_tStringStore);
}

GString &GString::ToValue()
{
	if (IsReference())
	{
		// 引用类型，将其转换成值
		// TODO
	}
	return *this;
}

gbool GString::IsReference() const
{
	return m_tStringStore.m_nType == GStringStore::STRING_STORE_TYPE_REFERENCE;
}

GStringStore::TYPE GString::GetTypeBySize(gsize size) const
{
	if (size <= GSmallStringStore::MAX_SIZE)
	{
		// 小字符串
		return GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	}

	if (size <= GNormalStringStore::MAX_SIZE)
	{
		// 普通字符串
		return GStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
	}

	// 大字符串
	return GStringStore::STRING_STORE_TYPE_VALUE_BIG;
}
