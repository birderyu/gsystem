#include "CsByte.h"

CsByte::CsByte(cs_byte val)
: CsPackage<cs_byte>(val)
{

}

CsByte::CsByte(const CsByte &val)
: CsPackage<cs_byte>(val)
{

}

cs_uint CsByte::ClassCode() const
{
	return CsByte::CLASSCODE;
}
