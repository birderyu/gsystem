// ±‰ªªæÿ’Û
#ifndef _CORE_MATRIX_H_
#define _CORE_MATRIX_H_

#include "CsObject.h"

/*
// ©∞a c e©¥ ©∞x©¥
// ©¶b d f©¶ ©¶y©¶ = [ax+cy+e bx+dy+f 1]
// ©∏0 0 1©º ©∏1©º
class CS_API CsMatrix
	: public CsObject
{
public:
	CsMatrix() : m_a(1), m_b(0), m_c(0), m_d(1), m_e(0), m_f(0) {}
	CsMatrix(cs_double a, cs_double b, cs_double c, cs_double d, cs_double e, cs_double f) :
		m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f) {}
	virtual ~CsMatrix() {}
	virtual CsMatrix Multiply(const CsMatrix &) const;
	virtual CsMatrix Inverse() const;
	virtual CsMatrix Translate(cs_double x, cs_double y) const;
	virtual CsMatrix Scale(cs_double scaleFactor) const;
	virtual CsMatrix ScaleNonUniform(cs_double scaleFactorX, cs_double scaleFactorY) const;
	virtual CsMatrix Rotate(cs_double angle) const;
	virtual CsMatrix RotateFromVector(cs_double x, cs_double y) const;
	virtual CsMatrix FlipX() const;
	virtual CsMatrix FlipY() const;
	virtual CsMatrix SkewX(cs_double angle) const;
	virtual CsMatrix SkewY(cs_double angle) const;

private:
	cs_double m_a;
	cs_double m_b;
	cs_double m_c;
	cs_double m_d;
	cs_double m_e;
	cs_double m_f;
};
*/
#endif // _CORE_MATRIX_H_