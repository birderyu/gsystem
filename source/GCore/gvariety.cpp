#include "gvariety.h"
#include "gbytes.h"
#include "gstring.h"
#include "gdatetime.h"
#include "gcstringhelper.h"
#include "gconstructor.h"

GVariety::GVariety(const gchar *val)
	: m_nType(VARIETY_TYPE_STRING)
{
	gsize size = GCStringHelper::Size(val);
	new(&m_strVal)GStringData(val, size);
}

GVariety::GVariety(const GString &val)
	: m_nType(VARIETY_TYPE_STRING)
	, m_strVal(val.m_tString)
{
	
}

GVariety::GVariety(const GVariety &val)
	: m_nType(val.m_nType)
{
	switch (m_nType)
	{
	case VARIETY_TYPE_ILLEGAL:
		break;
	case VARIETY_TYPE_BOOL:
		m_bVal = val.m_bVal;
		break;
	case VARIETY_TYPE_CHAR:
		m_cVal = val.m_cVal;
		break;
	case VARIETY_TYPE_SCHAR:
		m_scVal = val.m_scVal;
		break;
	case VARIETY_TYPE_UCHAR:
		m_ucVal = val.m_ucVal;
		break;
	case VARIETY_TYPE_WCHAR:
		m_wcVal = val.m_wcVal;
		break;
	case VARIETY_TYPE_SHORT:
		m_sVal = val.m_sVal;
		break;
	case VARIETY_TYPE_USHORT:
		m_usVal = val.m_usVal;
		break;
	case VARIETY_TYPE_INT:
		m_iVal = val.m_iVal;
		break;
	case VARIETY_TYPE_UINT:
		m_uiVal = val.m_uiVal;
		break;
	case VARIETY_TYPE_LONG:
		m_lVal = val.m_lVal;
		break;
	case VARIETY_TYPE_ULONG:
		m_ulVal = val.m_ulVal;
		break;
	case VARIETY_TYPE_LONGLONG:
		m_llVal = val.m_llVal;
		break;
	case VARIETY_TYPE_ULONGLONG:
		m_ullVal = val.m_ullVal;
		break;
	case VARIETY_TYPE_FLOAT:
		m_fVal = val.m_fVal;
		break;
	case VARIETY_TYPE_DOUBLE:
		m_dVal = val.m_dVal;
		break;
	case VARIETY_TYPE_LONGDOUBLE:
		m_ldVal = val.m_ldVal;
		break;
	case VARIETY_TYPE_STRING:
		// 不能直接调用m_strVal = val.m_strVal，因为此时的m_strVal处于未确定的状态
		// 直接构造一个m_strVal
		GCopyConstruct<GStringData>(&m_strVal, val.m_strVal);
		break;
	case VARIETY_TYPE_POINTER:
		m_pVal = val.m_pVal;
		break;
	default:
		break;
	}
}

GVariety::GVariety(GVariety &&val)
	: m_nType(val.m_nType)
{
	switch (m_nType)
	{
	case VARIETY_TYPE_ILLEGAL:
		break;
	case VARIETY_TYPE_BOOL:
		m_bVal = val.m_bVal;
		break;
	case VARIETY_TYPE_CHAR:
		m_cVal = val.m_cVal;
		break;
	case VARIETY_TYPE_SCHAR:
		m_scVal = val.m_scVal;
		break;
	case VARIETY_TYPE_UCHAR:
		m_ucVal = val.m_ucVal;
		break;
	case VARIETY_TYPE_WCHAR:
		m_wcVal = val.m_wcVal;
		break;
	case VARIETY_TYPE_SHORT:
		m_sVal = val.m_sVal;
		break;
	case VARIETY_TYPE_USHORT:
		m_usVal = val.m_usVal;
		break;
	case VARIETY_TYPE_INT:
		m_iVal = val.m_iVal;
		break;
	case VARIETY_TYPE_UINT:
		m_uiVal = val.m_uiVal;
		break;
	case VARIETY_TYPE_LONG:
		m_lVal = val.m_lVal;
		break;
	case VARIETY_TYPE_ULONG:
		m_ulVal = val.m_ulVal;
		break;
	case VARIETY_TYPE_LONGLONG:
		m_llVal = val.m_llVal;
		break;
	case VARIETY_TYPE_ULONGLONG:
		m_ullVal = val.m_ullVal;
		break;
	case VARIETY_TYPE_FLOAT:
		m_fVal = val.m_fVal;
		break;
	case VARIETY_TYPE_DOUBLE:
		m_dVal = val.m_dVal;
		break;
	case VARIETY_TYPE_LONGDOUBLE:
		m_ldVal = val.m_ldVal;
		break;
	case VARIETY_TYPE_STRING:
		// 不能直接调用m_strVal = GMove(val.m_strVal)，因为此时的m_strVal处于未确定的状态
		// 直接移动构造一个m_strVal
		GMoveConstruct<GStringData>(&m_strVal, GMove(val.m_strVal));
		break;
	case VARIETY_TYPE_POINTER:
		m_pVal = val.m_pVal;
		break;
	default:
		break;
	}
}

gvoid GVariety::SetValue(const gchar *val)
{
	gsize size = GCStringHelper::Size(val);
	if (m_nType == VARIETY_TYPE_STRING)
	{
		// 直接Resize，可能不需要重新分配内存
		m_strVal.Resize(size);
		GCStringHelper::Copy(val, size, m_strVal.Start());
	}
	else
	{
		Free();
		m_nType = VARIETY_TYPE_STRING;
		new(&m_strVal)GStringData(val, size);
	}
}

gvoid GVariety::SetValue(const GString &val)
{
	gsize size = val.Size();
	if (m_nType == VARIETY_TYPE_STRING)
	{
		m_strVal = val.m_tString;
	}
	else
	{
		Free();
		m_nType = VARIETY_TYPE_STRING;
		GCopyConstruct<GStringData>(&m_strVal, val.m_tString);
	}
}

gvoid GVariety::SetValue(GString &&val)
{
	gsize size = val.Size();
	if (m_nType == VARIETY_TYPE_STRING)
	{
		// 直接Resize，可能不需要重新分配内存
		m_strVal = GMove(val.m_tString);
	}
	else
	{
		Free();
		m_nType = VARIETY_TYPE_STRING;
		GMoveConstruct<GStringData>(&m_strVal, GMove(val.m_tString));
	}
}

gvoid GVariety::SetValue(const GVariety &val)
{
	if (m_nType == VARIETY_TYPE_STRING &&
		val.m_nType == VARIETY_TYPE_STRING)
	{
		m_strVal = val.m_strVal;
	}
	else
	{
		Free();
		m_nType = val.m_nType;
		switch (m_nType)
		{
		case VARIETY_TYPE_ILLEGAL:
			break;
		case VARIETY_TYPE_BOOL:
			m_bVal = val.m_bVal;
			break;
		case VARIETY_TYPE_CHAR:
			m_cVal = val.m_cVal;
			break;
		case VARIETY_TYPE_SCHAR:
			m_scVal = val.m_scVal;
			break;
		case VARIETY_TYPE_UCHAR:
			m_ucVal = val.m_ucVal;
			break;
		case VARIETY_TYPE_WCHAR:
			m_wcVal = val.m_wcVal;
			break;
		case VARIETY_TYPE_SHORT:
			m_sVal = val.m_sVal;
			break;
		case VARIETY_TYPE_USHORT:
			m_usVal = val.m_usVal;
			break;
		case VARIETY_TYPE_INT:
			m_iVal = val.m_iVal;
			break;
		case VARIETY_TYPE_UINT:
			m_uiVal = val.m_uiVal;
			break;
		case VARIETY_TYPE_LONG:
			m_lVal = val.m_lVal;
			break;
		case VARIETY_TYPE_ULONG:
			m_ulVal = val.m_ulVal;
			break;
		case VARIETY_TYPE_LONGLONG:
			m_llVal = val.m_llVal;
			break;
		case VARIETY_TYPE_ULONGLONG:
			m_ullVal = val.m_ullVal;
			break;
		case VARIETY_TYPE_FLOAT:
			m_fVal = val.m_fVal;
			break;
		case VARIETY_TYPE_DOUBLE:
			m_dVal = val.m_dVal;
			break;
		case VARIETY_TYPE_LONGDOUBLE:
			m_ldVal = val.m_ldVal;
			break;
		case VARIETY_TYPE_STRING:
			GCopyConstruct<GStringData>(&m_strVal, val.m_strVal);
			break;
		case VARIETY_TYPE_POINTER:
			m_pVal = val.m_pVal;
			break;
		default:
			break;
		}
	}
}

gbool GVariety::ToBool(gbool def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_BOOL:
		return m_bVal;
	case VARIETY_TYPE_CHAR:
		return m_cVal != 0;
	case VARIETY_TYPE_SCHAR:
		return m_scVal != 0;
	case VARIETY_TYPE_UCHAR:
		return m_ucVal != 0;
	case VARIETY_TYPE_WCHAR:
		return m_wcVal != 0;
	case VARIETY_TYPE_SHORT:
		return m_sVal != 0;
	case VARIETY_TYPE_USHORT:
		return m_usVal != 0;
	case VARIETY_TYPE_INT:
		return m_iVal != 0;
	case VARIETY_TYPE_UINT:
		return m_uiVal != 0;
	case VARIETY_TYPE_LONG:
		return m_lVal != 0;
	case VARIETY_TYPE_ULONG:
		return m_ulVal != 0;
	case VARIETY_TYPE_LONGLONG:
		return m_llVal != 0;
	case VARIETY_TYPE_ULONGLONG:
		return m_ullVal != 0;
	case VARIETY_TYPE_STRING:
	{
		if (m_strVal.Size() != 4 && m_strVal.Size() != 5)
		{
			return def;
		}
		if (m_strVal[0] == 't' && m_strVal[1] == 'r' &&
			m_strVal[2] == 'u' && m_strVal[3] == 'e')
		{
			return true;
		}
		else if (m_strVal[0] == 'f' && m_strVal[1] == 'a' 
			&& m_strVal[2] == 'l' && m_strVal[3] == 's' 
			&& m_strVal[4] == 'e')
		{
			return false;
		}
	}
		break;
	default:
		break;
	}
	return def;
}

gchar GVariety::ToChar(gchar def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_CHAR:
		return m_cVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 'T';
		else return 'F';
	}
		break;
	case VARIETY_TYPE_SCHAR:
		return static_cast<gchar>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gchar>(m_ucVal);
	case VARIETY_TYPE_STRING:
	{
		if (m_strVal.IsEmpty())
		{
			return ' ';
		}
		else
		{
			return m_strVal[0];
		}
	}
		break;
	default:
		break;
	}
	return def;
}

gschar GVariety::ToSChar(gschar def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_SCHAR:
		return m_scVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 't';
		else return 'f';
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gschar>(m_cVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gschar>(m_ucVal);
	case VARIETY_TYPE_STRING:
	{
		if (m_strVal.IsEmpty())
		{
			return ' ';
		}
		else
		{
			return static_cast<gschar>(m_strVal[0]);
		}
	}
		break;
	default:
		break;
	}
	return def;
}

guchar GVariety::ToUChar(guchar def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_UCHAR:
		return m_ucVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 't';
		else return 'f';
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<guchar>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<guchar>(m_scVal);
	case VARIETY_TYPE_STRING:
	{
		if (m_strVal.IsEmpty())
		{
			return ' ';
		}
		else
		{
			return static_cast<guchar>(m_strVal.GetAt(0));
		}
	}
		break;
	default:
		break;
	}
	return def;
}

gwchar GVariety::ToWChar(gwchar def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_WCHAR:
		return m_wcVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return (gwchar)'t';
		else return (gwchar)'f';
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gwchar>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gwchar>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gwchar>(m_ucVal);
	case VARIETY_TYPE_STRING:
	{
		if (m_pVal)
		{
			GString *pStr = static_cast<GString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return static_cast<gwchar>(pStr->CString()[0]);
			}
		}
	}
		break;
	default:
		break;
	}
	return def;
}

gshort GVariety::ToShort(gshort def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_SHORT:
		return m_sVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gshort>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gshort>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gshort>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gshort>(m_wcVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gshort>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gshort>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gshort>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gshort>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gshort>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gshort>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gshort>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gshort>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gshort>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gshort>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToShort(GNULL);
		break;
	default:
		break;
	}
	return def;
}

gushort GVariety::ToUShort(gushort def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_USHORT:
		return m_usVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gushort>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gushort>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gushort>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gushort>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gushort>(m_sVal);
	case VARIETY_TYPE_INT:
		return static_cast<gushort>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gushort>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gushort>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gushort>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gushort>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gushort>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gushort>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gushort>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gushort>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToUShort(GNULL);
	default:
		break;
	}
	return def;
}

gint GVariety::ToInt(gint def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_INT:
		return m_iVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gint>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gint>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gint>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gint>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gint>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gint>(m_usVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gint>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gint>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gint>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gint>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gint>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gint>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gint>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gint>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToInt(GNULL);
		break;
	default:
		break;
	}
	return def;
}

guint GVariety::ToUInt(guint def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_UINT:
		return m_uiVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<guint>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<guint>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<guint>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<guint>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<guint>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<guint>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<guint>(m_iVal);
	case VARIETY_TYPE_LONG:
		return static_cast<guint>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<guint>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<guint>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<guint>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<guint>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<guint>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<guint>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToUInt(GNULL);
		break;
	default:
		break;
	}
	return def;
}

glong GVariety::ToLong(glong def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_LONG:
		return m_lVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<glong>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<glong>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<glong>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<glong>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<glong>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<glong>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<glong>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<glong>(m_uiVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<glong>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<glong>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<glong>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<glong>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<glong>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<glong>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToLong(GNULL);
	default:
		break;
	}
	return def;
}

gulong GVariety::ToULong(gulong def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_ULONG:
		return m_ulVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gulong>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gulong>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gulong>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gulong>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gulong>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gulong>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gulong>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gulong>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gulong>(m_lVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gulong>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gulong>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gulong>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gulong>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gulong>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToULong(GNULL);
	default:
		break;
	}
	return def;
}

glonglong GVariety::ToLongLong(glonglong def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_LONGLONG:
		return m_llVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<glonglong>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<glonglong>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<glonglong>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<glonglong>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<glonglong>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<glonglong>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<glonglong>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<glonglong>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<glonglong>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<glonglong>(m_ulVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<glonglong>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<glonglong>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<glonglong>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<glonglong>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToLongLong(GNULL);
	default:
		break;
	}
	return def;
}

gulonglong GVariety::ToULongLong(gulonglong def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_ULONGLONG:
		return m_ullVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gulonglong>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gulonglong>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gulonglong>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gulonglong>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gulonglong>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gulonglong>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gulonglong>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gulonglong>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gulonglong>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gulonglong>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gulonglong>(m_llVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gulonglong>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gulonglong>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gulonglong>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToULongLong(GNULL);
	default:
		break;
	}
	return def;
}

gfloat GVariety::ToFloat(gfloat def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_FLOAT:
		return m_fVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gfloat>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gfloat>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gfloat>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gfloat>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gfloat>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gfloat>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gfloat>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gfloat>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gfloat>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gfloat>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gfloat>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gfloat>(m_ullVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gfloat>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gfloat>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToFloat(GNULL);
	default:
		break;
	}
	return def;
}

gdouble GVariety::ToDouble(gdouble def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_DOUBLE:
		return m_dVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gdouble>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gdouble>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gdouble>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gdouble>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gdouble>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gdouble>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gdouble>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gdouble>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gdouble>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gdouble>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gdouble>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gdouble>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gdouble>(m_fVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gdouble>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToDouble(GNULL);
		break;
	default:
		break;
	}
	return def;
}

glongdouble GVariety::ToLongDouble(glongdouble def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_LONGDOUBLE:
		return m_ldVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<glongdouble>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<glongdouble>(m_scVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<glongdouble>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<glongdouble>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<glongdouble>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<glongdouble>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<glongdouble>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<glongdouble>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<glongdouble>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<glongdouble>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<glongdouble>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<glongdouble>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<glongdouble>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<glongdouble>(m_dVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToDecimal(GNULL);
	default:
		break;
	}
	return def;
}

GString GVariety::ToString() const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_STRING:
		return GString(m_strVal);
		break;
	case VARIETY_TYPE_BOOL:
		if (m_bVal) return GString("true", 4);
		else return GString("false", 5);
		break;
	case VARIETY_TYPE_CHAR:
		return GString(m_cVal);
		break;
	case VARIETY_TYPE_SCHAR:
		return GString(m_scVal);
		break;
	case VARIETY_TYPE_UCHAR:
		return GString(m_ucVal);
		break;
	case VARIETY_TYPE_WCHAR:
		// TODO：wchar转char
		return GString(m_wcVal);
		break;
	case VARIETY_TYPE_SHORT:
		return GString::Number(m_sVal);
		break;
	case VARIETY_TYPE_USHORT:
		return GString::Number(m_usVal);
		break;
	case VARIETY_TYPE_INT:
		return GString::Number(m_iVal);
		break;
	case VARIETY_TYPE_UINT:
		return GString::Number(m_uiVal);
		break;
	case VARIETY_TYPE_LONG:
		return GString::Number(m_lVal);
		break;
	case VARIETY_TYPE_ULONG:
		return GString::Number(m_ulVal);
		break;
	case VARIETY_TYPE_LONGLONG:
		return GString::Number(m_llVal);
		break;
	case VARIETY_TYPE_ULONGLONG:
		return GString::Number(m_ullVal);
		break;
	case VARIETY_TYPE_FLOAT:
		return GString::Number(m_fVal);
		break;
	case VARIETY_TYPE_DOUBLE:
		return GString::Number(m_dVal);
		break;
	case VARIETY_TYPE_LONGDOUBLE:
		return GString::Number(m_ldVal);
		break;
	default:
		break;
	}
	return "";
}

gsmall GVariety::ToSmall(gsmall def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_SCHAR:
		return m_scVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gsmall>(m_cVal);
	case VARIETY_TYPE_UCHAR:
		return static_cast<gsmall>(m_ucVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gsmall>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gsmall>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gsmall>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gsmall>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gsmall>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gsmall>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gsmall>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gsmall>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gsmall>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gsmall>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gsmall>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gsmall>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToSmall(GNULL);
	default:
		break;
	}
	return def;
}

gusmall GVariety::ToUSmall(gusmall def) const
{
	switch (m_nType)
	{
	case VARIETY_TYPE_UCHAR:
		return m_ucVal;
	case VARIETY_TYPE_BOOL:
	{
		if (m_bVal) return 1;
		else return 0;
	}
		break;
	case VARIETY_TYPE_CHAR:
		return static_cast<gusmall>(m_cVal);
	case VARIETY_TYPE_SCHAR:
		return static_cast<gusmall>(m_scVal);
	case VARIETY_TYPE_WCHAR:
		return static_cast<gusmall>(m_wcVal);
	case VARIETY_TYPE_SHORT:
		return static_cast<gusmall>(m_sVal);
	case VARIETY_TYPE_USHORT:
		return static_cast<gusmall>(m_usVal);
	case VARIETY_TYPE_INT:
		return static_cast<gusmall>(m_iVal);
	case VARIETY_TYPE_UINT:
		return static_cast<gusmall>(m_uiVal);
	case VARIETY_TYPE_LONG:
		return static_cast<gusmall>(m_lVal);
	case VARIETY_TYPE_ULONG:
		return static_cast<gusmall>(m_ulVal);
	case VARIETY_TYPE_LONGLONG:
		return static_cast<gusmall>(m_llVal);
	case VARIETY_TYPE_ULONGLONG:
		return static_cast<gusmall>(m_ullVal);
	case VARIETY_TYPE_FLOAT:
		return static_cast<gusmall>(m_fVal);
	case VARIETY_TYPE_DOUBLE:
		return static_cast<gusmall>(m_dVal);
	case VARIETY_TYPE_LONGDOUBLE:
		return static_cast<gusmall>(m_ldVal);
	case VARIETY_TYPE_STRING:
		// TODO
		//return m_strVal.ToUSmall(GNULL);
	default:
		break;
	}
	return def;
}

gsize GVariety::ToSize(gsize def) const
{
	gsize sizeofgsize = sizeof(gsize);
	// TODO，改为编译期执行
	if (sizeofgsize == 1)
	{
		return ToUInt8(static_cast<guint8>(def));
	}
	else if (sizeofgsize == 2)
	{
		return ToUInt16(static_cast<guint16>(def));
	}
	else if (sizeofgsize == 4)
	{
		return ToUInt32(static_cast<guint32>(def));
	}
	else if (sizeofgsize == 8)
	{
		return ToUInt64(static_cast<guint64>(def));
	}
	return def;
}

gtime GVariety::ToTime(gtime def) const
{
	gusmall sizeofgsize = sizeof(gtime);
	// TODO，改为编译期执行
	if (sizeofgsize == 1)
	{
		return ToInt8(def);
	}
	else if (sizeofgsize == 2)
	{
		return ToInt16(def);
	}
	else if (sizeofgsize == 4)
	{
		return ToInt32(def);
	}
	else if (sizeofgsize == 8)
	{
		return ToInt64(def);
	}
	return def;
}

GVariety &GVariety::operator=(const GVariety &val)
{
	if (this == &val)
	{
		return *this;
	}
	Free();
	m_nType = val.m_nType;
	switch (m_nType)
	{
	case VARIETY_TYPE_ILLEGAL:
		break;
	case VARIETY_TYPE_BOOL:
		m_bVal = val.m_bVal;
		break;
	case VARIETY_TYPE_CHAR:
		m_cVal = val.m_cVal;
		break;
	case VARIETY_TYPE_SCHAR:
		m_scVal = val.m_scVal;
		break;
	case VARIETY_TYPE_UCHAR:
		m_ucVal = val.m_ucVal;
		break;
	case VARIETY_TYPE_WCHAR:
		m_wcVal = val.m_wcVal;
		break;
	case VARIETY_TYPE_SHORT:
		m_sVal = val.m_sVal;
		break;
	case VARIETY_TYPE_USHORT:
		m_usVal = val.m_usVal;
		break;
	case VARIETY_TYPE_INT:
		m_iVal = val.m_iVal;
		break;
	case VARIETY_TYPE_UINT:
		m_uiVal = val.m_uiVal;
		break;
	case VARIETY_TYPE_LONG:
		m_lVal = val.m_lVal;
		break;
	case VARIETY_TYPE_ULONG:
		m_ulVal = val.m_ulVal;
		break;
	case VARIETY_TYPE_LONGLONG:
		m_llVal = val.m_llVal;
		break;
	case VARIETY_TYPE_ULONGLONG:
		m_ullVal = val.m_ullVal;
		break;
	case VARIETY_TYPE_FLOAT:
		m_fVal = val.m_fVal;
		break;
	case VARIETY_TYPE_DOUBLE:
		m_dVal = val.m_dVal;
		break;
	case VARIETY_TYPE_LONGDOUBLE:
		m_ldVal = val.m_ldVal;
		break;
	case VARIETY_TYPE_STRING:
		m_strVal = GMove(val.m_strVal);
		break;
	case VARIETY_TYPE_POINTER:
		m_pVal = val.m_pVal;
		break;
	default:
		break;
	}
	return *this;
}

GVariety &GVariety::operator=(GVariety &&val)
{
	if (this == &val)
	{
		return *this;
	}
	Free();
	m_nType = val.m_nType;
	switch (m_nType)
	{
	case VARIETY_TYPE_ILLEGAL:
		break;
	case VARIETY_TYPE_BOOL:
		m_bVal = val.m_bVal;
		break;
	case VARIETY_TYPE_CHAR:
		m_cVal = val.m_cVal;
		break;
	case VARIETY_TYPE_SCHAR:
		m_scVal = val.m_scVal;
		break;
	case VARIETY_TYPE_UCHAR:
		m_ucVal = val.m_ucVal;
		break;
	case VARIETY_TYPE_WCHAR:
		m_wcVal = val.m_wcVal;
		break;
	case VARIETY_TYPE_SHORT:
		m_sVal = val.m_sVal;
		break;
	case VARIETY_TYPE_USHORT:
		m_usVal = val.m_usVal;
		break;
	case VARIETY_TYPE_INT:
		m_iVal = val.m_iVal;
		break;
	case VARIETY_TYPE_UINT:
		m_uiVal = val.m_uiVal;
		break;
	case VARIETY_TYPE_LONG:
		m_lVal = val.m_lVal;
		break;
	case VARIETY_TYPE_ULONG:
		m_ulVal = val.m_ulVal;
		break;
	case VARIETY_TYPE_LONGLONG:
		m_llVal = val.m_llVal;
		break;
	case VARIETY_TYPE_ULONGLONG:
		m_ullVal = val.m_ullVal;
		break;
	case VARIETY_TYPE_FLOAT:
		m_fVal = val.m_fVal;
		break;
	case VARIETY_TYPE_DOUBLE:
		m_dVal = val.m_dVal;
		break;
	case VARIETY_TYPE_LONGDOUBLE:
		m_ldVal = val.m_ldVal;
		break;
	case VARIETY_TYPE_STRING:
		m_strVal = GMove(val.m_strVal);
		break;
	case VARIETY_TYPE_POINTER:
		m_pVal = val.m_pVal;
		break;
	default:
		break;
	}
	val.m_nType = VARIETY_TYPE_ILLEGAL;
	val.m_pVal = GNULL;
}

gvoid GVariety::Free()
{
	if (m_nType == VARIETY_TYPE_BYTES)
	{
		GDestruct<GBytesData>(&m_bytesVal);
	}
	else if (m_nType == VARIETY_TYPE_STRING)
	{
		GDestruct<GStringData>(&m_strVal);
	}
	else if (m_nType == VARIETY_TYPE_WSTRING)
	{
		GDestruct<GWStringData>(&m_wstrVal);
	}

	m_nType = VARIETY_TYPE_ILLEGAL;
	m_pVal = GNULL;
}
