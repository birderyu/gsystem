#include "gstring.h"
#include "gstringlist.h"
#include "gcstring.h"
#include <stdarg.h>
#include <stdio.h>

#define G_STRING_FORMAT_BUFFER_SIZE 4096

namespace gsystem { // gsystem

GString GString::ReferenceOf(gcstring str)
{
	gsize size = GCString::Size(str);
	if (size <= 0)
	{
		return GString();
	}
	return GString(GStringData::ReferenceOf(str, size));
}

GString GString::ReferenceOf(const GString &str)
{
	return ReferenceOf(str.CString());
}

GString GString::Format(gcstring format, ...)
{
	// TODO，模仿QString自己实现一套
	va_list ap;
	va_start(ap, format);
	gchar limit[G_STRING_FORMAT_BUFFER_SIZE];
	limit[0] = '\0';
	vsnprintf_s(limit, G_STRING_FORMAT_BUFFER_SIZE, format, ap);
	va_end(ap);
	return GString(limit);
}

GString::GString()
{
	
}

GString::GString(gchar c)
	: m_tString(1)
{
	m_tString.Resize(1);
	m_tString[0] = c;
}

GString::GString(gcstring str)
{
	gsize size = GCString::Size(str);
	m_tString.Resize(size);
	GCString::Copy(str, size, m_tString.Start());
}

GString::GString(gcstring str, gsize size)
	: m_tString(str, size)
{
	
}

GString::GString(const GString &str)
	: m_tString(str.m_tString)
{
	
}

GString::GString(GString &&str)
	: m_tString(GMove(str.m_tString))
{
	
}

GString::GString(const GStringData &str)
	: m_tString(str)
{

}

GString::GString(GStringData &&str)
	: m_tString(GForward<GStringData>(str))
{

}

gbool GString::IsEmpty() const
{
	return m_tString.IsEmpty();
}

GString GString::Trim() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString();
	}

	GStringData str(new_size);
	str.Reserve(new_size);
	GCString::Trim(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString GString::TrimLeft() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString();
	}

	GStringData str(new_size);
	str.Reserve(new_size);
	GCString::TrimLeft(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString GString::TrimRight() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString();
	}

	GStringData str(new_size);
	str.Reserve(new_size);
	GCString::TrimRight(m_tString.Start(), new_size, str.Start(), new_size);
	str.Resize(new_size);
	return str;
}

GString GString::ToUpper() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString();
	}

	GString str(*this);
	GCString::MakeUpper(str.m_tString.Start(), new_size);
	return str;
}

GString GString::ToLower() const
{
	gsize new_size = Size();
	if (0 == new_size)
	{
		return GString();
	}

	GString str(*this);
	GCString::MakeLower(str.m_tString.Start(), new_size);
	return str;
}

gcstring GString::CString() const
{
	if (IsEmpty())
	{
		return "";
	}
	return m_tString.Start();
}

gsize GString::Size() const
{
	return m_tString.Size();
}

gvoid GString::Resize(gsize size)
{
	m_tString.Resize(size);
}

gvoid GString::Reserve(gsize capacity)
{
	m_tString.Reserve(capacity);
}

gchar &GString::GetAt(gsize pos)
{
	return m_tString.GetAt(pos);
}

const gchar &GString::GetAt(gsize pos) const
{
	return m_tString.GetAt(pos);
}

gchar *GString::CursorAt(gsize pos)
{
	return m_tString.CursorAt(pos);
}

const gchar *GString::CursorAt(gsize pos) const
{
	return m_tString.CursorAt(pos);
}

GString &GString::Replace(const GString &from, const GString &to, gbool bIsSensitive)
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
		gchar cStr[G_SMALL_STRING_MAX_SIZE];
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
		gchar *pStr = (gchar*)GMalloc((estimate_size + 1) * sizeof(gchar));
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

GStringList GString::Split(const GString &sep, gbool ignoreEmpty, gbool isSensitive) const
{
	GStringList strs;
	if (sep.IsEmpty())
	{
		return strs;
	}
	GString str;
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
				GString res = SubString(i, pos - i).Trim();
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

gsize GString::Find(gchar c, gsize start, gbool isSensitive) const
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

gsize GString::Find(const GString &str, gsize start, gbool isSensitive) const
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

GString GString::SubString(gsize start, gsize size) const
{
	if (start >= Size() || start == NULL_POS ||
		size == 0 || size == MAX_SIZE)
	{
		return GString();
	}
	return GString(&m_tString[start], size);
}

gbool GString::Equals(const GString &str, gbool bIsSensitive) const
{
	if (bIsSensitive)
	{
		return *this == str;
	}
	return false;
}

gbool GString::StartWith(gchar c) const
{
	return m_tString[0] == c;
}

gbool GString::EndWith(gchar c) const
{
	return m_tString[m_tString.Size() - 1] == c;
}

gvoid GString::Append(const GString &str)
{
	m_tString.Append(str.m_tString);
}

gvoid GString::Append(GString &&str)
{
	m_tString.Append(GMove(str.m_tString));
}

} // namespace gsystem
