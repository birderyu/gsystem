#ifndef _CORE_LONG_DOUBLE_FLOAT_H_
#define _CORE_LONG_DOUBLE_FLOAT_H_

#include "gpackage.h"

G_BEGIN_NAMESPACE

class GAPI GLongDoubleFloat 
	: public GNumber<glongdouble>
{
public:
	enum { CLASS_CODE = CLASS_CODE_LONG_DOUBLE_FLOAT, };

public:
	static glongdouble MaxValue();
	static glongdouble MinValue();
	static glongdouble Epsilon();
	static gsize PrecisionDigit();
	static gsize MantissaDigit(); // 尾数占据的数位
	static gint MaxExponent();
	static gint MaxBinaryExponent();
	static gint MinExponent();
	static gint MinBinaryExponent();
	static gsize ExponentRadix();
	static gsize AdditionRounding();

	static GLongDoubleFloat ValueOf(const GString &);

public:
	GLongDoubleFloat(glongdouble val = 0.0);
	GLongDoubleFloat(const GLongDoubleFloat &);

	guint ClassCode() const;
	gbool IsNaN() const;
};

typedef GLongDoubleFloat GLongDouble;
typedef GLongDoubleFloat GDecimal;

G_END_NAMESPACE

#endif // _CORE_LONG_DOUBLE_FLOAT_H_