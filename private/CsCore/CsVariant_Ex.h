#ifndef _CORE_VARIANT_EX_H_
#define _CORE_VARIANT_EX_H_

#include "CsGlobal.h"
#include "CsVariant.h"

class CsVariant_Ex
	: public CsNewT<CsVariant_Ex>
{
public:
	CsVariant_Ex();
	CsVariant_Ex(cs_bool bValue);
	CsVariant_Ex(cs_char cValue);
	CsVariant_Ex(cs_schar cValue);
	CsVariant_Ex(cs_uchar cValue);
	CsVariant_Ex(cs_wchar cValue);
	CsVariant_Ex(cs_short nValue);
	CsVariant_Ex(cs_ushort nValue);
	CsVariant_Ex(cs_int nValue);
	CsVariant_Ex(cs_uint nValue);
	CsVariant_Ex(cs_long nValue);
	CsVariant_Ex(cs_ulong nValue);
	CsVariant_Ex(cs_longlong nValue);
	CsVariant_Ex(cs_ulonglong nValue);
	CsVariant_Ex(cs_float nValue);
	CsVariant_Ex(cs_double nValue);
	CsVariant_Ex(cs_decimal nValue);
	CsVariant_Ex(const CsString &sValue);
	CsVariant_Ex(const CsObject &tValue);
	CsVariant_Ex(const CsObjectP &pValue);
	CsVariant_Ex(const cs_pointer pValue);
	CsVariant_Ex(const CsVariant_Ex &tOther);
	~CsVariant_Ex();

	CS_VARIANT_TYPE GetVariantType() const;
	cs_pointer GetPoiter() const;
	cs_void SetPoiter(const cs_pointer pValue);

	cs_void SetValue(cs_bool bValue);
	cs_void SetValue(cs_char cValue);
	cs_void SetValue(cs_schar cValue);
	cs_void SetValue(cs_uchar cValue);
	cs_void SetValue(cs_wchar cValue);
	cs_void SetValue(cs_short nValue);
	cs_void SetValue(cs_ushort nValue);
	cs_void SetValue(cs_int nValue);
	cs_void SetValue(cs_uint nValue);
	cs_void SetValue(cs_long nValue);
	cs_void SetValue(cs_ulong nValue);
	cs_void SetValue(cs_longlong nValue);
	cs_void SetValue(cs_ulonglong nValue);
	cs_void SetValue(cs_float nValue);
	cs_void SetValue(cs_double nValue);
	cs_void SetValue(cs_decimal nValue);
	cs_void SetValue(const CsString &sValue);
	cs_void SetValue(const CsObject &tValue);

	cs_bool ToBool(const cs_bool bDefValue) const;
	cs_char ToChar(const cs_char cDefValue) const;
	cs_schar ToSChar(const cs_schar cDefValue) const;
	cs_uchar ToUChar(const cs_uchar cDefValue) const;
	cs_wchar ToWChar(const cs_wchar cDefValue) const;
	cs_small ToSmall(const cs_small nDefValue) const;
	cs_usmall ToUSmall(const cs_usmall nDefValue) const;
	cs_short ToShort(const cs_short nDefValue) const;
	cs_ushort ToUShort(const cs_ushort nDefValue) const;
	cs_int ToInt(const cs_int nDefValue) const;
	cs_uint ToUInt(const cs_uint nDefValue) const;
	cs_long ToLong(const cs_long nDefValue) const;
	cs_ulong ToULong(const cs_ulong nDefValue) const;
	cs_longlong ToLongLong(const cs_longlong nDefValue) const;
	cs_ulonglong ToULongLong(const cs_ulonglong nDefValue) const;
	cs_float ToFloat(const cs_float nDefValue) const;
	cs_double ToDouble(const cs_double nDefValue) const;
	cs_decimal ToDecimal(const cs_decimal nDefValue) const;
	CsString ToString(const CsString &sDefValue) const;
	CsObject *ToObject() const;

	cs_bool IsValid() const;

	CsVariant_Ex &operator=(const CsVariant_Ex &var);
	
private:
	cs_void ClearMemery();

	template<typename BaseT, typename PackageT>
	BaseT ToNumber(const cs_uint nClassCode, const BaseT &nDefValue) const;

	union
	{
		cs_bool			m_bVal;
		cs_char			m_cVal;
		cs_schar		m_scVal;
		cs_uchar		m_ucVal;
		cs_wchar		m_wcVal;
		cs_short		m_sVal;
		cs_ushort		m_usVal;
		cs_int			m_iVal;
		cs_uint			m_uiVal;
		cs_long			m_lVal;
		cs_ulong		m_ulVal;
		cs_longlong		m_llVal;
		cs_ulonglong	m_ullVal;
		cs_float		m_fVal;
		cs_double		m_dVal;
		cs_decimal		m_decVal;
		cs_pointer		m_pVal;
		CsStringStore	m_strVal;
	};
	cs_byte m_nType;
};

template<typename BaseT, typename PackageT>
BaseT CsVariant_Ex::ToNumber(const cs_uint nClassCode, const BaseT &nDefValue) const
{
	// TODO
	return BaseT();
}

#endif // _CORE_VARIANT_PRIVATE_H_