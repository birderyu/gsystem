#ifndef _CORE_BASE_STRING_H_
#define _CORE_BASE_STRING_H_

#include "gseries.h"

namespace gsystem {

/****************************************************************************
**
** @brief 基础字符串类型
**
****************************************************************************/
template<typename CharT, gsize LOCAL_SIZE>
class GBaseString
{

private:
	typedef GSeries<CharT, LOCAL_SIZE, true, 0> StringDataT;

public:
	typedef	CharT *			StringT;
	typedef	const CharT *	CStringT;

public:
	GBaseString();
	GBaseString(CharT c);
	GBaseString(CStringT str);
	GBaseString(const GBaseString<CharT, LOCAL_SIZE> &str);
	GBaseString(GBaseString<CharT, LOCAL_SIZE> &&str);

	CStringT CString() const;

	gsize Size() const;
	gbool IsEmpty() const;
	CharT &GetAt(gsize pos);
	const CharT &GetAt(gsize pos) const;
	CharT *CursorAt(gsize pos);
	const CharT *CursorAt(gsize pos) const;
	gvoid Resize(gsize size);
	gvoid Reserve(gsize size);
	gbool StartWith(CharT c) const;
	gbool EndWith(CharT c) const;
	gvoid Append(const GBaseString<CharT, LOCAL_SIZE> &str);
	gvoid Append(GBaseString<CharT, LOCAL_SIZE> &&str);
	GBaseString<CharT, LOCAL_SIZE> Trim() const;
	GBaseString<CharT, LOCAL_SIZE> TrimLeft() const;
	GBaseString<CharT, LOCAL_SIZE> TrimRight() const;
	GBaseString<CharT, LOCAL_SIZE> ToUpper() const;
	GBaseString<CharT, LOCAL_SIZE> ToLower() const;
	GBaseString<CharT, LOCAL_SIZE> &Replace(const GBaseString<CharT, LOCAL_SIZE> &from, const GBaseString<CharT, LOCAL_SIZE> &to, gbool isSensitive);
	gsize Find(CharT c, gsize start, gbool isSensitive) const;
	gsize Find(const GBaseString<CharT, LOCAL_SIZE> &str, gsize start, gbool isSensitive) const;
	GBaseString<CharT, LOCAL_SIZE> SubString(gsize start, gsize length) const;

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

	GBaseString<CharT, LOCAL_SIZE> &operator=(const GBaseString<CharT, LOCAL_SIZE> &str);
	GBaseString<CharT, LOCAL_SIZE> &operator=(GBaseString<CharT, LOCAL_SIZE> &&sStr);
	GBaseString<CharT, LOCAL_SIZE> &operator=(CStringT str);
	GBaseString<CharT, LOCAL_SIZE> &operator=(CharT c);
	GBaseString<CharT, LOCAL_SIZE> &operator+=(const GBaseString<CharT, LOCAL_SIZE> &sStr);
	const CharT &operator[](gsize pos) const;
	CharT &operator[](gsize pos);

	gbool Equals(const GBaseString<CharT, LOCAL_SIZE> &str, gbool isSensitive) const;
	GStringListT<GBaseString<CharT, LOCAL_SIZE>> Split(const GBaseString<CharT, LOCAL_SIZE> &sep, gbool ignoreEmpty, gbool isSensitive) const;

protected:
	GBaseString(CStringT str, gsize size);
	GBaseString(const StringDataT &str);
	GBaseString(StringDataT &&str);

protected:
	StringDataT m_tString;
};

}

#include "inline/gbasestring.inl"

#endif // _CORE_BASE_STRING_H_