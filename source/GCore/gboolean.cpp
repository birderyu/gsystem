#include "gboolean.h"

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

guint GBoolean::ClassCode() const
{
	return GBoolean::CLASS_CODE;
}