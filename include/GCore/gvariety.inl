#ifndef _CORE_VARIETY_INLINE_
#define _CORE_VARIETY_INLINE_

GINLINE GVariety::GVariety()
: m_nType(VARIETY_TYPE_ILLEGAL)
, m_pVal(GNULL)
{

}

GINLINE GVariety::GVariety(gbool val)
: m_nType(VARIETY_TYPE_BOOL)
, m_bVal(val)
{

}

GINLINE GVariety::GVariety(gchar val)
: m_nType(VARIETY_TYPE_CHAR)
, m_cVal(val)
{

}

GINLINE GVariety::GVariety(gschar val)
: m_nType(VARIETY_TYPE_SCHAR)
, m_scVal(val)
{

}

GINLINE GVariety::GVariety(guchar val)
: m_nType(VARIETY_TYPE_UCHAR)
, m_ucVal(val)
{

}

GINLINE GVariety::GVariety(gwchar val)
: m_nType(VARIETY_TYPE_WCHAR)
, m_wcVal(val)
{

}

GINLINE GVariety::GVariety(gshort val)
: m_nType(VARIETY_TYPE_SHORT)
, m_sVal(val)
{

}

GINLINE GVariety::GVariety(gushort val)
: m_nType(VARIETY_TYPE_USHORT)
, m_usVal(val)
{

}

GINLINE GVariety::GVariety(gint val)
: m_nType(VARIETY_TYPE_INT)
, m_iVal(val)
{

}

GINLINE GVariety::GVariety(guint val)
: m_nType(VARIETY_TYPE_UINT)
, m_uiVal(val)
{

}

GINLINE GVariety::GVariety(glong val)
: m_nType(VARIETY_TYPE_LONG)
, m_lVal(val)
{

}

GINLINE GVariety::GVariety(gulong val)
: m_nType(VARIETY_TYPE_ULONG)
, m_ulVal(val)
{

}

GINLINE GVariety::GVariety(glonglong val)
: m_nType(VARIETY_TYPE_LONGLONG)
, m_llVal(val)
{

}

GINLINE GVariety::GVariety(gulonglong val)
: m_nType(VARIETY_TYPE_ULONGLONG)
, m_ullVal(val)
{

}

GINLINE GVariety::GVariety(gfloat val)
: m_nType(VARIETY_TYPE_FLOAT)
, m_fVal(val)
{

}

GINLINE GVariety::GVariety(gdouble val)
: m_nType(VARIETY_TYPE_DOUBLE)
, m_dVal(val)
{

}

GINLINE GVariety::GVariety(glongdouble val)
: m_nType(VARIETY_TYPE_LONGDOUBLE)
, m_ldVal(val)
{

}

GINLINE GVariety::GVariety(gpointer val)
: m_nType(VARIETY_TYPE_POINTER)
, m_pVal(val)
{

}

GINLINE GVariety::~GVariety()
{
	Free();
}

GINLINE GVariety::TYPE GVariety::GetType() const
{
	return static_cast<GVariety::TYPE>(m_nType);
}

GINLINE gbool GVariety::Valid() const
{
	if (m_nType == VARIETY_TYPE_ILLEGAL)
	{
		return false;
	}
	else if (m_nType == VARIETY_TYPE_POINTER)
	{
		return m_pVal != GNULL;
	}
	return true;
}

GINLINE gvoid GVariety::SetValue(gbool val)
{
	Free();
	m_nType = VARIETY_TYPE_BOOL;
	m_bVal = val;
}

GINLINE gvoid GVariety::SetValue(gchar val)
{
	Free();
	m_nType = VARIETY_TYPE_CHAR;
	m_cVal = val;
}

GINLINE gvoid GVariety::SetValue(gschar val)
{
	Free();
	m_nType = VARIETY_TYPE_SCHAR;
	m_scVal = val;
}

GINLINE gvoid GVariety::SetValue(guchar val)
{
	Free();
	m_nType = VARIETY_TYPE_USHORT;
	m_ucVal = val;
}

GINLINE gvoid GVariety::SetValue(gwchar val)
{
	Free();
	m_nType = VARIETY_TYPE_WCHAR;
	m_wcVal = val;
}

GINLINE gvoid GVariety::SetValue(gshort val)
{
	Free();
	m_nType = VARIETY_TYPE_SHORT;
	m_sVal = val;
}

GINLINE gvoid GVariety::SetValue(gushort val)
{
	Free();
	m_nType = VARIETY_TYPE_USHORT;
	m_usVal = val;
}

GINLINE gvoid GVariety::SetValue(gint val)
{
	Free();
	m_nType = VARIETY_TYPE_INT;
	m_iVal = val;
}

GINLINE gvoid GVariety::SetValue(guint val)
{
	Free();
	m_nType = VARIETY_TYPE_UINT;
	m_uiVal = val;
}

GINLINE gvoid GVariety::SetValue(glong val)
{
	Free();
	m_nType = VARIETY_TYPE_LONG;
	m_lVal = val;
}

GINLINE gvoid GVariety::SetValue(gulong val)
{
	Free();
	m_nType = VARIETY_TYPE_ULONG;
	m_ulVal = val;
}

GINLINE gvoid GVariety::SetValue(glonglong val)
{
	Free();
	m_nType = VARIETY_TYPE_LONGLONG;
	m_llVal = val;
}

GINLINE gvoid GVariety::SetValue(gulonglong val)
{
	Free();
	m_nType = VARIETY_TYPE_ULONGLONG;
	m_ullVal = val;
}

GINLINE gvoid GVariety::SetValue(gfloat val)
{
	Free();
	m_nType = VARIETY_TYPE_FLOAT;
	m_fVal = val;
}

GINLINE gvoid GVariety::SetValue(gdouble val)
{
	Free();
	m_nType = VARIETY_TYPE_DOUBLE;
	m_dVal = val;
}

GINLINE gvoid GVariety::SetValue(glongdouble val)
{
	Free();
	m_nType = VARIETY_TYPE_LONGDOUBLE;
	m_ldVal = val;
}

GINLINE gvoid GVariety::SetPoiter(gpointer val)
{
	Free();
	m_nType = VARIETY_TYPE_POINTER;
	m_pVal = val;
}

GINLINE greal GVariety::ToReal(greal def) const
{
	return ToDouble(def);
}

GINLINE gbyte GVariety::ToByte(gbyte def) const
{
	return ToUSmall(def);
}

GINLINE gword GVariety::ToWord(gword def) const
{
	return ToUShort(def);
}

GINLINE gint8 GVariety::ToInt8(gint8 def) const
{
	return ToSmall(def);
}

GINLINE guint8 GVariety::ToUInt8(guint8 def) const
{
	return ToUSmall(def);
}

GINLINE gint16 GVariety::ToInt16(gint16 def) const
{
	return ToShort(def);
}

GINLINE guint16 GVariety::ToUInt16(guint16 def) const
{
	return ToUShort(def);
}

GINLINE gint32 GVariety::ToInt32(gint32 def) const
{
	return ToInt(def);
}

GINLINE guint32 GVariety::ToUInt32(guint32 def) const
{
	return ToUInt(def);
}

GINLINE gint64 GVariety::ToInt64(gint64 def) const
{
	return ToLongLong(def);
}

GINLINE guint64 GVariety::ToUInt64(guint64 def) const
{
	return ToULongLong(def);
}

GINLINE gdecimal GVariety::ToDecimal(gdecimal def) const
{
	return ToLongDouble(def);
}

GINLINE gpointer GVariety::GetPoiter() const
{
	if (m_nType == VARIETY_TYPE_POINTER)
	{
		return m_pVal;
	}
	return GNULL;
}

template<typename T> 
GINLINE T GVariety::GetValue() const
{
	throw("unsupported type");
}

template<>
GINLINE gint GVariety::GetValue<gint>() const
{
	return ToInt();
}

#endif // _CORE_VARIETY_INLINE_