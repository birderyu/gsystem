#include "ghash.h"
#include "gmath.h"

namespace gsystem { // gsystem

guint GHashing(gbool value)
{
	if (value)
	{
		return 1;
	}
	return 0;
}

guint GHashing(gchar value)
{
	return static_cast<guint>(value);
}

guint GHashing(gschar value)
{
	return static_cast<guint>(value);
}

guint GHashing(guchar value)
{
	return static_cast<guint>(value);
}

guint GHashing(gchar16 value)
{
	return static_cast<guint>(value);
}

guint GHashing(gchar32 value)
{
	return static_cast<guint>(value);
}

guint GHashing(gwchar value)
{
	return static_cast<guint>(value);
}

guint GHashing(gshort value)
{
	return static_cast<guint>(value);
}

guint GHashing(gushort value)
{
	return static_cast<guint>(value);
}

guint GHashing(gint value)
{
	return static_cast<guint>(value);
}

guint GHashing(guint value)
{
	return value;
}

guint GHashing(glong value)
{
	return static_cast<guint>(value);
}

guint GHashing(gulong value)
{
	return static_cast<guint>(value);
}

guint GHashing(glonglong value)
{
	return static_cast<guint>(value);
}

guint GHashing(gulonglong value)
{
	return static_cast<guint>(value);
}

guint GHashing(gfloat value)
{
	return GHashing(static_cast<gdouble>(value));
}

guint GHashing(gdouble value)
{
	gdouble e = 0;
	gdouble tmp = value;
	if (value < 0)
	{
		tmp = -value;
	}
	e = GMath::Ceil(GMath::Log(value));
	return guint((G_INT64_MAX + 1.0) * tmp * GMath::Exp(-e));
}

guint GHashing(glongdouble value)
{
	return GHashing(static_cast<gdouble>(value));
}

guint GHashing(gptr value)
{
	return (guint) value;
}

} // namespace gsystem
