#include "glongdoublefloat.h"

glongdouble GLongDoubleFloat::MaxValue()
{
	return 1.7976931348623158e+308;
}

glongdouble GLongDoubleFloat::MinValue()
{
	return 2.2250738585072014e-308;
}

glongdouble GLongDoubleFloat::Epsilon()
{
	return 2.2204460492503131e-016;
}

gsize GLongDoubleFloat::PrecisionDigit()
{
	return 15;
}

gsize GLongDoubleFloat::MantissaDigit()
{
	return 53;
}

gint GLongDoubleFloat::MaxExponent()
{
	return 308;
}

gint GLongDoubleFloat::MaxBinaryExponent()
{
	return 1024;
}

gint GLongDoubleFloat::MinExponent()
{
	return -307;
}

gint GLongDoubleFloat::MinBinaryExponent()
{
	return -1021;
}

gsize GLongDoubleFloat::ExponentRadix()
{
	return 2;
}

gsize GLongDoubleFloat::AdditionRounding()
{
	return 1;
}

GLongDoubleFloat GLongDoubleFloat::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GLongDoubleFloat();
	}
	return GLongDoubleFloat(str.ToLongDouble());
}

GLongDoubleFloat::GLongDoubleFloat(glongdouble val)
: GNumber<glongdouble>(val)
{

}

GLongDoubleFloat::GLongDoubleFloat(const GLongDoubleFloat &val)
: GNumber<glongdouble>(val)
{

}

guint GLongDoubleFloat::ClassCode() const
{
	return GLongDoubleFloat::CLASS_CODE;
}

gbool GLongDoubleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
