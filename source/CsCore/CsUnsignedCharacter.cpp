#include "CsUnsignedCharacter.h"

CsUnsignedCharacter::CsUnsignedCharacter(cs_uchar val)
: CsNumber<cs_uchar>(val)
{

}

CsUnsignedCharacter::CsUnsignedCharacter(const CsUnsignedCharacter &val)
: CsNumber<cs_uchar>(val)
{

}

cs_uint CsUnsignedCharacter::ClassCode() const
{
	return CsUnsignedCharacter::CLASSCODE;
}
