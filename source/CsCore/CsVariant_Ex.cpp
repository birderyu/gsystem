#include "CsVariant_Ex.h"
#include "CsString.h"
#include "CsNumber.h"

CsVariant_Ex::CsVariant_Ex()
: m_nType(VARIANT_TYPE_ILLEGAL)
, m_pVal(NULL)
{

}

CsVariant_Ex::CsVariant_Ex(cs_bool bValue)
: m_nType(VARIANT_TYPE_BOOL)
, m_bVal(bValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_char cValue)
: m_nType(VARIANT_TYPE_CHAR)
, m_cVal(cValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_schar cValue)
: m_nType(VARIANT_TYPE_SCHAR)
, m_scVal(cValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_uchar cValue)
: m_nType(VARIANT_TYPE_UCHAR)
, m_ucVal(cValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_wchar cValue)
: m_nType(VARIANT_TYPE_WCHAR)
, m_wcVal(cValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_short nValue)
: m_nType(VARIANT_TYPE_SHORT)
, m_sVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_ushort nValue)
: m_nType(VARIANT_TYPE_USHORT)
, m_usVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_int nValue)
: m_nType(VARIANT_TYPE_INT)
, m_iVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_uint nValue)
: m_nType(VARIANT_TYPE_UINT)
, m_uiVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_long nValue)
: m_nType(VARIANT_TYPE_LONG)
, m_lVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_ulong nValue)
: m_nType(VARIANT_TYPE_ULONG)
, m_ulVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_longlong nValue)
: m_nType(VARIANT_TYPE_LONGLONG)
, m_llVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_ulonglong nValue)
: m_nType(VARIANT_TYPE_ULONGLONG)
, m_ullVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_float nValue)
: m_nType(VARIANT_TYPE_FLOAT)
, m_fVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_double nValue)
: m_nType(VARIANT_TYPE_DOUBLE)
, m_dVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(cs_decimal nValue)
: m_nType(VARIANT_TYPE_DECIMAL)
, m_decVal(nValue)
{

}

CsVariant_Ex::CsVariant_Ex(const CsString &sValue)
: m_nType(VARIANT_TYPE_STRING)
, m_pVal(new CsString(sValue))
{

}

CsVariant_Ex::CsVariant_Ex(const CsObject &tValue)
: m_nType(VARIANT_TYPE_OBJECT)
, m_pVal(NULL)
{

}

CsVariant_Ex::CsVariant_Ex(const cs_pointer pValue)
: m_nType(VARIANT_TYPE_POINTER)
, m_pVal(pValue)
{

}

CsVariant_Ex::CsVariant_Ex(const CsVariant_Ex &tOther)
: m_nType(tOther.m_nType)
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
	{
		if (tOther.m_pVal)
		{
			//m_pVal = static_cast<CsObject*>(tOther.m_pVal)->Clone();
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

CsVariant_Ex::~CsVariant_Ex()
{
	ClearMemery();
}

CS_VARIANT_TYPE CsVariant_Ex::GetVariantType() const
{
	return static_cast<CS_VARIANT_TYPE>(m_nType);
}

cs_pointer CsVariant_Ex::GetPoiter() const
{
	if (m_nType == VARIANT_TYPE_POINTER)
	{
		return m_pVal;
	}
	return NULL;
}

cs_void CsVariant_Ex::SetPoiter(const cs_pointer pValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_POINTER;
	m_pVal = pValue;
}

cs_void CsVariant_Ex::SetValue(cs_bool bValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_BOOL;
	m_bVal = bValue;
}

cs_void CsVariant_Ex::SetValue(cs_char cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_CHAR;
	m_cVal = cValue;
}

cs_void CsVariant_Ex::SetValue(cs_uchar cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_USHORT;
	m_ucVal = cValue;
}

cs_void CsVariant_Ex::SetValue(cs_wchar cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_WCHAR;
	m_wcVal = cValue;
}

cs_void CsVariant_Ex::SetValue(cs_short nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_SHORT;
	m_sVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_ushort nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_USHORT;
	m_usVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_int nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_INT;
	m_iVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_uint nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_UINT;
	m_uiVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_long nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_LONG;
	m_lVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_ulong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_ULONG;
	m_ulVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_longlong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_LONGLONG;
	m_llVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_ulonglong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_ULONGLONG;
	m_ullVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_float nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_FLOAT;
	m_fVal = nValue;
}

cs_void CsVariant_Ex::SetValue(cs_double nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_DOUBLE;
	m_dVal = nValue;
}

cs_void CsVariant_Ex::SetValue(const CsString &sValue)
{
	if (m_nType == VARIANT_TYPE_STRING && m_pVal)
	{
		CsString &sStr = *(CsString*)m_pVal;
		sStr = sValue;
	}
	else
	{
		m_nType = VARIANT_TYPE_STRING;
		m_pVal = new CsString(sValue);
	}
}

cs_void CsVariant_Ex::SetValue(const CsObject &tValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_OBJECT;
	//m_pVal = tValue.Clone();
}

cs_bool CsVariant_Ex::ToBool(const cs_bool bDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			CsString sStr = static_cast<CsString*>(m_pVal)->ToUpper();
			if (sStr == "TRUE")
			{
				return true;
			}
			else if (sStr == "FALSE")
			{
				return false;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_bool, CsBoolean>(CLASS_CODE_BOOLEAN, bDefValue);
		break;
	default:
		break;
	}
	return bDefValue;
}

cs_char CsVariant_Ex::ToChar(const cs_char cDefValue) const
{
	switch (m_nType)
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
				return pStr->CString()[0];
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_char, CsChar>(CLASS_CODE_CHARACTER, cDefValue);
	default:
		break;
	}
	return cDefValue;
}

cs_uchar CsVariant_Ex::ToUChar(const cs_uchar cDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<cs_uchar>(m_cVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<cs_uchar>(m_wcVal);
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
				return static_cast<cs_uchar>(pStr->CString()[0]);
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_uchar, CsUChar>(CLASS_CODE_UNSIGNED_CHARACTER, cDefValue);
		break;
	default:
		break;
	}
	return cDefValue;
}

cs_wchar CsVariant_Ex::ToWChar(const cs_wchar cDefValue) const
{
	switch (m_nType)
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
				return static_cast<cs_wchar>(pStr->CString()[0]);
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_wchar, CsWChar>(CLASS_CODE_WIND_CHARACTER, cDefValue);
		break;
	default:
		break;
	}
	return cDefValue;
}

cs_small CsVariant_Ex::ToSmall(const cs_small nDefValue) const
{
	// TODO
	return 0;
}

cs_usmall CsVariant_Ex::ToUSmall(const cs_usmall nDefValue) const
{
	// TODO
	return 0;
}

cs_short CsVariant_Ex::ToShort(const cs_short nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_short, CsShort>(CLASS_CODE_SHORT_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ushort CsVariant_Ex::ToUShort(const cs_ushort nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_ushort, CsUShort>(CLASS_CODE_UNSIGNED_SHORT_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_int CsVariant_Ex::ToInt(const cs_int nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_int, CsInteger>(CLASS_CODE_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_uint CsVariant_Ex::ToUInt(const cs_uint nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_uint, CsUInteger>(CLASS_CODE_UNSIGNED_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_long CsVariant_Ex::ToLong(const cs_long nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_long, CsLong>(CLASS_CODE_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ulong CsVariant_Ex::ToULong(const cs_ulong nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_ulong, CsULong>(CLASS_CODE_UNSIGNED_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_longlong CsVariant_Ex::ToLongLong(const cs_longlong nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_longlong, CsLongLong>(CLASS_CODE_LONG_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_ulonglong CsVariant_Ex::ToULongLong(const cs_ulonglong nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_ulonglong, CsULongLong>(CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_float CsVariant_Ex::ToFloat(const cs_float nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_float, CsFloat>(CLASS_CODE_SINGLE_FLOAT, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

cs_double CsVariant_Ex::ToDouble(const cs_double nDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
		return ToNumber<cs_double, CsDoubleFloat>(CLASS_CODE_DOUBLE_FLOAT, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

CsString CsVariant_Ex::ToString(const CsString &sDefValue) const
{
	switch (m_nType)
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
	case VARIANT_TYPE_OBJECT:
	{
		if (m_pVal)
		{
			CsObject *pObjcet = static_cast<CsObject*>(m_pVal);
			return pObjcet->ToString();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		break;
	default:
		break;
	}
	return sDefValue;
}

CsObject *CsVariant_Ex::ToObject() const
{
	/*
	switch (m_emType)
	{
	case VARIANT_TYPE_OBJECT:
	{
		if (m_pVal)
		{
			//return static_cast<CsObject*>(m_pVal)->Boxing();
		}
	}
		break;
	case VARIANT_TYPE_BOOL:
		return new CsBoolean(m_bVal);
		break;
	case VARIANT_TYPE_CHAR:
		return new CsCharacter(m_cVal);
		break;
	case VARIANT_TYPE_UCHAR:
		return new CsUCharacter(m_ucVal);
		break;
	case VARIANT_TYPE_WCHAR:
		return new CsWCharacter(m_wcVal);
		break;
	case VARIANT_TYPE_SHORT:
		return new CsShort(m_sVal);
		break;
	case VARIANT_TYPE_USHORT:
		return new CsUShort(m_usVal);
		break;
	case VARIANT_TYPE_INT:
		return new CsInteger(m_iVal);
		break;
	case VARIANT_TYPE_UINT:
		return new CsUInteger(m_uiVal);
		break;
	case VARIANT_TYPE_LONG:
		return new CsLong(m_lVal);
		break;
	case VARIANT_TYPE_ULONG:
		return new CsULong(m_ulVal);
		break;
	case VARIANT_TYPE_LONGLONG:
		return new CsLongLong(m_llVal);
		break;
	case VARIANT_TYPE_ULONGLONG:
		return new CsULongLong(m_ullVal);
		break;
	case VARIANT_TYPE_FLOAT:
		return new CsFloat(m_fVal);
		break;
	case VARIANT_TYPE_DOUBLE:
		return new CsDouble(m_dVal);
		break;
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			return static_cast<CsString*>(m_pVal)->Boxing();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		break;
	default:
		break;
	}
	*/
	return NULL;
}

cs_bool CsVariant_Ex::IsValid() const
{
	if (m_nType == VARIANT_TYPE_ILLEGAL)
	{
		return false;
	}
	else if (m_nType == VARIANT_TYPE_STRING
		|| m_nType == VARIANT_TYPE_OBJECT
		|| m_nType == VARIANT_TYPE_POINTER)
	{
		return m_pVal != NULL;
	}
	return true;
}

CsVariant_Ex &CsVariant_Ex::operator = (const CsVariant_Ex &var)
{
	m_nType = var.m_nType;
	switch (m_nType)
	{
	case VARIANT_TYPE_ILLEGAL:
		break;
	case VARIANT_TYPE_BOOL:
		m_bVal = var.m_bVal;
		break;
	case VARIANT_TYPE_CHAR:
		m_cVal = var.m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		m_ucVal = var.m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		m_wcVal = var.m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		m_sVal = var.m_sVal;
		break;
	case VARIANT_TYPE_USHORT:
		m_usVal = var.m_usVal;
		break;
	case VARIANT_TYPE_INT:
		m_iVal = var.m_iVal;
		break;
	case VARIANT_TYPE_UINT:
		m_uiVal = var.m_uiVal;
		break;
	case VARIANT_TYPE_LONG:
		m_lVal = var.m_lVal;
		break;
	case VARIANT_TYPE_ULONG:
		m_ulVal = var.m_ulVal;
		break;
	case VARIANT_TYPE_LONGLONG:
		m_llVal = var.m_llVal;
		break;
	case VARIANT_TYPE_ULONGLONG:
		m_ullVal = var.m_ullVal;
		break;
	case VARIANT_TYPE_FLOAT:
		m_fVal = var.m_fVal;
		break;
	case VARIANT_TYPE_DOUBLE:
		m_dVal = var.m_dVal;
		break;
	case VARIANT_TYPE_STRING:
	{
		if (var.m_pVal)
		{
			m_pVal = new CsString(*(CsString*)var.m_pVal);
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
	{
		if (var.m_pVal)
		{
			//m_pVal = static_cast<CsObject*>(var.m_pVal)->Clone();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		m_pVal = var.m_pVal;
		break;
	default:
		break;
	}
	return *this;
}

void CsVariant_Ex::ClearMemery()
{
	if (!m_pVal)
	{
		return;
	}
	if (m_nType == VARIANT_TYPE_STRING)
	{
		CsString *pString = static_cast<CsString*>(m_pVal);
		delete pString;
	}
	else if (m_nType == VARIANT_TYPE_OBJECT)
	{
		CsObject *pObject = static_cast<CsObject*>(m_pVal);
		delete pObject;
	}
	m_pVal = NULL;
}
