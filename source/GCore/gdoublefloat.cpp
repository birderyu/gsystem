#include "gdoublefloat.h"

gdouble GDoubleFloat::MaxValue()
{
	return 1.7976931348623158e+308;
}

gdouble GDoubleFloat::MinValue()
{
	return 2.2250738585072014e-308;
}

gdouble GDoubleFloat::Epsilon()
{
	return 2.2204460492503131e-016;
}

gsize GDoubleFloat::PrecisionDigit()
{
	return 15;
}

gsize GDoubleFloat::MantissaDigit()
{
	return 53;
}

gint GDoubleFloat::MaxExponent()
{
	return 308;
}

gint GDoubleFloat::MaxBinaryExponent()
{
	return 1024;
}

gint GDoubleFloat::MinExponent()
{
	return -307;
}

gint GDoubleFloat::MinBinaryExponent()
{
	return -1021;
}

gsize GDoubleFloat::ExponentRadix()
{
	return 2;
}

gsize GDoubleFloat::AdditionRounding()
{
	return 1;
}

GDoubleFloat GDoubleFloat::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GDoubleFloat();
	}
	return GDoubleFloat(str.ToDouble());
}

GDoubleFloat::GDoubleFloat(gdouble val)
: GNumber<gdouble>(val)
{

}

GDoubleFloat::GDoubleFloat(const GDoubleFloat &val)
: GNumber<gdouble>(val)
{

}

guint GDoubleFloat::ClassCode() const
{
	return GDoubleFloat::CLASS_CODE;
}

gbool GDoubleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
