#include "CsLongDoubleFloat.h"

cs_longdouble CsLongDoubleFloat::MaxValue()
{
	return 1.7976931348623158e+308;
}

cs_longdouble CsLongDoubleFloat::MinValue()
{
	return 2.2250738585072014e-308;
}

cs_longdouble CsLongDoubleFloat::Epsilon()
{
	return 2.2204460492503131e-016;
}

cs_size_t CsLongDoubleFloat::PrecisionDigit()
{
	return 15;
}

cs_size_t CsLongDoubleFloat::MantissaDigit()
{
	return 53;
}

cs_int CsLongDoubleFloat::MaxExponent()
{
	return 308;
}

cs_int CsLongDoubleFloat::MaxBinaryExponent()
{
	return 1024;
}

cs_int CsLongDoubleFloat::MinExponent()
{
	return -307;
}

cs_int CsLongDoubleFloat::MinBinaryExponent()
{
	return -1021;
}

cs_size_t CsLongDoubleFloat::ExponentRadix()
{
	return 2;
}

cs_size_t CsLongDoubleFloat::AdditionRounding()
{
	return 1;
}

CsLongDoubleFloat CsLongDoubleFloat::ValueOf(const CsString &str)
{
	if (str.IsEmpty())
	{
		return CsLongDoubleFloat();
	}
	return CsLongDoubleFloat(str.ToDecimal());
}

CsLongDoubleFloat::CsLongDoubleFloat(cs_longdouble val)
: CsNumber<cs_longdouble>(val)
{

}

CsLongDoubleFloat::CsLongDoubleFloat(const CsLongDoubleFloat &val)
: CsNumber<cs_longdouble>(val)
{

}

cs_uint CsLongDoubleFloat::ClassCode() const
{
	return CsLongDoubleFloat::CLASSCODE;
}

cs_bool CsLongDoubleFloat::IsNaN() const
{
	return m_nValue != m_nValue;
}
