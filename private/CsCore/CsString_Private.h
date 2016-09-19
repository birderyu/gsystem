#ifndef _CORE_STRING_PRIVATE_H_
#define _CORE_STRING_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsString.h"
#include <string>
#include <sstream>

class CsString_Private :public CsObject_Private
{
	CS_DECLARE_OPERATOR_NEW_DELETE

public:
	CsString_Private(CsString *pPublic);
	CsString_Private(CsString *pPublic, const cs_char cChar);
	CsString_Private(CsString *pPublic, const cs_char *pStr);
	CsString_Private(CsString *pPublic, const std::string &sStr);
	CsString_Private(CsString *pPublic, const CsString_Private &sStr);
	~CsString_Private();

	cs_bool Equals(CsString_Private *pStr) const;
	cs_uint64 HashCode() const;

	cs_bool operator==(const CsString_Private &sStr);
	CsString_Private &operator=(const CsString_Private &sStr);
	CsString_Private &operator+=(const CsString_Private &sStr);

	cs_uint GetSize() const;
	cs_bool IsEmpty() const;
	cs_cstring GetCStr() const;

	cs_void MakeTrim();
	cs_void MakeUpper();
	cs_void MakeLower();
	cs_void Format(const char *format, ...);

	template <typename T>
	static CsString FromNum(T nNum, cs_int nBase);

	template <typename T>
	T ToNum(cs_bool *bIsOk = NULL) const;

private:
	std::string m_sStr;
};

template <typename T>
CsString CsString_Private::FromNum(T nNum, cs_int nBase)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	oss << nNum;
	return CsString(oss.str());
}

template <typename T>
T CsString_Private::ToNum(cs_bool *bIsOk) const
{
	std::istringstream iss(m_sStr.c_str());
	T nNum;
	if (bIsOk)
	{
		*bIsOk = false;
	}
	if (iss >> nNum)
	{
		if (bIsOk)
		{
			*bIsOk = true;
		}
	}
	return nNum;
}

#endif // _CORE_STRING_PRIVATE_H_
