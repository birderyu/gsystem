#ifndef _CORE_VARIANT_H_
#define _CORE_VARIANT_H_

#include "gobject.h"
#include "gstring.h"

class CsVariant_Ex;

enum G_VARIANT_TYPE
{
	VARIANT_TYPE_ILLEGAL = -1,
	VARIANT_TYPE_BOOL,
	VARIANT_TYPE_CHAR,
	VARIANT_TYPE_SCHAR,
	VARIANT_TYPE_UCHAR,
	VARIANT_TYPE_WCHAR,
	VARIANT_TYPE_SHORT,
	VARIANT_TYPE_USHORT,
	VARIANT_TYPE_INT,
	VARIANT_TYPE_UINT,
	VARIANT_TYPE_LONG,
	VARIANT_TYPE_ULONG,
	VARIANT_TYPE_LONGLONG,
	VARIANT_TYPE_ULONGLONG,
	VARIANT_TYPE_FLOAT,
	VARIANT_TYPE_DOUBLE,
	VARIANT_TYPE_DECIMAL,
	VARIANT_TYPE_STRING,		// 字符串
	VARIANT_TYPE_GEOMERTY,		// 几何对象
	VARIANT_TYPE_OBJECT,		// object
	VARIANT_TYPE_POINTER,		// 指针
};

class GAPI GVariant 
	: public GObject
{
public:
	GVariant();
	GVariant(const gbool bValue);
	GVariant(const gchar cValue);
	GVariant(const guchar cValue);
	GVariant(const gwchar cValue);
	GVariant(const gshort nValue);
	GVariant(const gushort nValue);
	GVariant(const gint nValue);
	GVariant(const guint nValue);
	GVariant(const glong nValue);
	GVariant(const gulong nValue);
	GVariant(const glonglong nValue);
	GVariant(const gulonglong nValue);
	GVariant(const gfloat nValue);
	GVariant(const gdouble nValue);
	GVariant(gcstring sValue);
	GVariant(const GString &sValue);
	GVariant(const GObject &tValue);
	GVariant(const gpointer pValue);
	GVariant(const GVariant &tOther);
	~GVariant();

	G_VARIANT_TYPE GetVariantType() const;
	gpointer GetPoiter() const;

	gvoid SetPoiter(const gpointer pValue);
	gvoid SetValue(const gbool bValue);
	gvoid SetValue(const gchar cValue);
	gvoid SetValue(const guchar cValue);
	gvoid SetValue(const gwchar cValue);
	gvoid SetValue(const gshort nValue);
	gvoid SetValue(const gushort nValue);
	gvoid SetValue(const gint nValue);
	gvoid SetValue(const guint nValue);
	gvoid SetValue(const glong nValue);
	gvoid SetValue(const gulong nValue);
	gvoid SetValue(const glonglong nValue);
	gvoid SetValue(const gulonglong nValue);
	gvoid SetValue(const gfloat nValue);
	gvoid SetValue(const gdouble nValue);
	gvoid SetValue(gcstring sValue);
	gvoid SetValue(const GString &sValue);
	gvoid SetValue(const GObject &tValue);

	gbool ToBool(const gbool def = false) const;
	gchar ToChar(const gchar def = ' ') const;
	guchar ToUChar(const guchar def = ' ') const;
	gwchar ToWChar(const gwchar def = ' ') const;
	gsmall ToSmall(const gsmall def = 0) const;
	gusmall ToUSmall(const gusmall def = 0) const;
	gshort ToShort(const gshort def = 0) const;
	gushort ToUShort(const gushort def = 0) const;
	gint ToInt(const gint def = 0) const;
	guint ToUInt(const guint def = 0) const;
	glong ToLong(const glong def = 0) const;
	gulong ToULong(const gulong def = 0) const;
	glonglong ToLongLong(const glonglong def = 0) const;
	gulonglong ToULongLong(const gulonglong def = 0) const;
	gfloat ToFloat(const gfloat def = 0) const;
	gdouble ToDouble(const gdouble def = 0) const;
	GString ToString(const GString &def = "") const;
	GObject *ToObject() const;

	gbyte ToByte(const gbyte &def = 0) const;
	gint8 ToInt8(const gint8 &def = 0) const;
	guint8 ToUInt8(const guint8 &def = 0) const;
	gint16 ToInt16(const gint16 &def = 0) const;
	guint16 ToUInt16(const guint16 &def = 0) const;
	gint32 ToInt32(const gint32 &def = 0) const;
	guint32 ToUInt32(const guint32 &def = 0) const;
	gint64 ToInt64(const gint64 &def = 0) const;
	guint64 ToUInt64(const guint64 &def = 0) const;
	gsize ToSizeType(const gsize &def = 0) const;

	gbool IsValid() const;
	
	GVariant &operator=(const GVariant &var);

private:
	CsVariant_Ex *m_pVariant_Ex;
};

#endif // _CORE_VARIANT_H_