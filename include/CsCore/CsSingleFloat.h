#ifndef _CORE_SINGLE_SINGLE_FLOAT_H_
#define _CORE_SINGLE_SINGLE_FLOAT_H_

#include "CsPackage.h"

class CS_API CsSingleFloat 
	: public CsNumber<cs_float>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SINGLE_FLOAT, };

public:
	static cs_float MaxValue();
	static cs_float MinValue();
	static cs_float Epsilon();
	static cs_size_t PrecisionDigit();
	static cs_size_t MantissaDigit(); // 尾数占据的数位
	static cs_int MaxExponent();
	static cs_int MaxBinaryExponent();
	static cs_int MinExponent();
	static cs_int MinBinaryExponent();
	static cs_size_t ExponentRadix();
	static cs_size_t AdditionRounding();
	static cs_size_t Guard();
	static cs_size_t Normalize();

	static CsSingleFloat ValueOf(const CsString &);

public:
	CsSingleFloat(cs_float val = 0.0F);
	CsSingleFloat(const CsSingleFloat &);

	cs_uint ClassCode() const;
	cs_bool IsNaN() const;
};

typedef CsSingleFloat CsFloat;

#endif // _CORE_SINGLE_SINGLE_FLOAT_H_