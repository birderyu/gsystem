#include "gstring.h"
#include <sstream>

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace string { // gsystem.detail.string

template <typename T>
GString GNumberToString(T nNum, gint nBase)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << nNum;
	return GString(oss.str().c_str());
}

template <typename T>
T GStringToNumber(const GString &str, gbool *isok)
{
	std::istringstream iss(str.CString());
	T nNum;
	if (isok) *isok = false;

	if (iss >> nNum)
	{
		if (isok) *isok = true;
	}
	return nNum;
}

} // namespace gsystem.detail.string
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

GString GString::Number(gsmall nNum, gint nBase)
{
	return detail::string::GNumberToString<gsmall>(nNum, nBase);
}

GString GString::Number(gusmall nNum, gint nBase)
{
	return detail::string::GNumberToString<gusmall>(nNum, nBase);
}

GString GString::Number(gshort nNum, gint nBase)
{
	return detail::string::GNumberToString<gshort>(nNum, nBase);
}

GString GString::Number(gushort nNum, gint nBase)
{
	return detail::string::GNumberToString<gushort>(nNum, nBase);
}

GString GString::Number(gint nNum, gint nBase)
{
	return detail::string::GNumberToString<gint>(nNum, nBase);
}

GString GString::Number(guint nNum, gint nBase)
{
	return detail::string::GNumberToString<guint>(nNum, nBase);
}

GString GString::Number(glong nNum, gint nBase)
{
	return detail::string::GNumberToString<glong>(nNum, nBase);
}

GString GString::Number(gulong nNum, gint nBase)
{
	return detail::string::GNumberToString<gulong>(nNum, nBase);
}

GString GString::Number(glonglong nNum, gint nBase)
{
	return detail::string::GNumberToString<glonglong>(nNum, nBase);
}

GString GString::Number(gulonglong nNum, gint nBase)
{
	return detail::string::GNumberToString<gulonglong>(nNum, nBase);
}

GString GString::Number(gfloat nNum, gint nBase)
{
	return detail::string::GNumberToString<gfloat>(nNum, nBase);
}

GString GString::Number(gdouble nNum, gint nBase)
{
	return detail::string::GNumberToString<gdouble>(nNum, nBase);
}

GString GString::Number(gdecimal nNum, gint nBase)
{
	return detail::string::GNumberToString<gdecimal>(nNum, nBase);
}

gsmall GString::ToSmall(gbool *ok) const
{
	return detail::string::GStringToNumber<gsmall>(*this, ok);
}

gusmall GString::ToUSmall(gbool *ok) const
{
	return detail::string::GStringToNumber<gusmall>(*this, ok);
}

gshort GString::ToShort(gbool *ok) const
{
	return detail::string::GStringToNumber<gshort>(*this, ok);
}

gushort GString::ToUShort(gbool *ok) const
{
	return detail::string::GStringToNumber<gushort>(*this, ok);
}

gint GString::ToInt(gbool *ok) const
{
	return detail::string::GStringToNumber<gint>(*this, ok);
}

guint GString::ToUInt(gbool *ok) const
{
	return detail::string::GStringToNumber<guint>(*this, ok);
}

glong GString::ToLong(gbool *ok) const
{
	return detail::string::GStringToNumber<glong>(*this, ok);
}

gulong GString::ToULong(gbool *ok) const
{
	return detail::string::GStringToNumber<gulong>(*this, ok);
}

glonglong GString::ToLongLong(gbool *ok) const
{
	return detail::string::GStringToNumber<glonglong>(*this, ok);
}

gulonglong GString::ToULongLong(gbool *ok) const
{
	return detail::string::GStringToNumber<gulonglong>(*this, ok);
}

gfloat GString::ToFloat(gbool *ok) const
{
	return detail::string::GStringToNumber<gfloat>(*this, ok);
}

gdouble GString::ToDouble(gbool *ok) const
{
	return detail::string::GStringToNumber<gdouble>(*this, ok);
}

glongdouble GString::ToLongDouble(gbool *ok) const
{
	return detail::string::GStringToNumber<glongdouble>(*this, ok);
}

} // namespace gsystem
