#include "gstring.h"

gbool GString::operator==(const GString &sStr) const
{
	// TODO
	return false;
}

GString &GString::operator+=(const GString &sStr)
{
	// TODO
	return *this;
}

GString &GString::operator=(const GString &sStr)
{
	if (this == &sStr)
	{
		return *this;
	}

	Free();
	m_tStringStore.m_nType = sStr.m_tStringStore.m_nType;
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		m_tStringStore.m_sSmallStr.Initialize(sStr.m_tStringStore.m_sSmallStr);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		m_tStringStore.m_sNormalStr.Initialize(sStr.m_tStringStore.m_sNormalStr);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
		break;
	}
	return *this;
}

gchar GString::operator[](gsize pos) const
{
	return GetAt(pos);
}

gchar &GString::operator[](gsize pos)
{
	return GetAt(pos);
}

gbool GString::operator<(const GString &)
{
	// TODO
	return false;
}

gbool GString::operator>(const GString &)
{
	// TODO
	return false;
}

GString operator+(const GString &s1, const GString &s2)
{
	GString sStr(s1);
	sStr += s2;
	return sStr;
}

gbool operator>(const GString &s1, const GString &s2)
{
	// TODO
	return false;
}

gbool operator<(const GString &s1, const GString &s2)
{
	// TODO
	return false;
}