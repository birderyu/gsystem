#include "CsWideCharacter.h"

CsWideCharacter::CsWideCharacter(cs_wchar val)
: CsPackage<cs_wchar>(val)
{

}
CsWideCharacter::CsWideCharacter(const CsWideCharacter &val)
: CsPackage<cs_wchar>(val)
{

}

cs_uint CsWideCharacter::ClassCode() const
{
	return CsWideCharacter::CLASSCODE;
}