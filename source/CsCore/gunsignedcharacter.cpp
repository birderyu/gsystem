#include "gunsignedcharacter.h"

CsUnsignedCharacter::CsUnsignedCharacter(guchar val)
: GNumber<guchar>(val)
{

}

CsUnsignedCharacter::CsUnsignedCharacter(const CsUnsignedCharacter &val)
: GNumber<guchar>(val)
{

}

guint CsUnsignedCharacter::ClassCode() const
{
	return CsUnsignedCharacter::CLASS_CODE;
}
