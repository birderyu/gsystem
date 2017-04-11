#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "gseries.h"
#include "gserializable.h"

namespace gsystem { // gsystem
	class GVariety;
	class GStringList;
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	以8个字节为1个字符的字符串类型
**
** 该字符串中的字符，是以8个字节为单位的，因此它可以表示
**
****************************************************************************/
class GAPI GString final 
	: public GArray<gchar>
	, public GSerializable
{
	friend class GVariety;
	friend GAPI GString operator+(const GString &s1, const GString &s2);
	friend GAPI gbool operator==(const GString &s1, const GString &s2);
	friend GAPI gbool operator!=(const GString &s1, const GString &s2);
	friend GAPI gbool operator>(const GString &s1, const GString &s2);
	friend GAPI gbool operator>=(const GString &s1, const GString &s2);
	friend GAPI gbool operator<(const GString &s1, const GString &s2);
	friend GAPI gbool operator<=(const GString &s1, const GString &s2);

public: // 静态方法
	static GString Number(gsmall num, gint base = 10);
	static GString Number(gusmall num, gint base = 10);
	static GString Number(gshort num, gint base = 10);
	static GString Number(gushort num, gint base = 10);
	static GString Number(gint num, gint base = 10);
	static GString Number(guint num, gint base = 10);
	static GString Number(glong num, gint base = 10);
	static GString Number(gulong num, gint base = 10);
	static GString Number(glonglong num, gint base = 10);
	static GString Number(gulonglong num, gint base = 10);
	static GString Number(gfloat num, gint base = 10);
	static GString Number(gdouble num, gint base = 10);
	static GString Number(gdecimal num, gint base = 10);

	static GString ReferenceOf(gcstring str);
	static GString ReferenceOf(const GString &str);
	static GString Format(gcstring format, ...);

public: // 构造方法
	GString();
	GString(gchar c);
	GString(gcstring str);
	GString(const GString &str);
	GString(GString &&str);

public: // Array行为
	gsize Size() const;
	gsize Length() const; // 字符的长度
	gbool IsEmpty() const;
	gchar &GetAt(gsize pos);
	const gchar &GetAt(gsize pos) const;
	gchar *CursorAt(gsize);
	const gchar *CursorAt(gsize) const;
	gvoid Resize(gsize size);
	gvoid Reserve(gsize size);
	gbool StartWith(gchar c) const;
	gbool EndWith(gchar c) const;
	gvoid Append(const GString &str);
	gvoid Append(GString &&str);

public: // 字符串行为
	gbool Equals(const GString &str, gbool bIsSensitive = true) const;
	GString Trim() const;
	GString TrimLeft() const;
	GString TrimRight() const;
	GString ToUpper() const;
	GString ToLower() const;
	gcstring CString() const;
	GString &Replace(const GString &from, const GString &to, gbool bIsSensitive = true);
	// ignoreEmpty：是否忽略空格; isSensitive：大小写是否敏感
	GStringList Split(const GString &sep, gbool ignoreEmpty = false, gbool isSensitive = true) const;
	gsize Find(gchar c, gsize start = 0, gbool bIsSensitive = true) const;
	gsize Find(const GString &str, gsize start = 0, gbool bIsSensitive = true) const;
	GString SubString(gsize start, gsize length) const;

public: // 数字转换
	gsmall ToSmall(gbool *bIsOk = GNULL) const;
	gusmall ToUSmall(gbool *bIsOk = GNULL) const;
	gshort ToShort(gbool *bIsOk = GNULL) const;
	gushort ToUShort(gbool *bIsOk = GNULL) const;
	gint ToInt(gbool *bIsOk = GNULL) const;
	guint ToUInt(gbool *bIsOk = GNULL) const;
	glong ToLong(gbool *bIsOk = GNULL) const;
	gulong ToULong(gbool *bIsOk = GNULL) const;
	glonglong ToLongLong(gbool *bIsOk = GNULL) const;
	gulonglong ToULongLong(gbool *bIsOk = GNULL) const;
	gfloat ToFloat(gbool *bIsOk = GNULL) const;
	gdouble ToDouble(gbool *bIsOk = GNULL) const;
	glongdouble ToLongDouble(gbool *bIsOk = GNULL) const;

public: // Object
	const GObject *Boxing() const;
	GString ToString() const;

public: // Serializable
	guint ClassCode() const GNOEXCEPT;
	GString ClassName() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

public: // 运算符重载
	GString &operator=(const GString &str);
	GString &operator=(GString &&sStr);
	GString &operator+=(const GString &sStr);
	const gchar &operator[](gsize) const;
	gchar &operator[](gsize);

private: // 私有方法
	GString(gcstring str, gsize size);
	GString(const GStringData &str);
	GString(GStringData &&str);

private: // 私有成员
	GStringData m_tString;
};

/// 运算符
GAPI GString operator+(const GString &s1, const GString &s2);
GAPI gbool operator==(const GString &s1, const GString &s2);
GAPI gbool operator!=(const GString &s1, const GString &s2);
GAPI gbool operator>(const GString &s1, const GString &s2);
GAPI gbool operator>=(const GString &s1, const GString &s2);
GAPI gbool operator<(const GString &s1, const GString &s2);
GAPI gbool operator<=(const GString &s1, const GString &s2);

typedef GString GString8;

} // namespace gsystem

#endif // _CORE_STRING_H_
