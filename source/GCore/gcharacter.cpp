#include "gcharacter.h"

namespace gsystem { // gsystem

GCharacter::GCharacter(gchar val)
: GPackage<gchar>(val)
{

}
GCharacter::GCharacter(const GCharacter &val)
: GPackage<gchar>(val)
{

}

guint GCharacter::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::Character);
}

} // namespace gsystem
