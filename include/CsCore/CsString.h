#ifndef _CSCORE_CSSTRING_H_
#define _CSCORE_CSSTRING_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"
#include <string>

class CsStringList;

class CsCore_Export CsString final :public CsObject
{
public:
	CsString();
	CsString(const cs_char *pStr);
	CsString(const std::string &sStr);
	CsString(const CsString &sStr);
	~CsString();

	friend CsCore_Export CsString operator+(const CsString &s1, const CsString &s2);
	CsString &operator=(const CsString &sStr);
	CsString &operator+=(const CsString &sStr);

	static CsString FromNum(cs_int nNum, cs_int nBase = 10);
	static CsString FromNum(cs_double nNum, cs_int nBase = 10);

	cs_int ToInt(cs_bool *bIsOk = NULL) const;
	cs_bool IsEmpty() const;
	CsString Trim() const;
	CsString ToUpper() const;
	CsString ToLower() const;
	cs_ccharptr GetCStr() const;

	CsObject *CopyToObject() const;
	cs_uint ClassCode() const;
	CsString ToString() const;

private:
	void MakeTrim();
	void MakeUpper();
	void MakeLower();

public:
	enum { CLASSCODE = CORE_CLASSCODE_STRING, };
};

CsCore_Export CsString operator+(const CsString &s1, const CsString &s2);

#endif // _CSCORE_CSSTRING_H_
