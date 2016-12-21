#include "CsShortInteger.h"

cs_short CsShortInteger::MaxValue()
{
	return CS_INT16_MAX;
}

cs_short CsShortInteger::MinValue()
{
	return CS_INT16_MIN;
}

CsShortInteger CsShortInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsShortInteger();
	}
	return str.ToShort();
}

CsShortInteger::CsShortInteger(cs_short val)
: CsNumber<cs_short>(val)
{

}

CsShortInteger::CsShortInteger(const CsShortInteger &val)
: CsNumber<cs_short>(val)
{

}

CsShortInteger::~CsShortInteger()
{

}

cs_uint CsShortInteger::ClassCode() const
{
	return CsShortInteger::CLASS_CODE;
}