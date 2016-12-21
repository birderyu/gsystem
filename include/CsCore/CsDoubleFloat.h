#ifndef _CORE_DOUBLE_FLOAT_H_
#define _CORE_DOUBLE_FLOAT_H_

#include "CsPackage.h"

class CS_API CsDoubleFloat 
	: public CsNumber<cs_double>
{
public:
	enum 
	{ 
		CLASS_CODE = CLASS_CODE_DOUBLE_FLOAT, 
	};

public:
	static cs_double MaxValue();
	static cs_double MinValue();
	static cs_double Epsilon();
	static cs_size_t PrecisionDigit();
	static cs_size_t MantissaDigit(); // 尾数占据的数位
	static cs_int MaxExponent();
	static cs_int MaxBinaryExponent();
	static cs_int MinExponent();
	static cs_int MinBinaryExponent();
	static cs_size_t ExponentRadix();
	static cs_size_t AdditionRounding();

	static CsDoubleFloat ValueOf(const CsString &);

public:
	CsDoubleFloat(cs_double val = 0.0);
	CsDoubleFloat(const CsDoubleFloat &);

	cs_uint ClassCode() const;
	cs_bool IsNaN() const;
};

typedef CsDoubleFloat CsDouble;

#endif // _CORE_DOUBLE_FLOAT_H_