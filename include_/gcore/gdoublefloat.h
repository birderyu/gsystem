#ifndef _CORE_DOUBLE_FLOAT_H_
#define _CORE_DOUBLE_FLOAT_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GDoubleFloat 
	: public GNumber<gdouble>
{
public:
	static gdouble MaxValue();
	static gdouble MinValue();
	static gdouble Epsilon();
	static gsize PrecisionDigit();
	static gsize MantissaDigit(); // 尾数占据的数位
	static gint MaxExponent();
	static gint MaxBinaryExponent();
	static gint MinExponent();
	static gint MinBinaryExponent();
	static gsize ExponentRadix();
	static gsize AdditionRounding();

	static GDoubleFloat ValueOf(const GString &);

public:
	GDoubleFloat(gdouble val = 0.0);
	GDoubleFloat(const GDoubleFloat &);

	guint ClassCode() const GNOEXCEPT;
	gbool IsNaN() const;
};

typedef GDoubleFloat GDouble;

} // namespace gsystem

#endif // _CORE_DOUBLE_FLOAT_H_