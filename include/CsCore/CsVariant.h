#ifndef _CORE_VARIANT_H_
#define _CORE_VARIANT_H_

#include "CsObject.h"
#include "CsString.h"

enum CS_VARIANT_TYPE
{
	VARIANT_TYPE_ILLEGAL = -1,
	VARIANT_TYPE_BOOL,
	VARIANT_TYPE_CHAR,
	VARIANT_TYPE_UCHAR,
	VARIANT_TYPE_WCHAR,
	VARIANT_TYPE_SHORT,
	VARIANT_TYPE_USHORT,
	VARIANT_TYPE_INT,
	VARIANT_TYPE_UINT,
	VARIANT_TYPE_LONG,
	VARIANT_TYPE_ULONG,
	VARIANT_TYPE_LONGLONG,
	VARIANT_TYPE_ULONGLONG,	// longlong
	VARIANT_TYPE_FLOAT,
	VARIANT_TYPE_DOUBLE,	// double
	VARIANT_TYPE_STRING,	// ×Ö·û´®
	VARIANT_TYPE_POINTER,	// Ö¸Õë
};

class CS_CORE_EXPORT CsVariant :public CsObject
{
public:
	CsVariant();
	CsVariant(const cs_bool bValue);
	CsVariant(const cs_char cValue);
	CsVariant(const cs_uchar cValue);
	CsVariant(const cs_wchar cValue);
	CsVariant(const cs_short nValue);
	CsVariant(const cs_ushort nValue);
	CsVariant(const cs_int nValue);
	CsVariant(const cs_uint nValue);
	CsVariant(const cs_long nValue);
	CsVariant(const cs_ulong nValue);
	CsVariant(const cs_longlong nValue);
	CsVariant(const cs_ulonglong nValue);
	CsVariant(const cs_float nValue);
	CsVariant(const cs_double nValue);
	CsVariant(cs_cstring sValue);
	CsVariant(const CsString &sValue);
	CsVariant(const cs_pointer pValue);
	CsVariant(const CsVariant &tOther);
	~CsVariant();

	CS_VARIANT_TYPE GetVariantType() const;
	cs_pointer GetPoiter() const;

	void SetPoiter(const cs_pointer pValue);
	void SetValue(const cs_bool bValue);
	void SetValue(const cs_char cValue);
	void SetValue(const cs_uchar cValue);
	void SetValue(const cs_wchar cValue);
	void SetValue(const cs_short nValue);
	void SetValue(const cs_ushort nValue);
	void SetValue(const cs_int nValue);
	void SetValue(const cs_uint nValue);
	void SetValue(const cs_long nValue);
	void SetValue(const cs_ulong nValue);
	void SetValue(const cs_longlong nValue);
	void SetValue(const cs_ulonglong nValue);
	void SetValue(const cs_float nValue);
	void SetValue(const cs_double nValue);
	void SetValue(cs_cstring sValue);
	void SetValue(const CsString &sValue);

	cs_bool ToBool(const cs_bool def = false) const;
	cs_char ToChar(const cs_char def = ' ') const;
	cs_uchar ToUChar(const cs_uchar def = ' ') const;
	cs_wchar ToWChar(const cs_wchar def = ' ') const;
	cs_short ToShort(const cs_short def = 0) const;
	cs_ushort ToUShort(const cs_ushort def = 0) const;
	cs_int ToInt(const cs_int def = 0) const;
	cs_uint ToUInt(const cs_uint def = 0) const;
	cs_long ToLong(const cs_long def = 0) const;
	cs_ulong ToULong(const cs_ulong def = 0) const;
	cs_longlong ToLongLong(const cs_longlong def = 0) const;
	cs_ulonglong ToULongLong(const cs_ulonglong def = 0) const;
	cs_float ToFloat(const cs_float def = 0) const;
	cs_double ToDouble(const cs_double def = 0) const;
	CsString ToString(const CsString &def = "") const;

	cs_byte ToByte(const cs_byte &def = 0) const;
	cs_int8 ToInt8(const cs_int8 &def = 0) const;
	cs_uint8 ToUInt8(const cs_uint8 &def = 0) const;
	cs_int16 ToInt16(const cs_int16 &def = 0) const;
	cs_uint16 ToUInt16(const cs_uint16 &def = 0) const;
	cs_int32 ToInt32(const cs_int32 &def = 0) const;
	cs_uint32 ToUInt32(const cs_uint32 &def = 0) const;
	cs_int64 ToInt64(const cs_int64 &def = 0) const;
	cs_uint64 ToUInt64(const cs_uint64 &def = 0) const;
	cs_size_t ToSizeType(const cs_size_t &def = 0) const;
};

#endif // _CORE_VARIANT_H_