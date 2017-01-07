#include "ghash.h"
#include "gmath.h"

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

guint GHashing(gwchar)
{
	return 0;
}

guint GHashing(gshort)
{
	return 0;
}

guint GHashing(gushort)
{
	return 0;
}

guint GHashing(gint val)
{
	return val % G_INT32_MAX;
}

guint GHashing(guint)
{
	return 0;
}

guint GHashing(glong)
{
	return 0;
}

guint GHashing(gulong)
{
	return 0;
}

guint GHashing(glonglong)
{
	return 0;
}

guint GHashing(gulonglong)
{
	return 0;
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

guint GHashing(gpointer)
{
	return 0;
}