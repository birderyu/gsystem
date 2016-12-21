#ifndef _CORE_LONG_DOUBLE_FLOAT_H_
#define _CORE_LONG_DOUBLE_FLOAT_H_

#include "CsPackage.h"

class CS_API CsLongDoubleFloat 
	: public CsNumber<cs_longdouble>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_DOUBLE_FLOAT, };

public:
	static cs_longdouble MaxValue();
	static cs_longdouble MinValue();
	static cs_longdouble Epsilon();
	static cs_size_t PrecisionDigit();
	static cs_size_t MantissaDigit(); // 尾数占据的数位
	static cs_int MaxExponent();
	static cs_int MaxBinaryExponent();
	static cs_int MinExponent();
	static cs_int MinBinaryExponent();
	static cs_size_t ExponentRadix();
	static cs_size_t AdditionRounding();

	static CsLongDoubleFloat ValueOf(const CsString &);

public:
	CsLongDoubleFloat(cs_longdouble val = 0.0);
	CsLongDoubleFloat(const CsLongDoubleFloat &);

	cs_uint ClassCode() const;
	cs_bool IsNaN() const;
};

typedef CsLongDoubleFloat CsLongDouble;
typedef CsLongDoubleFloat CsDecimal;

#endif // _CORE_LONG_DOUBLE_FLOAT_H_