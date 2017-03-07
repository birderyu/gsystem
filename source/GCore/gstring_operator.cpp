#include "gstring.h"
#include "gcstringhelper.h"

GString &GString::operator=(const GString &str)
{
	if (this == &str)
	{
		return *this;
	}

	m_tString = str.m_tString;
	return *this;
}

GString &GString::operator=(GString &&str)
{
	if (this == &str)
	{
		return *this;
	}

	m_tString = GMove(str.m_tString);
	return *this;
}

GString &GString::operator+=(const GString &str)
{
	Append(str);
	return *this;
}

const gchar &GString::operator[](gsize pos) const
{
	return m_tString[pos];
}

gchar &GString::operator[](gsize pos)
{
	return m_tString[pos];
}

GString operator+(const GString &s1, const GString &s2)
{
	gsize size1 = s1.Size();
	gsize size2 = s2.Size();
	GStringData str(size1 + size2);
	GCStringHelper::Copy(s1.m_tString.Start(), size1, str.Start());
	GCStringHelper::Copy(s2.m_tString.Start(), size2, str.CursorAt(size1));
	str.Resize(size1 + size2);
	return GString(GMove(str));
}

gbool operator==(const GString &s1, const GString &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	return strcmp(s1.CString(), s2.CString()) == 0;
}

gbool operator!=(const GString &s1, const GString &s2)
{
	return !(s1 == s2);
}

gbool operator>(const GString &s1, const GString &s2)
{
	if (&s1 == &s2)
	{
		return false;
	}
	return strcmp(s1.CString(), s2.CString()) > 0;
}

gbool operator>=(const GString &s1, const GString &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	return strcmp(s1.CString(), s2.CString()) >= 0;
}

gbool operator<(const GString &s1, const GString &s2)
{
	if (&s1 == &s2)
	{
		return false;
	}
	return strcmp(s1.CString(), s2.CString()) < 0;
}

gbool operator<=(const GString &s1, const GString &s2)
{
	if (&s1 == &s2)
	{
		return true;
	}
	return strcmp(s1.CString(), s2.CString()) <= 0;
}