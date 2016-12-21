#include "CsUnsignedLongLongInteger.h"

cs_ulonglong CsUnsignedLongLongInteger::MaxValue()
{
	return CS_UINT64_MAX;
}

cs_ulonglong CsUnsignedLongLongInteger::MinValue()
{
	return 0LL;
}

CsUnsignedLongLongInteger CsUnsignedLongLongInteger::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsUnsignedLongLongInteger();
	}
	return str.ToULongLong();
}

CsUnsignedLongLongInteger::CsUnsignedLongLongInteger(cs_ulonglong val)
: CsNumber<cs_ulonglong>(val)
{

}

CsUnsignedLongLongInteger::CsUnsignedLongLongInteger(const CsUnsignedLongLongInteger &val)
: CsNumber<cs_ulonglong>(val)
{

}

CsUnsignedLongLongInteger::~CsUnsignedLongLongInteger()
{

}

cs_uint CsUnsignedLongLongInteger::ClassCode() const
{
	return CsUnsignedLongLongInteger::CLASS_CODE;
}