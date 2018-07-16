#include "gstring8.h"
#include "gcstring.h"
#include "gclasscode.h"
#include "garchive.h"
#include "gutility.h"
#include <stdarg.h>
#include <stdio.h>
#include <sstream>
#include <string.h>

#define G_STRING_FORMAT_BUFFER_SIZE 4096

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace string { // gsystem.detail.string

template <typename T>
GString8 GNumberToString(T num, gint base)
{
	std::ostringstream oss;
	if (base == 2)
	{

	}
	else if (base == 8)
	{
		oss << std::oct;
	}
	else if (base == 10)
	{
		oss << std::dec;
	}
	else if (base == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << num;
	return GString8(oss.str().c_str());
}

template <typename T>
T GStringToNumber(const GString8 &str, gbool *isok)
{
	std::istringstream iss(str.CString());
	T num;
	if (isok) *isok = false;

	if (iss >> num)
	{
		if (isok) *isok = true;
	}
	return num;
}

} // namespace gsystem.detail.string
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

GString8 GString8::Number(gsmall num, gint base)
{
	return detail::string::GNumberToString<gsmall>(num, base);
}

GString8 GString8::Number(gusmall num, gint base)
{
	return detail::string::GNumberToString<gusmall>(num, base);
}

GString8 GString8::Number(gshort num, gint base)
{
	return detail::string::GNumberToString<gshort>(num, base);
}

GString8 GString8::Number(gushort num, gint base)
{
	return detail::string::GNumberToString<gushort>(num, base);
}

GString8 GString8::Number(gint num, gint base)
{
	return detail::string::GNumberToString<gint>(num, base);
}

GString8 GString8::Number(guint num, gint base)
{
	return detail::string::GNumberToString<guint>(num, base);
}

GString8 GString8::Number(glong num, gint base)
{
	return detail::string::GNumberToString<glong>(num, base);
}

GString8 GString8::Number(gulong num, gint base)
{
	return detail::string::GNumberToString<gulong>(num, base);
}

GString8 GString8::Number(glonglong num, gint base)
{
	return detail::string::GNumberToString<glonglong>(num, base);
}

GString8 GString8::Number(gulonglong num, gint base)
{
	return detail::string::GNumberToString<gulonglong>(num, base);
}

GString8 GString8::Number(gfloat num, gint base)
{
	return detail::string::GNumberToString<gfloat>(num, base);
}

GString8 GString8::Number(gdouble num, gint base)
{
	return detail::string::GNumberToString<gdouble>(num, base);
}

GString8 GString8::Number(glongdouble num, gint base)
{
	return detail::string::GNumberToString<glongdouble>(num, base);
}

gsmall GString8::ToSmall(gbool *ok) const
{
	return detail::string::GStringToNumber<gsmall>(*this, ok);
}

gusmall GString8::ToUSmall(gbool *ok) const
{
	return detail::string::GStringToNumber<gusmall>(*this, ok);
}

gshort GString8::ToShort(gbool *ok) const
{
	return detail::string::GStringToNumber<gshort>(*this, ok);
}

gushort GString8::ToUShort(gbool *ok) const
{
	return detail::string::GStringToNumber<gushort>(*this, ok);
}

gint GString8::ToInt(gbool *ok) const
{
	return detail::string::GStringToNumber<gint>(*this, ok);
}

guint GString8::ToUInt(gbool *ok) const
{
	return detail::string::GStringToNumber<guint>(*this, ok);
}

glong GString8::ToLong(gbool *ok) const
{
	return detail::string::GStringToNumber<glong>(*this, ok);
}

gulong GString8::ToULong(gbool *ok) const
{
	return detail::string::GStringToNumber<gulong>(*this, ok);
}

glonglong GString8::ToLongLong(gbool *ok) const
{
	return detail::string::GStringToNumber<glonglong>(*this, ok);
}

gulonglong GString8::ToULongLong(gbool *ok) const
{
	return detail::string::GStringToNumber<gulonglong>(*this, ok);
}

gfloat GString8::ToFloat(gbool *ok) const
{
	return detail::string::GStringToNumber<gfloat>(*this, ok);
}

gdouble GString8::ToDouble(gbool *ok) const
{
	return detail::string::GStringToNumber<gdouble>(*this, ok);
}

glongdouble GString8::ToLongDouble(gbool *ok) const
{
	return detail::string::GStringToNumber<glongdouble>(*this, ok);
}

GString8 GString8::ReferenceOf(gcstring8 str)
{
	gsize size = GCString::Size(str);
	if (size <= 0)
	{
		return GString8();
	}
	return GString8(GString8Data::ReferenceOf(str, size));
}

GString8 GString8::ReferenceOf(const GString8 &str)
{
	return ReferenceOf(str.CString());
}

GString8 GString8::Format(gcstring8 format, ...)
{
	// TODO，模仿QString自己实现一套
	va_list ap;
	va_start(ap, format);
	gchar8 limit[G_STRING_FORMAT_BUFFER_SIZE];
	limit[0] = '\0';
	vsnprintf_s(limit, G_STRING_FORMAT_BUFFER_SIZE, format, ap);
	va_end(ap);
	return GString8(limit);
}

GString8::GString8()
{
	
}

GString8::GString8(gchar8 c)
	: m_tString(1)
{
	m_tString.Resize(1);
	m_tString[0] = c;
}

GString8::GString8(gcstring8 str)
{
	gsize size = GCString::Size(str);
	m_tString.Resize(size);
	GCString::Copy(str, size, m_tString.Start());
}

GString8::GString8(gcstring8 str, gsize size)
	: m_tString(str, size)
{
	
}

GString8::GString8(const GString8 &str)
	: m_tString(str.m_tString)
{
	
}

GString8::GString8(GString8 &&str)
	: m_tString(GMove(str.m_tString))
{
	
}

GString8::GString8(const GString8Data &str)
	: m_tString(str)
{

}

GString8::GString8(GString8Data &&str)
	: m_tString(GForward<GString8Data>(str))
{

}

gbool GString8::IsEmpty() const
{
	return m_tString.IsEmpty();
}

GString8 GString8::Trim() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString8();
	}

	GString8Data str(new_size);
	str.Reserve(new_size);
	GCString::Trim(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString8 GString8::TrimLeft() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString8();
	}

	GString8Data str(new_size);
	str.Reserve(new_size);
	GCString::TrimLeft(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString8 GString8::TrimRight() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString8();
	}

	GString8Data str(new_size);
	str.Reserve(new_size);
	GCString::TrimRight(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString8 GString8::ToUpper() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString8();
	}

	GString8 str(*this);
	GCString::MakeUpper(str.m_tString.Start(), new_size);
	return str;
}

GString8 GString8::ToLower() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString8();
	}

	GString8 str(*this);
	GCString::MakeLower(str.m_tString.Start(), new_size);
	return str;
}

gcstring8 GString8::CString() const
{
	if (IsEmpty())
	{
		return "";
	}
	return m_tString.Start();
}

gsize GString8::Size() const
{
	return m_tString.Size();
}

gvoid GString8::Resize(gsize size)
{
	m_tString.Resize(size);
}

gvoid GString8::Reserve(gsize capacity)
{
	m_tString.Reserve(capacity);
}

gchar8 &GString8::GetAt(gsize pos)
{
	return m_tString.GetAt(pos);
}

const gchar8 &GString8::GetAt(gsize pos) const
{
	return m_tString.GetAt(pos);
}

gchar8 *GString8::CursorAt(gsize pos)
{
	return m_tString.CursorAt(pos);
}

const gchar8 *GString8::CursorAt(gsize pos) const
{
	return m_tString.CursorAt(pos);
}

GString8 &GString8::Replace(const GString8 &from, const GString8 &to, gbool bIsSensitive)
{
	/*
	gsize size = Size();
	gsize from_size = from.Size();
	if (size <= 0 || from_size <= 0)
	{
		return *this;
	}

	gcstring cfrom = from.CString();
	gcstring cto = to.CString();
	gsize to_size = to.Size();

	// 预算一下替换过后的长度，长度按尽量可能大去计算
	gsize estimate_size = size;
	if (from_size < to_size)
	{
		// 有可能会被扩容
		estimate_size = size * to_size / from_size + 1;
	}

	// 转换为值类型
	ToValue();
	GStringStore::TYPE nEstimateType = GetTypeBySize(estimate_size);

	if (nEstimateType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
	{
		// 替换之后为小字符串
		gchar8 cStr[G_SMALL_STRING_MAX_SIZE];
		gsize out_len = 0;
		if (!GCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			cStr, out_len))
		{
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sSmallStr.Initialize(cStr, out_len);
		return *this;
	}
	else if (nEstimateType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
	{
		// 替换之后为普通字符串
		gchar8 *pStr = (gchar*)GMalloc((estimate_size + 1) * sizeof(gchar));
		gsize out_len = 0;
		if (!GCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			pStr, out_len))
		{
			GFree(pStr);
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sNormalStr.m_pStr = pStr;
		m_tStringStore.m_sNormalStr.m_nSize = out_len;
		return *this;
	}
	else
	{
		// GStringStore::STRING_STORE_TYPE_VALUE_BIG
		// 替换之后为大字符串
		// TODO
	}
	*/
	return *this;
}

GStringListT<GString8> GString8::Split(const GString8 &sep, gbool ignoreEmpty, gbool isSensitive) const
{
	GStringListT<GString8> strs;
	if (sep.IsEmpty())
	{
		return strs;
	}
	GString8 str;
	str.Reserve(Size() + sep.Size());
	str.Append(*this);
	str.Append(sep);
	gsize size = str.Size();
	for (gsize i = 0; i < size; ++i)
	{
		gsize pos = str.Find(sep, i, isSensitive);
		if (pos < size)
		{
			if (ignoreEmpty)
			{
				// 忽略空格
				GString8 res = SubString(i, pos - i).Trim();
				if (!res.IsEmpty())
				{
					strs.Add(res);
				}
			}
			else
			{
				strs.Add(SubString(i, pos - i));
			}
			i = pos + sep.Size() - 1;
		}
	}
	return strs;
}

gsize GString8::Find(gchar8 c, gsize start, gbool isSensitive) const
{
	gsize size = Size();
	if (start > size)
	{
		return NULL_POS;
	}
	gint pos = GCString::Matcher(CursorAt(start), size - start, c, isSensitive);
	if (-1 == pos)
	{
		return NULL_POS;
	}
	return pos + start;
}

gsize GString8::Find(const GString8 &str, gsize start, gbool isSensitive) const
{
	gsize size = Size();
	if (start > size)
	{
		return NULL_POS;
	}
	gint pos = GCString::Matcher(CursorAt(start), size - start, str.CString(), str.Size(), isSensitive);
	if (-1 == pos)
	{
		return NULL_POS;
	}
	return pos + start;
}

GString8 GString8::SubString(gsize start, gsize size) const
{
	if (start >= Size() || start == NULL_POS ||
		size == 0 || size == MAX_SIZE)
	{
		return GString8();
	}
	return GString8(&m_tString[start], size);
}

gbool GString8::Equals(const GString8 &str, gbool bIsSensitive) const
{
	if (bIsSensitive)
	{
		return *this == str;
	}
	// TODO
	return false;
}

gbool GString8::StartWith(gchar8 c) const
{
	return m_tString[0] == c;
}

gbool GString8::EndWith(gchar8 c) const
{
	return m_tString[m_tString.Size() - 1] == c;
}

GString8 &GString8::Append(const GString8 &str)
{
	m_tString.Append(str.m_tString);
	return *this;
}

GString8 &GString8::Append(GString8 &&str)
{
	m_tString.Append(GMove(str.m_tString));
	return *this;
}

guint GString8::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::String);
}

GString8 GString8::ClassName() const GNOEXCEPT
{
	return GString8::ReferenceOf("gsystem::GString");
}

gbool GString8::Serialize(GArchive &archive) const
{
	archive.Attach(CString(), Size());
	return true;
}

gbool GString8::Deserialize(GArchive &archive)
{
	// TODO
	return false;
}

GString8 &GString8::operator=(const GString8 &str)
{
	if (this == &str)
	{
		return *this;
	}

	m_tString = str.m_tString;
	return *this;
}

GString8 &GString8::operator=(GString8 &&str)
{
	if (this == &str)
	{
		return *this;
	}

	m_tString = GMove(str.m_tString);
	return *this;
}

GString8 &GString8::operator+=(const GString8 &str)
{
	Append(str);
	return *this;
}

const gchar8 &GString8::operator[](gsize pos) const
{
	return m_tString[pos];
}

gchar8 &GString8::operator[](gsize pos)
{
	return m_tString[pos];
}

GString8 operator+(const GString8 &s1, const GString8 &s2)
{
	gsize size1 = s1.Size();
	gsize size2 = s2.Size();
	GString8Data str(size1 + size2);
	GCString::Copy(s1.m_tString.Start(), size1, str.Start());
	GCString::Copy(s2.m_tString.Start(), size2, str.CursorAt(size1));
	str.Resize(size1 + size2);
	return GString8(GMove(str));
}

gbool operator==(const GString8 &s1, const GString8 &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	if (s1.CString() == s2.CString())
	{
		return true;
	}
	if (s1.Size() != s2.Size())
	{
		return false;
	}
	return strcmp(s1.CString(), s2.CString()) == 0;
}

gbool operator!=(const GString8 &s1, const GString8 &s2)
{
	return !(s1 == s2);
}

gbool operator>(const GString8 &s1, const GString8 &s2)
{
	if (&s1 == &s2)
	{
		return false;
	}
	return strcmp(s1.CString(), s2.CString()) > 0;
}

gbool operator>=(const GString8 &s1, const GString8 &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	return strcmp(s1.CString(), s2.CString()) >= 0;
}

gbool operator<(const GString8 &s1, const GString8 &s2)
{
	if (&s1 == &s2)
	{
		return false;
	}
	return strcmp(s1.CString(), s2.CString()) < 0;
}

gbool operator<=(const GString8 &s1, const GString8 &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	return strcmp(s1.CString(), s2.CString()) <= 0;
}

} // namespace gsystem
