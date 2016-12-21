#include "CsString.h"

const CsObject *CsString::Boxing() const
{
	return this;
}

cs_uint CsString::ClassCode() const
{
	return CsString::CLASS_CODE;
}

CsString CsString::ToString() const
{
	return *this;
}