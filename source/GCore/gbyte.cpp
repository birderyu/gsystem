#include "gbyte.h"

namespace gsystem { // gsystem

GByte::GByte(gbyte val)
: GPackage<gbyte>(val)
{

}

GByte::GByte(const GByte &val)
: GPackage<gbyte>(val)
{

}

guint GByte::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::Byte);
}

} // namespace gsystem
