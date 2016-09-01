#include "CsVariant_Private.h"
#include "CsString.h"

CsVariant_Private::CsVariant_Private(CsVariant *pPublic)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_ILLEGAL)
, m_pVal(NULL)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_bool bValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_BOOL)
, m_bVal(bValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_char cValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_CHAR)
, m_cVal(cValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_uchar cValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_UCHAR)
, m_ucVal(cValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_wchar cValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_WCHAR)
, m_wcVal(cValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_short nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_SHORT)
, m_sVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_ushort nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_USHORT)
, m_usVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_int nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_INT)
, m_iVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_uint nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_UINT)
, m_uiVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_long nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_LONG)
, m_lVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_ulong nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_ULONG)
, m_ulVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_longlong nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_LONGLONG)
, m_llVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_ulonglong nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_ULONGLONG)
, m_ullVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_float nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_FLOAT)
, m_fVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_double nValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_DOUBLE)
, m_dVal(nValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const CsString &sValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_STRING)
, m_pVal(new CsString(sValue))
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const cs_pointer pValue)
: CsObject_Private(pPublic)
, m_emType(VARIANT_TYPE_POINTER)
, m_pVal(pValue)
{

}

CsVariant_Private::CsVariant_Private(CsVariant *pPublic, const CsVariant_Private &tOther)
: CsObject_Private(pPublic), m_emType(tOther.m_emType)
{
	switch (m_emType)
	{
	case VARIANT_TYPE_ILLEGAL:
		break;
	case VARIANT_TYPE_BOOL:
		m_bVal = tOther.m_bVal;
		break;
	case VARIANT_TYPE_CHAR:
		m_cVal = tOther.m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		m_ucVal = tOther.m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		m_wcVal = tOther.m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		m_sVal = tOther.m_sVal;
		break;
	case VARIANT_TYPE_USHORT:
		m_usVal = tOther.m_usVal;
		break;
	case VARIANT_TYPE_INT:
		m_iVal = tOther.m_iVal;
		break;
	case VARIANT_TYPE_UINT:
		m_uiVal = tOther.m_uiVal;
		break;
	case VARIANT_TYPE_LONG:
		m_lVal = tOther.m_lVal;
		break;
	case VARIANT_TYPE_ULONG:
		m_ulVal = tOther.m_ulVal;
		break;
	case VARIANT_TYPE_LONGLONG:
		m_llVal = tOther.m_llVal;
		break;
	case VARIANT_TYPE_ULONGLONG:
		m_ullVal = tOther.m_ullVal;
		break;
	case VARIANT_TYPE_FLOAT:
		m_fVal = tOther.m_fVal;
		break;
	case VARIANT_TYPE_DOUBLE:
		m_dVal = tOther.m_dVal;
		break;
	case VARIANT_TYPE_STRING:
	{
		if (tOther.m_pVal)
		{
			m_pVal = new CsString(*(CsString*)tOther.m_pVal);
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		m_pVal = tOther.m_pVal;
		break;
	default:
		break;
	}
}

CsVariant_Private::~CsVariant_Private()
{
	ClearMemery();
}

CS_VARIANT_TYPE CsVariant_Private::GetVariantType() const
{
	return m_emType;
}

cs_pointer CsVariant_Private::GetPoiter() const
{
	if (m_emType == VARIANT_TYPE_POINTER)
	{
		return m_pVal;
	}
	return NULL;
}

void CsVariant_Private::SetPoiter(const cs_pointer pValue)
{
	ClearMemery();
	m_pVal = pValue;
}

void CsVariant_Private::SetValue(const cs_bool bValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_BOOL;
	m_bVal = bValue;
}

void CsVariant_Private::SetValue(const cs_char cValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_CHAR;
	m_cVal = cValue;
}

void CsVariant_Private::SetValue(const cs_uchar cValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_USHORT;
	m_ucVal = cValue;
}

void CsVariant_Private::SetValue(const cs_wchar cValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_WCHAR;
	m_wcVal = cValue;
}

void CsVariant_Private::SetValue(const cs_short nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_SHORT;
	m_sVal = nValue;
}

void CsVariant_Private::SetValue(const cs_ushort nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_USHORT;
	m_usVal = nValue;
}

void CsVariant_Private::SetValue(const cs_int nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_INT;
	m_iVal = nValue;
}

void CsVariant_Private::SetValue(const cs_uint nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_UINT;
	m_uiVal = nValue;
}

void CsVariant_Private::SetValue(const cs_long nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_LONG;
	m_lVal = nValue;
}

void CsVariant_Private::SetValue(const cs_ulong nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_ULONG;
	m_ulVal = nValue;
}

void CsVariant_Private::SetValue(const cs_longlong nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_LONGLONG;
	m_llVal = nValue;
}

void CsVariant_Private::SetValue(const cs_ulonglong nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_ULONGLONG;
	m_ullVal = nValue;
}

void CsVariant_Private::SetValue(const cs_float nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_FLOAT;
	m_fVal = nValue;
}

void CsVariant_Private::SetValue(const cs_double nValue)
{
	ClearMemery();
	m_emType = VARIANT_TYPE_DOUBLE;
	m_dVal = nValue;
}

void CsVariant_Private::SetValue(const CsString &sValue)
{
	if (m_emType == VARIANT_TYPE_STRING && m_pVal)
	{
		CsString &sStr = *(CsString*)m_pVal;
		sStr = sValue;
	}
	else
	{
		m_emType = VARIANT_TYPE_STRING;
		m_pVal = new CsString(sValue);
	}
}

cs_bool CsVariant_Private::ToBool(const cs_bool bDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_BOOL:
		return m_bVal;
	case VARIANT_TYPE_CHAR:
		return m_cVal != 0;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal != 0;
	case VARIANT_TYPE_WCHAR:
		return m_wcVal != 0;
	case VARIANT_TYPE_SHORT:
		return m_sVal != 0;
	case VARIANT_TYPE_USHORT:
		return m_usVal != 0;
	case VARIANT_TYPE_INT:
		return m_iVal != 0;
	case VARIANT_TYPE_UINT:
		return m_uiVal != 0;
	case VARIANT_TYPE_LONG:
		return m_lVal != 0;
	case VARIANT_TYPE_ULONG:
		return m_ulVal != 0;
	case VARIANT_TYPE_LONGLONG:
		return m_llVal != 0;
	case VARIANT_TYPE_ULONGLONG:
		return m_ullVal != 0;
	default:
		break;
	}
	return bDefValue;
}

cs_char CsVariant_Private::ToChar(const cs_char cDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_CHAR:
		return m_cVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_char>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_char>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_char>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_char>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_char>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_char>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_char>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_char>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_char>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_char>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_char>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_char>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			CsString *pStr = static_cast<CsString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return pStr->GetCStr()[0];
			}
		}
	}
		break;
	default:
		break;
	}
	return cDefValue;
}

cs_uchar CsVariant_Private::ToUChar(const cs_uchar cDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return m_cVal;
	case VARIANT_TYPE_WCHAR:
		return m_wcVal;
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_uchar>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_uchar>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_uchar>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_uchar>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_uchar>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_uchar>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_uchar>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_uchar>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_uchar>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_uchar>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			CsString *pStr = static_cast<CsString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return static_cast<cs_uchar>(pStr->GetCStr()[0]);
			}
		}
	}
		break;
	default:
		break;
	}
	return cDefValue;
}

cs_wchar CsVariant_Private::ToWChar(const cs_wchar cDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_WCHAR:
		return m_wcVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return m_cVal;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_wchar>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_wchar>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_wchar>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_wchar>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_wchar>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_wchar>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_wchar>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_wchar>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_wchar>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_wchar>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			CsString *pStr = static_cast<CsString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return static_cast<cs_wchar>(pStr->GetCStr()[0]);
			}
		}
	}
		break;
	default:
		break;
	}
	return cDefValue;
}

cs_short CsVariant_Private::ToShort(const cs_short nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_SHORT:
		return m_sVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_short>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_short>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_short>(m_wcVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_short>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_short>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_short>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_short>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_short>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_short>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_short>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_short>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_short>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_short nValue = static_cast<CsString*>(m_pVal)->ToShort(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ushort CsVariant_Private::ToUShort(const cs_ushort nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_USHORT:
		return m_usVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_ushort>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_ushort>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_ushort>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_ushort>(m_sVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_ushort>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_ushort>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_ushort>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_ushort>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_ushort>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_ushort>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_ushort>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_ushort>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_ushort nValue = static_cast<CsString*>(m_pVal)->ToUShort(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_int CsVariant_Private::ToInt(const cs_int nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_INT:
		return m_iVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_int>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_int>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_int>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_int>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_int>(m_usVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_int>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_int>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_int>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_int>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_int>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_int>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_int>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_int nValue = static_cast<CsString*>(m_pVal)->ToInt(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_uint CsVariant_Private::ToUInt(const cs_uint nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_UINT:
		return m_uiVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_uint>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_uint>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_uint>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_uint>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_uint>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_uint>(m_iVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_uint>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_uint>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_uint>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_uint>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_uint>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_uint>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_uint nValue = static_cast<CsString*>(m_pVal)->ToUInt(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_long CsVariant_Private::ToLong(const cs_long nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_LONG:
		return m_lVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_long>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_long>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_long>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_long>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_long>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_long>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_long>(m_uiVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_long>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_long>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_long>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_long>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_long>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_long nValue = static_cast<CsString*>(m_pVal)->ToLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ulong CsVariant_Private::ToULong(const cs_ulong nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_ULONG:
		return m_ulVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_ulong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_ulong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_ulong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_ulong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_ulong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_ulong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_ulong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_ulong>(m_lVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_ulong>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_ulong>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_ulong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_ulong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_ulong nValue = static_cast<CsString*>(m_pVal)->ToULong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_longlong CsVariant_Private::ToLongLong(const cs_longlong nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_LONGLONG:
		return m_llVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_longlong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_longlong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_longlong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_longlong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_longlong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_longlong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_longlong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_longlong>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_longlong>(m_ulVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_longlong>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_longlong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_ulong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_longlong nValue = static_cast<CsString*>(m_pVal)->ToLongLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ulonglong CsVariant_Private::ToULongLong(const cs_ulonglong nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_ULONGLONG:
		return m_ullVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_ulonglong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_ulonglong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_ulonglong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_ulonglong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_ulonglong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_ulonglong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_ulonglong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_ulonglong>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_ulonglong>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_ulonglong>(m_llVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_ulonglong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_ulonglong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_ulonglong nValue = static_cast<CsString*>(m_pVal)->ToULongLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_float CsVariant_Private::ToFloat(const cs_float nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_FLOAT:
		return m_fVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_float>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_float>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_float>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_float>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_float>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_float>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_float>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_float>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_float>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_float>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_float>(m_ullVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<cs_float>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_float nValue = static_cast<CsString*>(m_pVal)->ToFloat(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_double CsVariant_Private::ToDouble(const cs_double nDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_DOUBLE:
		return m_dVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_double>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<cs_double>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_double>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<cs_double>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<cs_double>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<cs_double>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<cs_double>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<cs_double>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<cs_double>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<cs_double>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<cs_double>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<cs_double>(m_fVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			cs_bool bIsOK = false;
			cs_double nValue = static_cast<CsString*>(m_pVal)->ToDouble(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	default:
		break;
	}
	return nDefValue;
}

CsString CsVariant_Private::ToString(const CsString &sDefValue) const
{
	switch (m_emType)
	{
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			return *(CsString*)m_pVal;
		}
	}
		break;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return "true";
		else return "false";
		break;
	case VARIANT_TYPE_CHAR:
		return m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		return m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		return CsString::FromNum(m_sVal);
		break;
	case VARIANT_TYPE_USHORT:
		return CsString::FromNum(m_usVal);
		break;
	case VARIANT_TYPE_INT:
		return CsString::FromNum(m_iVal);
		break;
	case VARIANT_TYPE_UINT:
		return CsString::FromNum(m_uiVal);
		break;
	case VARIANT_TYPE_LONG:
		return CsString::FromNum(m_lVal);
		break;
	case VARIANT_TYPE_ULONG:
		return CsString::FromNum(m_ulVal);
		break;
	case VARIANT_TYPE_LONGLONG:
		return CsString::FromNum(m_llVal);
		break;
	case VARIANT_TYPE_ULONGLONG:
		return CsString::FromNum(m_ullVal);
		break;
	case VARIANT_TYPE_FLOAT:
		return CsString::FromNum(m_fVal);
		break;
	case VARIANT_TYPE_DOUBLE:
		return CsString::FromNum(m_dVal);
		break;
	case VARIANT_TYPE_POINTER:
		break;
	default:
		break;
	}
	return sDefValue;
}

void CsVariant_Private::ClearMemery()
{
	if (m_emType == VARIANT_TYPE_STRING && m_pVal)
	{
		delete (CsString*)m_pVal;
		m_pVal = NULL;
	}
}
