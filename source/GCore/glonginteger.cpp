#include "glonginteger.h"

namespace gsystem { // gsystem

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
	return static_cast<guint>(GClassCode::LongInteger);
}

} // namespace gsystem
