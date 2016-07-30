#include "CsString.h"
#include "CsString_Private.h"

CsString::CsString()
: CsObject(new CsString_Private(this))
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

cs_uint CsString::ClassCode() const
{
	return CsString::CLASSCODE;
}

CsString CsString::ToString() const
{
	return *this;
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

CsString CsString::FromNum(cs_int nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_int>(nNum, nBase);
}

CsString CsString::FromNum(cs_double nNum, cs_int nBase)
{
	return CsString_Private::FromNum<cs_double>(nNum, nBase);
}

cs_int CsString::ToInt(cs_bool *bIsOk) const
{
	CS_PRIVATE(CsString);
	return pPrivate->ToNum<cs_int>(bIsOk);
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

cs_ccharptr CsString::GetCStr() const
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