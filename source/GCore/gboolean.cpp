#include "gboolean.h"

namespace gsystem { // gsystem

GBoolean GBoolean::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GBoolean();
	}
	if (str.Equals("true", false))
	{
		return GBoolean(true);
	}
	return GBoolean(false);
}

GBoolean::GBoolean(gbool val)
: GPackage<gbool>(val)
{

}

GBoolean::GBoolean(const GBoolean &val)
: GPackage<gbool>(val)
{

}

guint GBoolean::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::Boolean);
}

GString GBoolean::ClassName() const GNOEXCEPT
{
	return GString::ReferenceOf("gsystem::GBoolean");
}

} // namespace gsystem
