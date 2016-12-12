#include "CsString.h"
#include "CsString_Ex.h"

CsString::CsString()
: m_pString_Ex(new CsString_Ex())
{

}

CsString::CsString(const cs_char cChar)
: m_pString_Ex(new CsString_Ex(cChar))
{

}

CsString::CsString(const cs_char *pStr)
: m_pString_Ex(new CsString_Ex(pStr))
{

}

CsString::CsString(const CsString &sStr)
: m_pString_Ex(sStr.m_pString_Ex)
{
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
}

CsObject *CsString::Boxing() const
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

cs_bool CsString::operator == (const CsString &sStr) const
{
	return *m_pString_Ex == *sStr.m_pString_Ex;
}

CsString &CsString::operator+=(const CsString &sStr)
{
	if (m_pString_Ex.IsShared())
	{
		m_pString_Ex.Reset(new CsString_Ex(*m_pString_Ex));
	}
	*m_pString_Ex += *sStr.m_pString_Ex;
	return *this;
}

CsString &CsString::operator=(const CsString &sStr)
{
	if (m_pString_Ex.IsShared())
	{
		//m_pString_Ex.Reset(new CsString_Ex(*m_pString_Ex));
		// 由于下一步就要做拷贝操作，因此只需要重置一个空字符串即可
		m_pString_Ex.Reset(new CsString_Ex());
	}
	*m_pString_Ex = *sStr.m_pString_Ex;
	return *this;
}

cs_char CsString::operator[](cs_size_t id) const
{
	return m_pString_Ex->GetAt(id);
}

CsString CsString::FromNum(cs_small nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_small>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_usmall nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_usmall>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_short nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_short>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_ushort nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_ushort>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_int nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_int>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_uint nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_uint>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_long nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_long>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_ulong nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_ulong>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_longlong nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_longlong>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_ulonglong nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_ulonglong>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_float nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_float>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_double nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_double>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromNum(cs_decimal nNum, cs_int nBase)
{
	CsString sStr;
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	CsString_Ex::FromNum<cs_decimal>(nNum, nBase, *sStr.m_pString_Ex);
	return sStr;
}

CsString CsString::FromStdString(const std::string &sStr)
{
	return CsString(sStr.c_str());
}

cs_small CsString::ToSmall(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_small>(bIsOk);
}

cs_usmall CsString::ToUSmall(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_usmall>(bIsOk);
}

cs_short CsString::ToShort(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_short>(bIsOk);
}

cs_ushort CsString::ToUShort(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_ushort>(bIsOk);
}

cs_int CsString::ToInt(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_int>(bIsOk);
}

cs_uint CsString::ToUInt(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_uint>(bIsOk);
}

cs_long CsString::ToLong(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_long>(bIsOk);
}

cs_ulong CsString::ToULong(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_ulong>(bIsOk);
}

cs_longlong CsString::ToLongLong(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_longlong>(bIsOk);
}

cs_ulonglong CsString::ToULongLong(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_ulonglong>(bIsOk);
}

cs_float CsString::ToFloat(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_float>(bIsOk);
}

cs_double CsString::ToDouble(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_double>(bIsOk);
}

cs_decimal CsString::ToDecimal(cs_bool *bIsOk) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->ToNum<cs_decimal>(bIsOk);
}

cs_bool CsString::IsEmpty() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());

	return m_pString_Ex->IsEmpty();
}

CsString CsString::Trim() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CsString sStr(*this);
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	sStr.m_pString_Ex->MakeTrim();
	return sStr;
}

CsString CsString::TrimLeft() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CsString sStr(*this);
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	sStr.m_pString_Ex->MakeTrimLeft();
	return sStr;
}

CsString CsString::TrimRight() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CsString sStr(*this);
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	sStr.m_pString_Ex->MakeTrimRight();
	return sStr;
}

CsString CsString::ToUpper() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CsString sStr(*this);
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	sStr.m_pString_Ex->MakeUpper();
	return sStr;
}

CsString CsString::ToLower() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CsString sStr(*this);
	CS_ASSERT(!sStr.m_pString_Ex.IsNull());
	sStr.m_pString_Ex->MakeLower();
	return sStr;
}

cs_cstring CsString::CString() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->CString();
}

cs_size_t CsString::Size() const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->Length();
}

cs_char CsString::GetAt(cs_size_t id) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return m_pString_Ex->GetAt(id);
}

CsString &CsString::Replace(const CsString &from, const CsString &to, cs_bool bIsSensitive)
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	CS_ASSERT(!from.m_pString_Ex.IsNull());
	CS_ASSERT(!to.m_pString_Ex.IsNull());

	if (m_pString_Ex.IsShared())
	{
		m_pString_Ex.Reset(new CsString_Ex(*m_pString_Ex));
	}

	if (Size() <= 0 || from.Size() <= 0)
	{
		return *this;
	}

	cs_cstring cfrom = from.CString();
	cs_cstring cto = to.CString();
	cs_size_t to_len = to.Size();
	if (!cfrom ||
		(!cto && to_len >= 0))
	{
		return *this;
	}

	m_pString_Ex->Replace(cfrom, from.Size(), cto, to_len, bIsSensitive);
	return *this;
}

CsStringList CsString::Split(const CsString &sSep, cs_bool bIgnoreEmpty, cs_bool bIsSensitive) const
{
	CsStringList t;
	return t;
}

cs_int CsString::Find(cs_char c, cs_size_t start, cs_bool bIsSensitive) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return -1;
}

cs_int CsString::Find(const CsString &str, cs_size_t start, cs_bool bIsSensitive) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return -1;
}

CsString CsString::SubString(cs_size_t start, cs_size_t length) const
{
	CS_ASSERT(!m_pString_Ex.IsNull());
	return "";
}

cs_bool CsString::Equals(const CsString &str, cs_bool bIsSensitive) const
{
	if (bIsSensitive)
	{
		return *this == str;
	}
	return false;
}

CsString operator+(const CsString &s1, const CsString &s2)
{
	CsString sStr(s1);
	sStr += s2;
	return sStr;
}

/*
cs_bool operator==(const CsString &s1, const CsString &s2)
{
	return s1.operator==(s2);
}
*/