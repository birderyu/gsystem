#include "gunsignedshortinteger.h"

gushort GUnsignedShortInteger::MaxValue()
{
	return G_UINT16_MAX;
}

gushort GUnsignedShortInteger::MinValue()
{
	return 0;
}

GUnsignedShortInteger GUnsignedShortInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GUnsignedShortInteger();
	}
	return str.ToUShort();
}

GUnsignedShortInteger::GUnsignedShortInteger(gushort val)
: GNumber<gushort>(val)
{

}

GUnsignedShortInteger::GUnsignedShortInteger(const GUnsignedShortInteger &val)
: GNumber<gushort>(val)
{

}

GUnsignedShortInteger::~GUnsignedShortInteger()
{

}

guint GUnsignedShortInteger::ClassCode() const
{
	return GUnsignedShortInteger::CLASS_CODE;
}