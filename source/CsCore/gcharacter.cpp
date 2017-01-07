#include "gcharacter.h"

GCharacter::GCharacter(gchar val)
: GPackage<gchar>(val)
{

}
GCharacter::GCharacter(const GCharacter &val)
: GPackage<gchar>(val)
{

}

guint GCharacter::ClassCode() const
{
	return GCharacter::CLASS_CODE;
}