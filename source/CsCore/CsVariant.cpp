#include "CsVariant.h"
#include "CsVariant_Ex.h"

CsVariant::CsVariant()
: m_pVariant_Ex(new CsVariant_Ex())
{

}

CsVariant::CsVariant(cs_bool bValue)
: m_pVariant_Ex(new CsVariant_Ex(bValue))
{

}

CsVariant::CsVariant(cs_char cValue)
: m_pVariant_Ex(new CsVariant_Ex(cValue))
{

}

CsVariant::CsVariant(cs_uchar cValue)
: m_pVariant_Ex(new CsVariant_Ex(cValue))
{

}

CsVariant::CsVariant(cs_wchar cValue)
: m_pVariant_Ex(new CsVariant_Ex(cValue))
{

}

CsVariant::CsVariant(cs_short nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_ushort nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_int nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_uint nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_long nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_ulong nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_longlong nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_ulonglong nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_float nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_double nValue)
: m_pVariant_Ex(new CsVariant_Ex(nValue))
{

}

CsVariant::CsVariant(cs_cstring sValue)
: m_pVariant_Ex(new CsVariant_Ex(CsString(sValue)))
{

}

CsVariant::CsVariant(const CsString &sValue)
: m_pVariant_Ex(new CsVariant_Ex(sValue))
{

}

CsVariant::CsVariant(const CsObject &tValue)
: m_pVariant_Ex(new CsVariant_Ex(tValue))
{

}

CsVariant::CsVariant(const cs_pointer pValue)
: m_pVariant_Ex(new CsVariant_Ex(pValue))
{

}

CsVariant::CsVariant(const CsVariant &tOther)
: m_pVariant_Ex(new CsVariant_Ex(*tOther.m_pVariant_Ex))
{

}

CsVariant::~CsVariant()
{
	if (m_pVariant_Ex)
	{
		delete m_pVariant_Ex;
	}
}

CS_VARIANT_TYPE CsVariant::GetVariantType() const
{
	return m_pVariant_Ex->GetVariantType();
}

cs_pointer CsVariant::GetPoiter() const
{
	return m_pVariant_Ex->GetPoiter();
}

cs_void CsVariant::SetPoiter(const cs_pointer pValue)
{
	m_pVariant_Ex->SetPoiter(pValue);
}

cs_void CsVariant::SetValue(const cs_bool bValue)
{
	m_pVariant_Ex->SetValue(bValue);
}

cs_void CsVariant::SetValue(const cs_char cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_uchar cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_wchar cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_short nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ushort nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_int nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_uint nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_long nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ulong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_longlong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ulonglong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_float nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_double nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

cs_void CsVariant::SetValue(cs_cstring sValue)
{
	m_pVariant_Ex->SetValue(CsString(sValue));
}

cs_void CsVariant::SetValue(const CsString &sValue)
{
	m_pVariant_Ex->SetValue(sValue);
}

cs_void CsVariant::SetValue(const CsObject &tValue)
{
	m_pVariant_Ex->SetValue(tValue);
}

cs_bool CsVariant::ToBool(const cs_bool def) const
{
	return m_pVariant_Ex->ToBool(def);
}

cs_char CsVariant::ToChar(const cs_char def) const
{
	return m_pVariant_Ex->ToChar(def);
}

cs_uchar CsVariant::ToUChar(const cs_uchar def) const
{
	return m_pVariant_Ex->ToUChar(def);
}

cs_wchar CsVariant::ToWChar(const cs_wchar def) const
{
	return m_pVariant_Ex->ToWChar(def);
}

cs_small CsVariant::ToSmall(const cs_small def) const
{
	return m_pVariant_Ex->ToSmall(def);
}

cs_usmall CsVariant::ToUSmall(const cs_usmall def) const
{
	return m_pVariant_Ex->ToUSmall(def);
}

cs_short CsVariant::ToShort(const cs_short def) const
{
	return m_pVariant_Ex->ToShort(def);
}

cs_ushort CsVariant::ToUShort(const cs_ushort def) const
{
	return m_pVariant_Ex->ToUShort(def);
}

cs_int CsVariant::ToInt(const cs_int def) const
{
	return m_pVariant_Ex->ToInt(def);
}

cs_uint CsVariant::ToUInt(const cs_uint def) const
{
	return m_pVariant_Ex->ToUInt(def);
}

cs_long CsVariant::ToLong(const cs_long def) const
{
	return m_pVariant_Ex->ToLong(def);
}

cs_ulong CsVariant::ToULong(const cs_ulong def) const
{
	return m_pVariant_Ex->ToULong(def);
}

cs_longlong CsVariant::ToLongLong(const cs_longlong def) const
{
	return m_pVariant_Ex->ToLongLong(def);
}

cs_ulonglong CsVariant::ToULongLong(const cs_ulonglong def) const
{
	return m_pVariant_Ex->ToULongLong(def);
}

cs_float CsVariant::ToFloat(const cs_float def) const
{
	return m_pVariant_Ex->ToFloat(def);
}

cs_double CsVariant::ToDouble(const cs_double def) const
{
	return m_pVariant_Ex->ToDouble(def);
}

CsString CsVariant::ToString(const CsString &def) const
{
	return m_pVariant_Ex->ToString(def);
}

CsObject *CsVariant::ToObject() const
{
	return m_pVariant_Ex->ToObject();
}

cs_byte CsVariant::ToByte(const cs_byte &def) const
{
	return ToUChar(def);
}

cs_int8 CsVariant::ToInt8(const cs_int8 &def) const
{
	return ToSmall(def);
}

cs_uint8 CsVariant::ToUInt8(const cs_uint8 &def) const
{
	return ToUSmall(def);
}

cs_int16 CsVariant::ToInt16(const cs_int16 &def) const
{
	return ToShort(def);
}

cs_uint16 CsVariant::ToUInt16(const cs_uint16 &def) const
{
	return ToUShort(def);
}

cs_int32 CsVariant::ToInt32(const cs_int32 &def) const
{
	return ToInt(def);
}

cs_uint32 CsVariant::ToUInt32(const cs_uint32 &def) const
{
	return ToUInt(def);
}

cs_int64 CsVariant::ToInt64(const cs_int64 &def) const
{
	return ToLongLong(def);
}

cs_uint64 CsVariant::ToUInt64(const cs_uint64 &def) const
{
	return ToULongLong(def);
}

cs_size_t CsVariant::ToSizeType(const cs_size_t &def) const
{
	return ToUInt(def);
}

cs_bool CsVariant::IsValid() const
{
	return m_pVariant_Ex->IsValid();
}

CsVariant &CsVariant::operator = (const CsVariant &var)
{
	m_pVariant_Ex->operator=(*var.m_pVariant_Ex);
	return *this;
}