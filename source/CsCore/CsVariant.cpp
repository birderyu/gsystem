#include "CsVariant.h"
#include "CsVariant_Private.h"

CsVariant::CsVariant()
: CsObject(new CsVariant_Private(this))
{

}

CsVariant::CsVariant(const cs_bool bValue)
: CsObject(new CsVariant_Private(this, bValue))
{

}

CsVariant::CsVariant(const cs_char cValue)
: CsObject(new CsVariant_Private(this, cValue))
{

}

CsVariant::CsVariant(const cs_uchar cValue)
: CsObject(new CsVariant_Private(this, cValue))
{

}

CsVariant::CsVariant(const cs_wchar cValue)
: CsObject(new CsVariant_Private(this, cValue))
{

}

CsVariant::CsVariant(const cs_short nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_ushort nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_int nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_uint nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_long nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_ulong nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_longlong nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_ulonglong nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_float nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(const cs_double nValue)
: CsObject(new CsVariant_Private(this, nValue))
{

}

CsVariant::CsVariant(cs_cstring sValue)
: CsObject(new CsVariant_Private(this, CsString(sValue)))
{

}

CsVariant::CsVariant(const CsString &sValue)
: CsObject(new CsVariant_Private(this, sValue))
{

}

CsVariant::CsVariant(const CsObject &tValue)
: CsObject(new CsVariant_Private(this, tValue))
{

}

CsVariant::CsVariant(const cs_pointer pValue)
: CsObject(new CsVariant_Private(this, pValue))
{

}

CsVariant::CsVariant(const CsVariant &tOther)
: CsObject(new CsVariant_Private(this, *(CsVariant_Private*)tOther.m_pPrivate))
{

}

CsVariant::~CsVariant()
{

}

CS_VARIANT_TYPE CsVariant::GetVariantType() const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->GetVariantType();
}

cs_pointer CsVariant::GetPoiter() const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->GetPoiter();
}

cs_void CsVariant::SetPoiter(const cs_pointer pValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetPoiter(pValue);
}

cs_void CsVariant::SetValue(const cs_bool bValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(bValue);
}

cs_void CsVariant::SetValue(const cs_char cValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_uchar cValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_wchar cValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(cValue);
}

cs_void CsVariant::SetValue(const cs_short nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ushort nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_int nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_uint nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_long nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ulong nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_longlong nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_ulonglong nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_float nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(const cs_double nValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(nValue);
}

cs_void CsVariant::SetValue(cs_cstring sValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(CsString(sValue));
}

cs_void CsVariant::SetValue(const CsString &sValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(sValue);
}

cs_void CsVariant::SetValue(const CsObject &tValue)
{
	CS_PRIVATE(CsVariant);
	pPrivate->SetValue(tValue);
}

cs_bool CsVariant::ToBool(const cs_bool def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToBool(def);
}

cs_char CsVariant::ToChar(const cs_char def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToChar(def);
}

cs_uchar CsVariant::ToUChar(const cs_uchar def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToUChar(def);
}

cs_wchar CsVariant::ToWChar(const cs_wchar def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToWChar(def);
}

cs_short CsVariant::ToShort(const cs_short def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToShort(def);
}

cs_ushort CsVariant::ToUShort(const cs_ushort def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToUShort(def);
}

cs_int CsVariant::ToInt(const cs_int def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToInt(def);
}

cs_uint CsVariant::ToUInt(const cs_uint def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToUInt(def);
}

cs_long CsVariant::ToLong(const cs_long def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToLong(def);
}

cs_ulong CsVariant::ToULong(const cs_ulong def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToULong(def);
}

cs_longlong CsVariant::ToLongLong(const cs_longlong def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToLongLong(def);
}

cs_ulonglong CsVariant::ToULongLong(const cs_ulonglong def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToULongLong(def);
}

cs_float CsVariant::ToFloat(const cs_float def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToFloat(def);
}

cs_double CsVariant::ToDouble(const cs_double def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToDouble(def);
}

CsString CsVariant::ToString(const CsString &def) const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToString(def);
}

CsObject *CsVariant::ToObject() const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->ToObject();
}

cs_byte CsVariant::ToByte(const cs_byte &def) const
{
	return ToUChar(def);
}

cs_int8 CsVariant::ToInt8(const cs_int8 &def) const
{
	return ToChar(def);
}

cs_uint8 CsVariant::ToUInt8(const cs_uint8 &def) const
{
	return ToUChar(def);
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

cs_bool CsVariant::Valid() const
{
	CS_PRIVATE(CsVariant);
	return pPrivate->Valid();
}