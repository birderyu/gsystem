#include "gstring.h"

const GObject *GString::Boxing() const
{
	return this;
}

guint GString::ClassCode() const
{
	return GString::CLASS_CODE;
}

GString GString::ToString() const
{
	return *this;
}