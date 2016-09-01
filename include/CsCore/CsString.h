#ifndef _CSCORE_CSSTRING_H_
#define _CSCORE_CSSTRING_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"
#include <string>

class CsStringList;

class CS_CORE_EXPORT CsString final :public CsObject
{
public:
	CsString();
	CsString(const cs_char cChar);
	CsString(const cs_char *pStr);
	CsString(const std::string &sStr);
	CsString(const CsString &sStr);
	~CsString();

	friend CS_CORE_EXPORT CsString operator+(const CsString &s1, const CsString &s2);
	CsString &operator=(const CsString &sStr);
	CsString &operator+=(const CsString &sStr);

	static CsString FromNum(cs_short nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ushort nNum, cs_int nBase = 10);
	static CsString FromNum(cs_int nNum, cs_int nBase = 10);
	static CsString FromNum(cs_uint nNum, cs_int nBase = 10);
	static CsString FromNum(cs_long nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ulong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_longlong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_ulonglong nNum, cs_int nBase = 10);
	static CsString FromNum(cs_float nNum, cs_int nBase = 10);
	static CsString FromNum(cs_double nNum, cs_int nBase = 10);

	cs_short ToShort(cs_bool *bIsOk = NULL) const;
	cs_ushort ToUShort(cs_bool *bIsOk = NULL) const;
	cs_int ToInt(cs_bool *bIsOk = NULL) const;
	cs_uint ToUInt(cs_bool *bIsOk = NULL) const;
	cs_long ToLong(cs_bool *bIsOk = NULL) const;
	cs_ulong ToULong(cs_bool *bIsOk = NULL) const;
	cs_longlong ToLongLong(cs_bool *bIsOk = NULL) const;
	cs_ulonglong ToULongLong(cs_bool *bIsOk = NULL) const;
	cs_float ToFloat(cs_bool *bIsOk = NULL) const;
	cs_double ToDouble(cs_bool *bIsOk = NULL) const;
	cs_decimal ToDecimal(cs_bool *bIsOk = NULL) const;

	cs_bool IsEmpty() const;
	CsString Trim() const;
	CsString ToUpper() const;
	CsString ToLower() const;
	cs_cstring GetCStr() const;

	CsObject *CopyToObject() const;
	cs_uint ClassCode() const;
	CsString ToString() const;
	CsString Format() const;

private:
	void MakeTrim();
	void MakeUpper();
	void MakeLower();

public:
	enum { CLASSCODE = CORE_CLASSCODE_STRING, };
};

CS_CORE_EXPORT CsString operator+(const CsString &s1, const CsString &s2);

#endif // _CSCORE_CSSTRING_H_
