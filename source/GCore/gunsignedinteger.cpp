#include "gunsignedinteger.h"

guint GUnsignedInteger::MaxValue()
{
	return G_UINT32_MAX;
}

guint GUnsignedInteger::MinValue()
{
	return 0;
}

GUnsignedInteger GUnsignedInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GUnsignedInteger();
	}
	return str.ToUInt();
}

GUnsignedInteger::GUnsignedInteger(guint val)
: GNumber<guint>(val)
{

}

GUnsignedInteger::GUnsignedInteger(const GUnsignedInteger &val)
: GNumber<guint>(val)
{

}

GUnsignedInteger::~GUnsignedInteger()
{

}

guint GUnsignedInteger::ClassCode() const
{
	return GUnsignedInteger::CLASS_CODE;
}