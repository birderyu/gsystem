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

guint GByte::ClassCode() const
{
	return GByte::CLASS_CODE;
}

} // namespace gsystem
