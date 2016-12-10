#include "CsShortInteger.h"

cs_short CsShortInteger::MaxValue()
{
	return 32767;
}

cs_short CsShortInteger::MinValue()
{
	return -32768;
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
	return CsShortInteger::CLASSCODE;
}