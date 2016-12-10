#include "CsLongLongInteger.h"

cs_longlong CsLongLongInteger::MaxValue()
{
	return 9223372036854775807LL;
}

cs_longlong CsLongLongInteger::MinValue()
{
	return -9223372036854775807LL - 1;
}

CsLongLongInteger CsLongLongInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsLongLongInteger();
	}
	return str.ToLongLong();
}

CsLongLongInteger::CsLongLongInteger(cs_longlong val)
: CsNumber<cs_longlong>(val)
{

}

CsLongLongInteger::CsLongLongInteger(const CsLongLongInteger &val)
: CsNumber<cs_longlong>(val)
{

}

CsLongLongInteger::~CsLongLongInteger()
{

}

cs_uint CsLongLongInteger::ClassCode() const
{
	return CsLongLongInteger::CLASSCODE;
}