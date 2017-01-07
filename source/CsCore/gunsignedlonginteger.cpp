#include "gunsignedlonginteger.h"

gulong GUnsignedLongInteger::MaxValue()
{
	return G_UINT32L_MAX;
}

gulong GUnsignedLongInteger::MinValue()
{
	return 0L;
}

GUnsignedLongInteger GUnsignedLongInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GUnsignedLongInteger();
	}
	return str.ToULong();
}

GUnsignedLongInteger::GUnsignedLongInteger(gulong val)
: GNumber<gulong>(val)
{

}

GUnsignedLongInteger::GUnsignedLongInteger(const GUnsignedLongInteger &val)
: GNumber<gulong>(val)
{

}

guint GUnsignedLongInteger::ClassCode() const
{
	return GUnsignedLongInteger::CLASS_CODE;
}