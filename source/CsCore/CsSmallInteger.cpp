#include "CsSmallInteger.h"

cs_small CsSmallInteger::MaxValue()
{
	return CS_INT8_MAX;
}

cs_small CsSmallInteger::MinValue()
{
	return CS_INT8_MIN;
}

CsSmallInteger CsSmallInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsSmallInteger();
	}
	return str.ToSmall();
}

CsSmallInteger::CsSmallInteger(cs_small val)
: CsNumber<cs_small>(val)
{

}

CsSmallInteger::CsSmallInteger(const CsSmallInteger &val)
: CsNumber<cs_small>(val)
{

}

cs_uint CsSmallInteger::ClassCode() const
{
	return CsSmallInteger::CLASS_CODE;
}