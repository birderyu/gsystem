#include "gsignedcharacter.h"

namespace gsystem { // gsystem

GSignedCharacter::GSignedCharacter(gschar val)
: GPackage<gschar>(val)
{

}

GSignedCharacter::GSignedCharacter(const GSignedCharacter &val)
: GPackage<gschar>(val)
{

}

GSignedCharacter::~GSignedCharacter()
{

}

guint GSignedCharacter::ClassCode() const
{
	return static_cast<guint>(GClassCode::SignedCharacter);
}

} // namespace gsystem
