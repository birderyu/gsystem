#include "CsUnsignedSmallInteger.h"

cs_usmall CsUnsignedSmallInteger::MaxValue()
{
	return CS_UINT8_MAX;
}

cs_usmall CsUnsignedSmallInteger::MinValue()
{
	return 0;
}

CsUnsignedSmallInteger CsUnsignedSmallInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsUnsignedSmallInteger();
	}
	return str.ToUSmall();
}

CsUnsignedSmallInteger::CsUnsignedSmallInteger(cs_usmall val)
: CsNumber<cs_usmall>(val)
{

}

CsUnsignedSmallInteger::CsUnsignedSmallInteger(const CsUnsignedSmallInteger &val)
: CsNumber<cs_usmall>(val)
{

}

CsUnsignedSmallInteger::~CsUnsignedSmallInteger()
{

}

cs_uint CsUnsignedSmallInteger::ClassCode() const
{
	return CsUnsignedSmallInteger::CLASS_CODE;
}