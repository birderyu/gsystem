#include "gunsignedcharacter.h"

GUnsignedCharacter::GUnsignedCharacter(guchar val)
: GNumber<guchar>(val)
{

}

GUnsignedCharacter::GUnsignedCharacter(const GUnsignedCharacter &val)
: GNumber<guchar>(val)
{

}

guint GUnsignedCharacter::ClassCode() const
{
	return GUnsignedCharacter::CLASS_CODE;
}
