/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @author	Birderyu
** @contact	https://github.com/birderyu
** @file	gstring.h
** @date	2016-12-03
** @brief	字符串类型的定义
**
****************************************************************************/

#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "gobject.h"
#include "gstructure.h"
#include "gstringstore.h"
#include <string>

class GStringList;

/****************************************************************************
**
** gstring.h
**
** @class	GString
** @module	CsCore
** @brief	字符串类型
**
****************************************************************************/
class GAPI GString final 
	: public GListT<GString>
	, public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_STRING, };
public:
	static GString FromNum(gsmall nNum, gint nBase = 10);
	static GString FromNum(gusmall nNum, gint nBase = 10);
	static GString FromNum(gshort nNum, gint nBase = 10);
	static GString FromNum(gushort nNum, gint nBase = 10);
	static GString FromNum(gint nNum, gint nBase = 10);
	static GString FromNum(guint nNum, gint nBase = 10);
	static GString FromNum(glong nNum, gint nBase = 10);
	static GString FromNum(gulong nNum, gint nBase = 10);
	static GString FromNum(glonglong nNum, gint nBase = 10);
	static GString FromNum(gulonglong nNum, gint nBase = 10);
	static GString FromNum(gfloat nNum, gint nBase = 10);
	static GString FromNum(gdouble nNum, gint nBase = 10);
	static GString FromNum(gdecimal nNum, gint nBase = 10);

	static GString FromStdString(const std::string &sStr);

public:
	/****************************************************************************
	**
	** CsString
	**
	** @name	CsString
	** @brief	构造函数（constructor）
	**
	****************************************************************************/
	GString();
	GString(gchar cChar);
	GString(const gchar *pStr);
	GString(const GString &sStr);
	~GString();

	gsize Size() const;
	gbool Resize(gsize);

	gchar GetAt(gsize pos) const;
	gchar &GetAt(gsize pos);

	const gchar *Cursor(gsize pos) const;
	gchar *Cursor(gsize pos);

	gbool Equals(const GString &, gbool bIsSensitive = true) const;

	gbool StartWith(gchar c) const;
	gbool EndWith(gchar c) const;

	friend GAPI GString operator+(const GString &s1, const GString &s2);
	friend GAPI gbool operator>(const GString &s1, const GString &s2);
	friend GAPI gbool operator<(const GString &s1, const GString &s2);

	/// 运算符重载
	gbool operator==(const GString &sStr) const;
	GString &operator=(const GString &sStr);
	GString &operator+=(const GString &sStr);
	gchar operator[](gsize) const;
	gchar &operator[](gsize);
	gbool operator<(const GString &);
	gbool operator>(const GString &);

	gsmall ToSmall(gbool *bIsOk = NULL) const;
	gusmall ToUSmall(gbool *bIsOk = NULL) const;
	gshort ToShort(gbool *bIsOk = NULL) const;
	gushort ToUShort(gbool *bIsOk = NULL) const;
	gint ToInt(gbool *bIsOk = NULL) const;
	guint ToUInt(gbool *bIsOk = NULL) const;
	glong ToLong(gbool *bIsOk = NULL) const;
	gulong ToULong(gbool *bIsOk = NULL) const;
	glonglong ToLongLong(gbool *bIsOk = NULL) const;
	gulonglong ToULongLong(gbool *bIsOk = NULL) const;
	gfloat ToFloat(gbool *bIsOk = NULL) const;
	gdouble ToDouble(gbool *bIsOk = NULL) const;
	gdecimal ToDecimal(gbool *bIsOk = NULL) const;

	gbool IsEmpty() const;

	GString Trim() const;
	GString TrimLeft() const;
	GString TrimRight() const;

	GString ToUpper() const;
	GString ToLower() const;
	gcstring CString() const;
	GString &Replace(const GString &from, const GString &to, gbool bIsSensitive = true);
 
	// bIgnoreEmpty：是否忽略空格
	// bIsSensitive：大小写是否敏感
	GStringList Split(const GString &sSep, gbool bIgnoreEmpty = false, gbool bIsSensitive = true) const;
	gsize Find(gchar c, gsize start = 0, gbool bIsSensitive = true) const;
	gsize Find(const GString &str, gsize start = 0, gbool bIsSensitive = true) const;

	GString SubString(gsize start, gsize length) const;

	// 继承自Object的方法
	const GObject *Boxing() const;
	guint ClassCode() const;
	GString ToString() const;
	GString Format() const;

private:
	gbool IsReference() const;
	gvoid Free();
	GString &ToValue();
	GStringStore::TYPE GetTypeBySize(gsize) const;
	gbool Switch(GStringStore::TYPE);

	GStringStore m_tStringStore;
};

GAPI GString operator+(const GString &s1, const GString &s2);
GAPI gbool operator>(const GString &s1, const GString &s2);
GAPI gbool operator<(const GString &s1, const GString &s2);

#endif // _CORE_STRING_H_
