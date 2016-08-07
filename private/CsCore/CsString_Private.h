#ifndef _CSCORE_CSSTRING_PRIVATE_H_
#define _CSCORE_CSSTRING_PRIVATE_H_

#include "CsType.h"
#include "CsObject_Private.h"
#include "CsString.h"
#include <string>
#include <sstream>

class CsString_Private :public CsObject_Private
{
public:
	CsString_Private(CsString *pPublic);
	CsString_Private(CsString *pPublic, const cs_char *pStr);
	CsString_Private(CsString *pPublic, const std::string &sStr);
	CsString_Private(CsString *pPublic, const CsString_Private &sStr);
	~CsString_Private();

	cs_bool Equals(CsString_Private *pStr) const;
	cs_uint64 HashCode() const;

	CsString_Private &operator=(const CsString_Private &sStr);
	CsString_Private &operator+=(const CsString_Private &sStr);

	cs_uint GetSize() const;
	cs_bool IsEmpty() const;
	cs_ccharptr GetCStr() const;

	void MakeTrim();
	void MakeUpper();
	void MakeLower();

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
	std::istringstream iss(m_sStr);
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

#endif // _CSCORE_CSSTRING_PRIVATE_H_
