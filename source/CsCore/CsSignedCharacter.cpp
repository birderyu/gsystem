#include "CsSignedCharacter.h"

CsSignedCharacter::CsSignedCharacter(cs_schar val)
: CsPackage<cs_schar>(val)
{

}

CsSignedCharacter::CsSignedCharacter(const CsSignedCharacter &val)
: CsPackage<cs_schar>(val)
{

}

CsSignedCharacter::~CsSignedCharacter()
{

}

cs_uint CsSignedCharacter::ClassCode() const
{
	return CsSignedCharacter::CLASSCODE;
}