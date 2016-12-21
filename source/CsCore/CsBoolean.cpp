#include "CsBoolean.h"

CsBoolean CsBoolean::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsBoolean();
	}
	if (str.Equals("true", false))
	{
		return CsBoolean(true);
	}
	return CsBoolean(false);
}

CsBoolean::CsBoolean(cs_bool val)
: CsPackage<cs_bool>(val)
{

}

CsBoolean::CsBoolean(const CsBoolean &val)
: CsPackage<cs_bool>(val)
{

}

cs_uint CsBoolean::ClassCode() const
{
	return CsBoolean::CLASS_CODE;
}