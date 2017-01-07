#include "CsString.h"

cs_bool CsString::operator==(const CsString &sStr) const
{
	// TODO
	return false;
}

CsString &CsString::operator+=(const CsString &sStr)
{
	// TODO
	return *this;
}

CsString &CsString::operator=(const CsString &sStr)
{
	if (this == &sStr)
	{
		return *this;
	}

	Free();
	m_tStringStore.m_nType = sStr.m_tStringStore.m_nType;
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		m_tStringStore.m_sSmallStr.Initialize(sStr.m_tStringStore.m_sSmallStr);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		m_tStringStore.m_sNormalStr.Initialize(sStr.m_tStringStore.m_sNormalStr);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case CsStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
		break;
	}
	return *this;
}

cs_char CsString::operator[](cs_size_t pos) const
{
	return GetAt(pos);
}

cs_char &CsString::operator[](cs_size_t pos)
{
	return GetAt(pos);
}

cs_bool CsString::operator<(const CsString &)
{
	// TODO
	return false;
}

cs_bool CsString::operator>(const CsString &)
{
	// TODO
	return false;
}

CsString operator+(const CsString &s1, const CsString &s2)
{
	CsString sStr(s1);
	sStr += s2;
	return sStr;
}

cs_bool operator>(const CsString &s1, const CsString &s2)
{
	// TODO
	return false;
}

cs_bool operator<(const CsString &s1, const CsString &s2)
{
	// TODO
	return false;
}