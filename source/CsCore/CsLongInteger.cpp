#include "CsLongInteger.h"

cs_long CsLongInteger::MaxValue()
{
	return 2147483647L;
}

cs_long CsLongInteger::MinValue()
{
	return -2147483647L - 1;
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
	return CsLongInteger::CLASSCODE;
}