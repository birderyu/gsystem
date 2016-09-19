#include "CsString_Private.h"
#include "CsMutex_Private.h"
#include "CsAutoLock.h"

#define HASHCODE_BASE 31

CS_IMPLEMENT_OPERATOR_NEW_DELETE(CsString_Private, CsMutex_Private)

CsString_Private::CsString_Private(CsString *pPublic)
: CsObject_Private(pPublic), m_sStr()
{

}

CsString_Private::CsString_Private(CsString *pPublic, const cs_char cChar)
: CsObject_Private(pPublic), m_sStr()
{
	m_sStr = cChar;
}

CsString_Private::CsString_Private(CsString *pPublic, const cs_char *pStr)
: CsObject_Private(pPublic), m_sStr(pStr)
{

}
CsString_Private::CsString_Private(CsString *pPublic, const std::string &sStr)
: CsObject_Private(pPublic), m_sStr(sStr)
{

}

CsString_Private::CsString_Private(CsString *pPublic, const CsString_Private &sStr)
: CsObject_Private(pPublic), m_sStr(sStr.m_sStr)
{

}

CsString_Private::~CsString_Private()
{

}

cs_bool CsString_Private::Equals(CsString_Private *pStr) const
{
	if (!pStr)
	{
		return false;
	}
	return m_sStr == pStr->m_sStr;
}

cs_uint64 CsString_Private::HashCode() const
{
	cs_uint64 nCode = 0;
	cs_char c = '\0';
	cs_uint nSize = GetSize();
	cs_uint i = 0;
	for (i = 0; i < nSize; i++)
	{
		c = m_sStr[i];
		if (!c)
		{
			continue;
		}
		nCode = nCode * HASHCODE_BASE + c;
	}
	return nCode;
}

cs_bool CsString_Private::operator==(const CsString_Private &sStr)
{
	return m_sStr == sStr.m_sStr;
}

CsString_Private &CsString_Private::operator=(const CsString_Private &sStr)
{
	m_sStr = sStr.m_sStr;
	return *this;
}

CsString_Private &CsString_Private::operator+=(const CsString_Private &sStr)
{
	m_sStr += sStr.m_sStr;
	return *this;
}

cs_uint CsString_Private::GetSize() const
{
	return m_sStr.size();
}

cs_bool CsString_Private::IsEmpty() const
{
	return m_sStr.empty();
}

cs_cstring CsString_Private::GetCStr() const
{
	return m_sStr.c_str();
}

void CsString_Private::MakeTrim()
{
	std::string::size_type pos = m_sStr.find_last_not_of(' ');
	if (pos != std::string::npos)
	{
		m_sStr.erase(pos + 1);
		pos = m_sStr.find_first_not_of(' ');
		if (pos != std::string::npos) m_sStr.erase(0, pos);
	}
	else
	{
		m_sStr.erase(m_sStr.begin(), m_sStr.end());
	}
}

void CsString_Private::MakeUpper()
{
	std::string sStr;
	std::string::size_type i = 0;
	std::string::size_type end = m_sStr.size();
	for (i = 0; i < end; i++)
	{
		cs_char c = toupper(m_sStr.at(i));
		sStr.push_back(c);
	}
	m_sStr = sStr;
}

void CsString_Private::MakeLower()
{
	std::string sStr;
	std::string::size_type i = 0;
	std::string::size_type end = m_sStr.size();
	for (i = 0; i < end; i++)
	{
		cs_char c = tolower(m_sStr.at(i));
		sStr.push_back(c);
	}
	m_sStr = sStr;
}
