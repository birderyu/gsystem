#include "CsDoubleFloat.h"

cs_double CsDoubleFloat::MaxValue()
{
	return 1.7976931348623158e+308;
}

cs_double CsDoubleFloat::MinValue()
{
	return 2.2250738585072014e-308;
}

cs_double CsDoubleFloat::Epsilon()
{
	return 2.2204460492503131e-016;
}

cs_size_t CsDoubleFloat::PrecisionDigit()
{
	return 15;
}

cs_size_t CsDoubleFloat::MantissaDigit()
{
	return 53;
}

cs_int CsDoubleFloat::MaxExponent()
{
	return 308;
}

cs_int CsDoubleFloat::MaxBinaryExponent()
{
	return 1024;
}

cs_int CsDoubleFloat::MinExponent()
{
	return -307;
}

cs_int CsDoubleFloat::MinBinaryExponent()
{
	return -1021;
}

cs_size_t CsDoubleFloat::ExponentRadix()
{
	return 2;
}

cs_size_t CsDoubleFloat::AdditionRounding()
{
	return 1;
}

CsDoubleFloat CsDoubleFloat::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsDoubleFloat();
	}
	return CsDoubleFloat(str.ToDouble());
}

CsDoubleFloat::CsDoubleFloat(cs_double val)
: CsNumber<cs_double>(val)
{

}

CsDoubleFloat::CsDoubleFloat(const CsDoubleFloat &val)
: CsNumber<cs_double>(val)
{

}

cs_uint CsDoubleFloat::ClassCode() const
{
	return CsDoubleFloat::CLASSCODE;
}

cs_bool CsDoubleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
