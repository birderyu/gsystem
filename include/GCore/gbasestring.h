#ifndef _CORE_BASE_STRING_H_
#define _CORE_BASE_STRING_H_

#include "gseries.h"
#include "gserializable.h"
#include "gcharset.h"

// 字符串本地存储空间的字节数目
#define G_BASE_STRING_LOCAL_BYTE_SIZE 8

namespace gsystem {

template<typename CharT>
class GBaseString
	: public GArray<CharT>
	, public GSerializable
{
public:
	typedef	CharT *			StringT;
	typedef	const CharT *	CStringT;

private:
	typedef GSeries<CharT, LocalSize(), true, 0> StringDataT;

public:
	GBaseString();
	GBaseString(CharT c);
	GBaseString(CStringT str);
	GBaseString(const GBaseString<CharT> &str);
	GBaseString(GBaseString<CharT> &&str);
	virtual ~GBaseString() = 0;

	CStringT CString() const;

	gsize Size() const;
	gsize Length() const; // 字符的长度
	gbool IsEmpty() const;
	CharT &GetAt(gsize pos);
	const CharT &GetAt(gsize pos) const;
	CharT *CursorAt(gsize);
	const CharT *CursorAt(gsize) const;
	gvoid Resize(gsize size);
	gvoid Reserve(gsize size);
	gbool StartWith(CharT c) const;
	gbool EndWith(CharT c) const;
	gvoid Append(const GBaseString<CharT> &str);
	gvoid Append(GBaseString<CharT> &&str);
	GBaseString<CharT> Trim() const;
	GBaseString<CharT> TrimLeft() const;
	GBaseString<CharT> TrimRight() const;
	GBaseString<CharT> ToUpper() const;
	GBaseString<CharT> ToLower() const;
	GBaseString<CharT> &Replace(const GBaseString<CharT> &from, const GBaseString<CharT> &to, gbool isSensitive);
	gsize Find(CharT c, gsize start, gbool isSensitive) const;
	gsize Find(const GBaseString<CharT> &str, gsize start, gbool isSensitive) const;
	GBaseString<CharT> SubString(gsize start, gsize length) const;

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

	GBaseString<CharT> &operator=(const GBaseString<CharT> &str);
	GBaseString<CharT> &operator=(GBaseString<CharT> &&sStr);
	GBaseString<CharT> &operator=(CStringT str);
	GBaseString<CharT> &operator=(CharT c);
	GBaseString<CharT> &operator+=(const GBaseString<CharT> &sStr);
	const CharT &operator[](gsize pos) const;
	CharT &operator[](gsize pos);

private:
	constexpr static gsize LocalSize()
	{
		return G_BASE_STRING_LOCAL_BYTE_SIZE / sizeof(CharT);
	}

protected:
	GBaseString(CStringT str, gsize size);
	GBaseString(const StringDataT &str);
	GBaseString(StringDataT &&str);

protected:
	StringDataT m_tString;
	GCharSet m_emCharSet;
};

}

#undef G_BASE_STRING_LOCAL_BYTE_SIZE

#endif // _CORE_BASE_STRING_H_