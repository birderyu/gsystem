#include "gstring.h"
#include <sstream>

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace string { // gsystem.detail.string

template <typename T>
GString GNumberToString(T num, gint base)
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
	return GString(oss.str().c_str());
}

template <typename T>
T GStringToNumber(const GString &str, gbool *isok)
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

GString GString::Number(gsmall num, gint base)
{
	return detail::string::GNumberToString<gsmall>(num, base);
}

GString GString::Number(gusmall num, gint base)
{
	return detail::string::GNumberToString<gusmall>(num, base);
}

GString GString::Number(gshort num, gint base)
{
	return detail::string::GNumberToString<gshort>(num, base);
}

GString GString::Number(gushort num, gint base)
{
	return detail::string::GNumberToString<gushort>(num, base);
}

GString GString::Number(gint num, gint base)
{
	return detail::string::GNumberToString<gint>(num, base);
}

GString GString::Number(guint num, gint base)
{
	return detail::string::GNumberToString<guint>(num, base);
}

GString GString::Number(glong num, gint base)
{
	return detail::string::GNumberToString<glong>(num, base);
}

GString GString::Number(gulong num, gint base)
{
	return detail::string::GNumberToString<gulong>(num, base);
}

GString GString::Number(glonglong num, gint base)
{
	return detail::string::GNumberToString<glonglong>(num, base);
}

GString GString::Number(gulonglong num, gint base)
{
	return detail::string::GNumberToString<gulonglong>(num, base);
}

GString GString::Number(gfloat num, gint base)
{
	return detail::string::GNumberToString<gfloat>(num, base);
}

GString GString::Number(gdouble num, gint base)
{
	return detail::string::GNumberToString<gdouble>(num, base);
}

GString GString::Number(gdecimal num, gint base)
{
	return detail::string::GNumberToString<gdecimal>(num, base);
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
