#include "CsString.h"
#include "CsString_Private.h"

CsString::CsString()
: CsObject(new CsString_Private(this))
{

}

CsString::CsString(const cs_char cChar)
: CsObject(new CsString_Private(this, cChar))
{

}

CsString::CsString(const cs_char *pStr)
: CsObject(new CsString_Private(this, pStr))
{

}

CsString::CsString(const std::string &sStr)
: CsObject(new CsString_Private(this, sStr))
{

}

CsString::CsString(const CsString &sStr)
: CsObject(new CsString_Private(this, *(CsString_Private*)sStr.m_pPrivate))
{

}

CsString::~CsString()
{
	
}

CsObject *CsString::CopyToObject() const
{
	return new CsString(*this);
}

cs_uint CsString::ClassCode() const
{
	return CsString::CLASSCODE;
}

CsString CsString::ToString() const
{
	return *this;
}

cs_bool CsString::operator == (const CsString &sStr)
{
	CS_PRIVATE(CsString);
	return *pPrivate == *(CsString_Private*)sStr.GetPrivate();
}

CsString &CsString::operator+=(const CsString &sStr)
{
	CS_PRIVATE(CsString);
	*pPrivate += *(CsString_Private*)sStr.GetPrivate();
	return *this;
}

CsString &CsString::operator=(const CsString &sStr)
{
	CS_PRIVATE(CsString);
	*pPrivate = *(CsString_Private*)sStr.GetPrivate();
	return *this;
}

CsString CsString::FromNum(cs_short nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_short>(nNum, nBase);
}

CsString CsString::FromNum(cs_ushort nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_ushort>(nNum, nBase);
}

CsString CsString::FromNum(cs_int nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_int>(nNum, nBase);
}

CsString CsString::FromNum(cs_uint nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_uint>(nNum, nBase);
}

CsString CsString::FromNum(cs_long nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_long>(nNum, nBase);
}

CsString CsString::FromNum(cs_ulong nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_ulong>(nNum, nBase);
}

CsString CsString::FromNum(cs_longlong nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_longlong>(nNum, nBase);
}

CsString CsString::FromNum(cs_ulonglong nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_ulonglong>(nNum, nBase);
}

CsString CsString::FromNum(cs_float nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_float>(nNum, nBase);
}

CsString CsString::FromNum(cs_double nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_double>(nNum, nBase);
}

cs_short CsString::ToShort(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_short>(bIsOk);
}

cs_ushort CsString::ToUShort(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_ushort>(bIsOk);
}

cs_int CsString::ToInt(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_int>(bIsOk);
}

cs_uint CsString::ToUInt(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_uint>(bIsOk);
}

cs_long CsString::ToLong(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_long>(bIsOk);
}

cs_ulong CsString::ToULong(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_ulong>(bIsOk);
}

cs_longlong CsString::ToLongLong(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_longlong>(bIsOk);
}

cs_ulonglong CsString::ToULongLong(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_ulonglong>(bIsOk);
}

cs_float CsString::ToFloat(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_float>(bIsOk);
}

cs_double CsString::ToDouble(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_double>(bIsOk);
}

cs_decimal CsString::ToDecimal(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_decimal>(bIsOk);
}

cs_bool CsString::IsEmpty() const
{
	CS_PRIVATE(CsString);
	return pPrivate->IsEmpty();
}

CsString CsString::Trim() const
{
	CsString sStr(*this);
	sStr.MakeTrim();
	return sStr;
}

CsString CsString::ToUpper() const
{
	CsString sStr(*this);
	sStr.MakeUpper();
	return sStr;
}

CsString CsString::ToLower() const
{
	CsString sStr(*this);
	sStr.MakeLower();
	return sStr;
}

cs_cstring CsString::GetCStr() const
{
	CS_PRIVATE(CsString);
	return pPrivate->GetCStr();
}

void CsString::MakeTrim()
{
	CS_PRIVATE(CsString);
	pPrivate->MakeTrim();
}

void CsString::MakeUpper()
{
	CS_PRIVATE(CsString);
	pPrivate->MakeUpper();
}

void CsString::MakeLower()
{
	CS_PRIVATE(CsString);
	pPrivate->MakeLower();
}

CsString operator+(const CsString &s1, const CsString &s2)
{
	CsString sStr(s1);
	sStr += s2;
	return sStr;
}

cs_bool operator==(const CsString &s1, const CsString &s2)
{
	return s1 == s2;
}