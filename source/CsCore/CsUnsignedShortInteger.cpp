#include "CsUnsignedShortInteger.h"

cs_ushort CsUnsignedShortInteger::MaxValue()
{
	return CS_UINT16_MAX;
}

cs_ushort CsUnsignedShortInteger::MinValue()
{
	return 0;
}

CsUnsignedShortInteger CsUnsignedShortInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsUnsignedShortInteger();
	}
	return str.ToUShort();
}

CsUnsignedShortInteger::CsUnsignedShortInteger(cs_ushort val)
: CsNumber<cs_ushort>(val)
{

}

CsUnsignedShortInteger::CsUnsignedShortInteger(const CsUnsignedShortInteger &val)
: CsNumber<cs_ushort>(val)
{

}

CsUnsignedShortInteger::~CsUnsignedShortInteger()
{

}

cs_uint CsUnsignedShortInteger::ClassCode() const
{
	return CsUnsignedShortInteger::CLASS_CODE;
}