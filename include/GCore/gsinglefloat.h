#ifndef _CORE_SINGLE_SINGLE_FLOAT_H_
#define _CORE_SINGLE_SINGLE_FLOAT_H_

#include "gpackage.h"

class GAPI GSingleFloat 
	: public GNumber<gfloat>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SINGLE_FLOAT, };

public:
	static gfloat MaxValue();
	static gfloat MinValue();
	static gfloat Epsilon();
	static gsize PrecisionDigit();
	static gsize MantissaDigit(); // 尾数占据的数位
	static gint MaxExponent();
	static gint MaxBinaryExponent();
	static gint MinExponent();
	static gint MinBinaryExponent();
	static gsize ExponentRadix();
	static gsize AdditionRounding();
	static gsize Guard();
	static gsize Normalize();

	static GSingleFloat ValueOf(const GString &);

public:
	GSingleFloat(gfloat val = 0.0F);
	GSingleFloat(const GSingleFloat &);

	guint ClassCode() const;
	gbool IsNaN() const;
};

typedef GSingleFloat GFloat;

#endif // _CORE_SINGLE_SINGLE_FLOAT_H_