#include "CsString.h"

cs_void CsString::Free()
{
	CsStringStore::Free(m_tStringStore);
}

CsString &CsString::ToValue()
{
	if (IsReference())
	{
		// 引用类型，将其转换成值
		// TODO
	}
	return *this;
}

cs_bool CsString::IsReference() const
{
	return m_tStringStore.m_nType == CsStringStore::STRING_STORE_TYPE_REFERENCE;
}

CsStringStore::TYPE CsString::GetTypeBySize(cs_size_t size) const
{
	if (size <= CsSmallStringStore::MAX_SIZE)
	{
		// 小字符串
		return CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	}

	if (size <= CsNormalStringStore::MAX_SIZE)
	{
		// 普通字符串
		return CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
	}

	// 大字符串
	return CsStringStore::STRING_STORE_TYPE_VALUE_BIG;
}
