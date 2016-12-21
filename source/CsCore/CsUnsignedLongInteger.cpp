#include "CsUnsignedLongInteger.h"

cs_ulong CsUnsignedLongInteger::MaxValue()
{
	return CS_UINT32L_MAX;
}

cs_ulong CsUnsignedLongInteger::MinValue()
{
	return 0L;
}

CsUnsignedLongInteger CsUnsignedLongInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsUnsignedLongInteger();
	}
	return str.ToULong();
}

CsUnsignedLongInteger::CsUnsignedLongInteger(cs_ulong val)
: CsNumber<cs_ulong>(val)
{

}

CsUnsignedLongInteger::CsUnsignedLongInteger(const CsUnsignedLongInteger &val)
: CsNumber<cs_ulong>(val)
{

}

cs_uint CsUnsignedLongInteger::ClassCode() const
{
	return CsUnsignedLongInteger::CLASS_CODE;
}