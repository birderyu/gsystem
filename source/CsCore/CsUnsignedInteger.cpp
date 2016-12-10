#include "CsUnsignedInteger.h"

cs_uint CsUnsignedInteger::MaxValue()
{
	return 0xffffffff;
}

cs_uint CsUnsignedInteger::MinValue()
{
	return 0;
}

CsUnsignedInteger CsUnsignedInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsUnsignedInteger();
	}
	return str.ToUInt();
}

CsUnsignedInteger::CsUnsignedInteger(cs_uint val)
: CsNumber<cs_uint>(val)
{

}

CsUnsignedInteger::CsUnsignedInteger(const CsUnsignedInteger &val)
: CsNumber<cs_uint>(val)
{

}

CsUnsignedInteger::~CsUnsignedInteger()
{

}

cs_uint CsUnsignedInteger::ClassCode() const
{
	return CsUnsignedInteger::CLASSCODE;
}