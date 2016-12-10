#include "CsSmallInteger.h"

cs_small CsSmallInteger::MaxValue()
{
	return 127;
}

cs_small CsSmallInteger::MinValue()
{
	return -128;
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
	return CsSmallInteger::CLASSCODE;
}