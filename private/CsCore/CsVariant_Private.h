#ifndef _CORE_VARIANT_PRIVATE_H_
#define _CORE_VARIANT_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsVariant.h"

class CsVariant_Private :public CsObject_Private
{
public:
	CsVariant_Private(CsVariant *pPublic);
	CsVariant_Private(CsVariant *pPublic, const cs_bool bValue);
	CsVariant_Private(CsVariant *pPublic, const cs_char cValue);
	CsVariant_Private(CsVariant *pPublic, const cs_uchar cValue);
	CsVariant_Private(CsVariant *pPublic, const cs_wchar cValue);
	CsVariant_Private(CsVariant *pPublic, const cs_short nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_ushort nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_int nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_uint nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_long nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_ulong nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_longlong nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_ulonglong nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_float nValue);
	CsVariant_Private(CsVariant *pPublic, const cs_double nValue);
	CsVariant_Private(CsVariant *pPublic, const CsString &sValue);
	CsVariant_Private(CsVariant *pPublic, const cs_pointer pValue);
	CsVariant_Private(CsVariant *pPublic, const CsVariant_Private &tOther);
	~CsVariant_Private();

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
	void SetValue(const CsString &sValue);

	cs_bool ToBool(const cs_bool bDefValue) const;
	cs_char ToChar(const cs_char cDefValue) const;
	cs_uchar ToUChar(const cs_uchar cDefValue) const;
	cs_wchar ToWChar(const cs_wchar cDefValue) const;
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
	CsString ToString(const CsString &sDefValue) const;
	
private:
	void ClearMemery();
	union
	{
		cs_bool			m_bVal;
		cs_char			m_cVal;
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
		cs_pointer			m_pVal;
	};
	CS_VARIANT_TYPE m_emType;
};

#endif // _CORE_VARIANT_PRIVATE_H_