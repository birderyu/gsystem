#include "CsBytes.h"
#include "CsBytes_Ex.h"
#include "CsString.h"

CsBytes::CsBytes(cs_size_t nBufSize)
: m_pBytes_Ex(new CsBytes_Ex(nBufSize))
{
	CS_ASSERT(m_pBytes_Ex);
}

CsBytes::CsBytes(const CsBytes &tBytes)
: m_pBytes_Ex(new CsBytes_Ex(*tBytes.m_pBytes_Ex))
{
	CS_ASSERT(m_pBytes_Ex);
}

CsBytes::~CsBytes()
{
	delete m_pBytes_Ex;
}

cs_void CsBytes::Clear()
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->Clear();
}

cs_bool CsBytes::IsEmpty() const
{
	CS_ASSERT(m_pBytes_Ex);
	return m_pBytes_Ex->IsEmpty();
}

cs_byte *CsBytes::GetBuffer() const
{
	CS_ASSERT(m_pBytes_Ex);
	return m_pBytes_Ex->GetHead();
}

cs_size_t CsBytes::Length() const
{
	CS_ASSERT(m_pBytes_Ex);
	return m_pBytes_Ex->Length();
}

cs_bool CsBytes::ReadFrom(const cs_byte *pBuf, cs_size_t len)
{
	CS_ASSERT(m_pBytes_Ex);
	return m_pBytes_Ex->ReadFrom(pBuf, len);
}

cs_bool CsBytes::WriteTo(cs_size_t len, cs_byte *&pBuf)
{
	CS_ASSERT(m_pBytes_Ex);
	return m_pBytes_Ex->WriteTo(len, pBuf);
}

cs_bool CsBytes::WriteAllTo(cs_byte *&pBuf)
{
	return WriteTo(Length(), pBuf);
}

CsBytes &CsBytes::operator<<(cs_bool val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_bool>((cs_bool)val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_char val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_char>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_schar val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_schar>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_uchar val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_uchar>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_wchar val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_wchar>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_short val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_short>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ushort val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_ushort>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_int val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_int>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_uint val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_uint>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_long val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_long>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ulong val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_ulong>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_longlong val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_longlong>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ulonglong val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_ulonglong>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_float val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_float>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_double val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_double>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_decimal val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator<<<cs_decimal>(val);
	return *this;
}

CsBytes &CsBytes::operator<<(const CsString &val)
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->ReadFrom(val.CString());
	return *this;
}

CsBytes &CsBytes::operator<<(const CsBytes &val)
{
	ReadFrom(val.GetBuffer(), val.Length());
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_bool &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_bool>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_char &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_char>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_schar &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_schar>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uchar &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_uchar>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_wchar &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_wchar>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_short &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_short>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_ushort &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_ushort>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_int &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_int>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uint &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_uint>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_long &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_long>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_ulong &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_ulong>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_longlong &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_longlong>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_ulonglong &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_ulonglong>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_float &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_float>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_double &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_double>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_decimal &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	m_pBytes_Ex->operator>><cs_decimal>(val);
	return *this;
}

const CsBytes &CsBytes::operator>>(CsString &val) const
{
	CS_ASSERT(m_pBytes_Ex);
	cs_char c[CS_DEFAULT_BUF_SIZE];
	if (m_pBytes_Ex->WriteToStr(c, CS_DEFAULT_BUF_SIZE))
	{
		val = c;
	}
	return *this;
}

const CsBytes &CsBytes::operator>>(CsBytes &val) const
{
	// TODO
	return *this;
}