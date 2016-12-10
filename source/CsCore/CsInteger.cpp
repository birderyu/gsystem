#include "CsInteger.h"

cs_int CsInteger::MaxValue()
{
	return 2147483647;
}

cs_int CsInteger::MinValue()
{
	return -2147483647 - 1;
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
	return CsInteger::CLASSCODE;
}