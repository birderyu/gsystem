#include "gunsignedlonglonginteger.h"

gulonglong GUnsignedLongLongInteger::MaxValue()
{
	return G_UINT64_MAX;
}

gulonglong GUnsignedLongLongInteger::MinValue()
{
	return 0LL;
}

GUnsignedLongLongInteger GUnsignedLongLongInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GUnsignedLongLongInteger();
	}
	return str.ToULongLong();
}

GUnsignedLongLongInteger::GUnsignedLongLongInteger(gulonglong val)
: GNumber<gulonglong>(val)
{

}

GUnsignedLongLongInteger::GUnsignedLongLongInteger(const GUnsignedLongLongInteger &val)
: GNumber<gulonglong>(val)
{

}

GUnsignedLongLongInteger::~GUnsignedLongLongInteger()
{

}

guint GUnsignedLongLongInteger::ClassCode() const
{
	return GUnsignedLongLongInteger::CLASS_CODE;
}