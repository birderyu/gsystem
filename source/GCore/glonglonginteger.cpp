#include "glonglonginteger.h"

glonglong GLongLongInteger::MaxValue()
{
	return G_INT64_MAX;
}

glonglong GLongLongInteger::MinValue()
{
	return G_INT64_MIN;
}

GLongLongInteger GLongLongInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GLongLongInteger();
	}
	return str.ToLongLong();
}

GLongLongInteger::GLongLongInteger(glonglong val)
: GNumber<glonglong>(val)
{

}

GLongLongInteger::GLongLongInteger(const GLongLongInteger &val)
: GNumber<glonglong>(val)
{

}

GLongLongInteger::~GLongLongInteger()
{

}

guint GLongLongInteger::ClassCode() const
{
	return GLongLongInteger::CLASS_CODE;
}