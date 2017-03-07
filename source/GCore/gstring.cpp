#include "gstring.h"
#include "gstringlist.h"
#include "gcstringhelper.h"

GString::GString()
{
	
}

GString::GString(gchar c)
	: m_tString(1)
{
	m_tString.Resize(1);
	m_tString[0] = c;
}

GString::GString(const gchar *str)
{
	gsize size = GCStringHelper::Size(str);
	m_tString.Resize(size);
	GCStringHelper::Copy(str, size, m_tString.Start());
}

GString::GString(const gchar *str, gsize size)
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
	GCStringHelper::Trim(m_tString.Start(), new_size, str.Start(), new_size);
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
	GCStringHelper::TrimLeft(m_tString.Start(), new_size, str.Start(), new_size);
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
	GCStringHelper::TrimRight(m_tString.Start(), new_size, str.Start(), new_size);
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
	GCStringHelper::MakeUpper(str.m_tString.Start(), new_size);
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
	GCStringHelper::MakeLower(str.m_tString.Start(), new_size);
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

GStringList GString::Split(const GString &sSep, gbool bIgnoreEmpty, gbool bIsSensitive) const
{
	// TODO
	GStringList t;
	return t;
}

gsize GString::Find(gchar c, gsize start, gbool bIsSensitive) const
{
	// TODO
	return NULL_POS;
}

gsize GString::Find(const GString &str, gsize start, gbool bIsSensitive) const
{
	// TODO
	return NULL_POS;
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
