#include "CsCharacter.h"

CsCharacter::CsCharacter(cs_char val)
: CsPackage<cs_char>(val)
{

}
CsCharacter::CsCharacter(const CsCharacter &val)
: CsPackage<cs_char>(val)
{

}

cs_uint CsCharacter::ClassCode() const
{
	return CsCharacter::CLASS_CODE;
}