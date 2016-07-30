#ifndef _CSCORE_CSMATH_H_
#define _CSCORE_CSMATH_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsMath
{
public:
	/// 根号2
	static cs_real Cs_Sqrt2;

	/// 圆周率
	static cs_real Cs_PI;

	/// 圆周率除以2
	static cs_real Cs_PI_2;

	/// 圆周率除以4
	static cs_real Cs_PI_4;

	/// 圆周率的倒数
	static cs_real Cs_1_PI;

	/// 2除以圆周率
	static cs_real Cs_2_PI;

	/// 自然常数
	static cs_real Cs_E;
	static cs_real Cs_Log2E;
	static cs_real Cs_Log10E;
	static cs_real Cs_Ln2;
	static cs_real Cs_Ln10;

	/// 取绝对值
	static cs_uint		Abs(cs_int v);
	static cs_double	Abs(cs_double v);
	static cs_decimal	Abs(cs_decimal v);

	static cs_int Ceil(cs_real v);
	static cs_int Floor(cs_real v);
	static cs_real FastSin(cs_real x);

protected:
	CsMath();
	~CsMath();
};

#endif // _CSCORE_CSMATH_H_
