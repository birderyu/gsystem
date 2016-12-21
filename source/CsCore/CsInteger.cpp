#include "CsInteger.h"

cs_int CsInteger::MaxValue()
{
	return CS_INT32_MAX;
}

cs_int CsInteger::MinValue()
{
	return CS_INT32_MIN;
}

CsInteger CsInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsInteger();
	}
	return str.ToInt();
}

CsInteger::CsInteger(cs_int val)
: CsNumber<cs_int>(val)
{

}

CsInteger::CsInteger(const CsInteger &val)
: CsNumber<cs_int>(val)
{

}

cs_uint CsInteger::ClassCode() const
{
	return CsInteger::CLASS_CODE;
}