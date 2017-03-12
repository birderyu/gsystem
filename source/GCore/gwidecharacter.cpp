#include "gwidecharacter.h"

namespace gnova { // gnova

GWideCharacter::GWideCharacter(gwchar val)
: GPackage<gwchar>(val)
{

}
GWideCharacter::GWideCharacter(const GWideCharacter &val)
: GPackage<gwchar>(val)
{

}

guint GWideCharacter::ClassCode() const
{
	return GWideCharacter::CLASS_CODE;
}

}