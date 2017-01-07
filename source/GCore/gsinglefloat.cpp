#include "gsinglefloat.h"

gfloat GSingleFloat::MaxValue()
{
	return 3.402823466e+38F;
}

gfloat GSingleFloat::MinValue()
{
	return 1.175494351e-38F;
}

gfloat GSingleFloat::Epsilon()
{
	return 1.192092896e-07F;
}

gsize GSingleFloat::PrecisionDigit()
{
	return 6;
}

gsize GSingleFloat::MantissaDigit()
{
	return 24;
}

gint GSingleFloat::MaxExponent()
{
	return 38;
}

gint GSingleFloat::MaxBinaryExponent()
{
	return 128;
}

gint GSingleFloat::MinExponent()
{
	return -37;
}

gint GSingleFloat::MinBinaryExponent()
{
	return -125;
}

gsize GSingleFloat::ExponentRadix()
{
	return 2;
}

gsize GSingleFloat::AdditionRounding()
{
	return 1;
}

gsize GSingleFloat::Guard()
{
	return 0;
}

gsize GSingleFloat::Normalize()
{
	return 0;
}

GSingleFloat GSingleFloat::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GSingleFloat();
	}
	return GSingleFloat(str.ToFloat());
}

GSingleFloat::GSingleFloat(gfloat val)
: GNumber<gfloat>(val)
{

}

GSingleFloat::GSingleFloat(const GSingleFloat &val)
: GNumber<gfloat>(val)
{

}

guint GSingleFloat::ClassCode() const
{
	return GSingleFloat::CLASS_CODE;
}

gbool GSingleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
