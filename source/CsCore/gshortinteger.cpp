#include "gshortinteger.h"

gshort GShortInteger::MaxValue()
{
	return G_INT16_MAX;
}

gshort GShortInteger::MinValue()
{
	return G_INT16_MIN;
}

GShortInteger GShortInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GShortInteger();
	}
	return str.ToShort();
}

GShortInteger::GShortInteger(gshort val)
: GNumber<gshort>(val)
{

}

GShortInteger::GShortInteger(const GShortInteger &val)
: GNumber<gshort>(val)
{

}

GShortInteger::~GShortInteger()
{

}

guint GShortInteger::ClassCode() const
{
	return GShortInteger::CLASS_CODE;
}