#include "gsmallinteger.h"

gsmall GSmallInteger::MaxValue()
{
	return G_INT8_MAX;
}

gsmall GSmallInteger::MinValue()
{
	return G_INT8_MIN;
}

GSmallInteger GSmallInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GSmallInteger();
	}
	return str.ToSmall();
}

GSmallInteger::GSmallInteger(gsmall val)
: GNumber<gsmall>(val)
{

}

GSmallInteger::GSmallInteger(const GSmallInteger &val)
: GNumber<gsmall>(val)
{

}

guint GSmallInteger::ClassCode() const
{
	return GSmallInteger::CLASS_CODE;
}