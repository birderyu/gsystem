#include "CsLongInteger.h"

cs_int CsLongInteger::MaxValue()
{
	return CS_INT32L_MAX;
}

cs_int CsLongInteger::MinValue()
{
	return CS_INT32L_MIN;
}

CsLongInteger CsLongInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsLongInteger();
	}
	return str.ToLong();
}

CsLongInteger::CsLongInteger(cs_long val)
: CsNumber<cs_long>(val)
{

}

CsLongInteger::CsLongInteger(const CsLongInteger &val)
: CsNumber<cs_long>(val)
{

}

cs_uint CsLongInteger::ClassCode() const
{
	return CsLongInteger::CLASS_CODE;
}