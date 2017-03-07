#ifndef _CORE_VARIETY_H_
#define _CORE_VARIETY_H_

#include "gseries.h"

class GBytes;
class GString;
class GWString;
class GDateTime;

namespace GNova {
	namespace Variety {
		namespace Private {

			template<typename T>
			struct GVarietyExtraType
				: GFalseType {};

			template<>
			struct GVarietyExtraType<GBytes>
				: GTrueType {};

			template<>
			struct GVarietyExtraType<GString>
				: GTrueType {};

			template<>
			struct GVarietyExtraType<GWString>
				: GTrueType {};

			template<typename T>
			struct GVarietyConstructible
				: GCatBase<GIsArithmetic<T>::value || GVarietyExtraType<T>::value>
			{
			};

			template<typename T>
			struct GVarietyGetValue 
				: GCatBase<GIsArithmetic<T>::value 
					|| GIsPointer<T>::value
					|| GVarietyExtraType<T>::value>
			{
			};

			template<typename T>
			struct GVarietyGetReference
				: GCatBase<GIsArithmetic<T>::value>
			{
			};

		}
	}
}

/// 一个使用union结构构件的变体结构（variant）
/// 为了与使用模板实现的变体类型区分，将其命名为GVariety
/// 由于union的局限性，其中可以保存的数据结构有限
/// 使用模板实现的变体结构则无此方面的限制，见GVariant
/// GVariety支持的数据类型有：
/// 基本内置类型：gbool、gchar、gschar、guchar、gwchar、gshort、gushort、gint、guint、
/// glong、gulong、glonglong、gulonglong、gfloat、gdouble、glongdouble，及这些类型的等价类型
/// 字符串GString、字节数组GBytes、宽字符串GWString
class GAPI GVariety
	: public GNewT<GVariety>
{
public:
	enum TYPE
	{
		VARIETY_TYPE_ILLEGAL = 0,
		VARIETY_TYPE_BOOL,
		VARIETY_TYPE_CHAR,
		VARIETY_TYPE_SCHAR,
		VARIETY_TYPE_UCHAR,
		VARIETY_TYPE_WCHAR,
		VARIETY_TYPE_SHORT,
		VARIETY_TYPE_USHORT,
		VARIETY_TYPE_INT,
		VARIETY_TYPE_UINT,
		VARIETY_TYPE_LONG,
		VARIETY_TYPE_ULONG,
		VARIETY_TYPE_LONGLONG,
		VARIETY_TYPE_ULONGLONG,
		VARIETY_TYPE_FLOAT,
		VARIETY_TYPE_DOUBLE,
		VARIETY_TYPE_LONGDOUBLE,
		VARIETY_TYPE_BYTES,			// 字节数组
		VARIETY_TYPE_STRING,		// 字符串
		VARIETY_TYPE_WSTRING,		// 字符串
		VARIETY_TYPE_DATETIME,		// 日期时间
		VARIETY_TYPE_POINTER,		// 指针
	};

public:
	GVariety();
	GVariety(gbool val);
	GVariety(gchar val);
	GVariety(gschar val);
	GVariety(guchar val);
	GVariety(gwchar val);
	GVariety(gshort val);
	GVariety(gushort val);
	GVariety(gint val);
	GVariety(guint val);
	GVariety(glong val);
	GVariety(gulong val);
	GVariety(glonglong val);
	GVariety(gulonglong val);
	GVariety(gfloat val);
	GVariety(gdouble val);
	GVariety(glongdouble val);
	GVariety(const GBytes &val);
	GVariety(const gchar *val);
	GVariety(const GString &val);
	GVariety(const gwchar *val);
	GVariety(const GWString &val);
	GVariety(const GDateTime &val);
	GVariety(gpointer val);
	GVariety(const GVariety &val);
	GVariety(GVariety &&val);
	~GVariety();

	TYPE GetType() const;
	gbool Valid() const;

	template<typename T> T GetValue() const;
	template<typename T> gbool TryGetValue(T &val) const;
	template<typename T> const T &GetReference() const;
	template<typename T> T &GetReference();
	//template<typename T> gvoid SetValue(const T &val);
	//template<typename T> gvoid SetValue(T &&val);

	GString ToString() const;

	GVariety &operator=(const GVariety &val);
	GVariety &operator=(GVariety &&val);

	gvoid SetValue(gbool val);
	gvoid SetValue(gchar val);
	gvoid SetValue(gschar val);
	gvoid SetValue(guchar val);
	gvoid SetValue(gwchar val);
	gvoid SetValue(gshort val);
	gvoid SetValue(gushort val);
	gvoid SetValue(gint val);
	gvoid SetValue(guint val);
	gvoid SetValue(glong val);
	gvoid SetValue(gulong val);
	gvoid SetValue(glonglong val);
	gvoid SetValue(gulonglong val);
	gvoid SetValue(gfloat val);
	gvoid SetValue(gdouble val);
	gvoid SetValue(glongdouble val);
	gvoid SetValue(const gchar *val);
	gvoid SetValue(const GString &val);
	gvoid SetValue(GString &&val);
	gvoid SetValue(const GVariety &val);
	gvoid SetPoiter(gpointer val);

	gbool ToBool(gbool def = false) const;
	gchar ToChar(gchar def = 0) const;
	gschar ToSChar(gschar def = 0) const;
	guchar ToUChar(guchar def = 0) const;
	gwchar ToWChar(gwchar def = 0) const;
	gshort ToShort(gshort def = 0) const;
	gushort ToUShort(gushort def = 0) const;
	gint ToInt(gint def = 0) const;
	guint ToUInt(guint def = 0) const;
	glong ToLong(glong def = 0) const;
	gulong ToULong(gulong def = 0) const;
	glonglong ToLongLong(glonglong def = 0) const;
	gulonglong ToULongLong(gulonglong def = 0) const;
	gfloat ToFloat(gfloat def = 0) const;
	gdouble ToDouble(gdouble def = 0) const;
	glongdouble ToLongDouble(glongdouble def) const;

	gsmall ToSmall(gsmall def = 0) const;
	gusmall ToUSmall(gusmall def = 0) const;
	gsize ToSize(gsize def = 0) const;
	gtime ToTime(gtime def = 0) const;

	greal ToReal(greal def = 0) const;
	gbyte ToByte(gbyte def = 0) const;
	gword ToWord(gword def = 0) const;
	gint8 ToInt8(gint8 def = 0) const;
	guint8 ToUInt8(guint8 def = 0) const;
	gint16 ToInt16(gint16 def = 0) const;
	guint16 ToUInt16(guint16 def = 0) const;
	gint32 ToInt32(gint32 def = 0) const;
	guint32 ToUInt32(guint32 def = 0) const;
	gint64 ToInt64(gint64 def = 0) const;
	guint64 ToUInt64(guint64 def = 0) const;
	gdecimal ToDecimal(gdecimal def = 0) const;

	gpointer GetPoiter() const;

private:
	gvoid Free();

	union
	{
		gbool			m_bVal;
		gchar			m_cVal;
		gschar			m_scVal;
		guchar			m_ucVal;
		gwchar			m_wcVal;
		gshort			m_sVal;
		gushort			m_usVal;
		gint			m_iVal;
		guint			m_uiVal;
		glong			m_lVal;
		gulong			m_ulVal;
		glonglong		m_llVal;
		gulonglong		m_ullVal;
		gfloat			m_fVal;
		gdouble			m_dVal;
		glongdouble		m_ldVal;
		gpointer		m_pVal;
		GBytesData		m_bytesVal;
		GStringData		m_strVal;
		GWStringData	m_wstrVal;
		gbyte			m_timeVal[G_DATE_TIME_SIZE];
	};
	gbyte m_nType;
};

#include "gvariety.inl"

#endif // _CORE_VARIETY_H_