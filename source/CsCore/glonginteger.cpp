#include "glonginteger.h"

gint GLongInteger::MaxValue()
{
	return G_INT32L_MAX;
}

gint GLongInteger::MinValue()
{
	return G_INT32L_MIN;
}

GLongInteger GLongInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GLongInteger();
	}
	return str.ToLong();
}

GLongInteger::GLongInteger(glong val)
: GNumber<glong>(val)
{

}

GLongInteger::GLongInteger(const GLongInteger &val)
: GNumber<glong>(val)
{

}

guint GLongInteger::ClassCode() const
{
	return GLongInteger::CLASS_CODE;
}