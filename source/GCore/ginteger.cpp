#include "ginteger.h"

gint GInteger::MaxValue()
{
	return G_INT32_MAX;
}

gint GInteger::MinValue()
{
	return G_INT32_MIN;
}

GInteger GInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GInteger();
	}
	return str.ToInt();
}

GInteger::GInteger(gint val)
: GNumber<gint>(val)
{

}

GInteger::GInteger(const GInteger &val)
: GNumber<gint>(val)
{

}

guint GInteger::ClassCode() const
{
	return GInteger::CLASS_CODE;
}