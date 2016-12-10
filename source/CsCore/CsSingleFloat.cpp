#include "CsSingleFloat.h"

cs_float CsSingleFloat::MaxValue()
{
	return 3.402823466e+38F;
}

cs_float CsSingleFloat::MinValue()
{
	return 1.175494351e-38F;
}

cs_float CsSingleFloat::Epsilon()
{
	return 1.192092896e-07F;
}

cs_size_t CsSingleFloat::PrecisionDigit()
{
	return 6;
}

cs_size_t CsSingleFloat::MantissaDigit()
{
	return 24;
}

cs_int CsSingleFloat::MaxExponent()
{
	return 38;
}

cs_int CsSingleFloat::MaxBinaryExponent()
{
	return 128;
}

cs_int CsSingleFloat::MinExponent()
{
	return -37;
}

cs_int CsSingleFloat::MinBinaryExponent()
{
	return -125;
}

cs_size_t CsSingleFloat::ExponentRadix()
{
	return 2;
}

cs_size_t CsSingleFloat::AdditionRounding()
{
	return 1;
}

cs_size_t CsSingleFloat::Guard()
{
	return 0;
}

cs_size_t CsSingleFloat::Normalize()
{
	return 0;
}

CsSingleFloat CsSingleFloat::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsSingleFloat();
	}
	return CsSingleFloat(str.ToFloat());
}

CsSingleFloat::CsSingleFloat(cs_float val)
: CsNumber<cs_float>(val)
{

}

CsSingleFloat::CsSingleFloat(const CsSingleFloat &val)
: CsNumber<cs_float>(val)
{

}

cs_uint CsSingleFloat::ClassCode() const
{
	return CsSingleFloat::CLASSCODE;
}

cs_bool CsSingleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
