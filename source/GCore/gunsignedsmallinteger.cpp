#include "gunsignedsmallinteger.h"

namespace gsystem { // gsystem

gusmall GUnsignedSmallInteger::MaxValue()
{
	return G_UINT8_MAX;
}

gusmall GUnsignedSmallInteger::MinValue()
{
	return 0;
}

GUnsignedSmallInteger GUnsignedSmallInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GUnsignedSmallInteger();
	}
	return str.ToUSmall();
}

GUnsignedSmallInteger::GUnsignedSmallInteger(gusmall val)
: GNumber<gusmall>(val)
{

}

GUnsignedSmallInteger::GUnsignedSmallInteger(const GUnsignedSmallInteger &val)
: GNumber<gusmall>(val)
{

}

GUnsignedSmallInteger::~GUnsignedSmallInteger()
{

}

guint GUnsignedSmallInteger::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::UnsignedSmallInteger);
}

} // namespace gsystem
