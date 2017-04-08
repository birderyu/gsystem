#include "gunsignedcharacter.h"

namespace gsystem { // gsystem

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
	return static_cast<guint>(GClassCode::UnsignedCharacter);
}

} // namespace gsystem
