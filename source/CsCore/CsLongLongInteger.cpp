#include "CsLongLongInteger.h"

cs_longlong CsLongLongInteger::MaxValue()
{
	return CS_INT64_MAX;
}

cs_longlong CsLongLongInteger::MinValue()
{
	return CS_INT64_MIN;
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
	return CsLongLongInteger::CLASS_CODE;
}