#include "ghash.h"
#include "gmath.h"

namespace gsystem { // gsystem

guint GHashing(gbool val)
{
	if (val)
	{
		return 1;
	}
	return 0;
}

guint GHashing(gchar val)
{
	return static_cast<guint>(val);
}

guint GHashing(gschar val)
{
	return static_cast<guint>(val);
}

guint GHashing(guchar val)
{
	return static_cast<guint>(val);
}

guint GHashing(gwchar val)
{
	return static_cast<guint>(val);
}

guint GHashing(gshort val)
{
	return static_cast<guint>(val);
}

guint GHashing(gushort val)
{
	return static_cast<guint>(val);
}

guint GHashing(gint val)
{
	return static_cast<guint>(val);
}

guint GHashing(guint val)
{
	return val;
}

guint GHashing(glong val)
{
	return static_cast<guint>(val);
}

guint GHashing(gulong val)
{
	return static_cast<guint>(val);
}

guint GHashing(glonglong val)
{
	return static_cast<guint>(val);
}

guint GHashing(gulonglong val)
{
	return static_cast<guint>(val);
}

guint GHashing(gfloat)
{
	return 0;
}

guint GHashing(gdouble val)
{
	gdouble e = 0;
	gdouble tmp = val;
	if (val < 0)
	{
		tmp = -val;
	}
	e = GMath::Ceil(GMath::Log(val));
	return guint((G_INT64_MAX + 1.0) * tmp * GMath::Exp(-e));
}

guint GHashing(gdecimal)
{
	return 0;
}

guint GHashing(gptr)
{
	return 0;
}

} // namespace gsystem
