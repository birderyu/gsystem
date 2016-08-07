#ifndef _CSCORE_CSMATH_H_
#define _CSCORE_CSMATH_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsMath
{
public:
	/// 根号2
	static cs_double Cs_Sqrt2;

	/// 圆周率
	static cs_double Cs_PI;

	/// 圆周率除以2
	static cs_double Cs_PI_2;

	/// 圆周率除以4
	static cs_double Cs_PI_4;

	/// 圆周率的倒数
	static cs_double Cs_1_PI;

	/// 2除以圆周率
	static cs_double Cs_2_PI;

	/// 自然常数
	static cs_double Cs_E;
	static cs_double Cs_Log2E;
	static cs_double Cs_Log10E;
	static cs_double Cs_Ln2;
	static cs_double Cs_Ln10;

	/// 数字比较
	static cs_bool Equals(cs_float v1, cs_float v2, cs_float precision);
	static cs_bool Equals(cs_double v1, cs_double v2, cs_double precision);

	/// 取绝对值
	static cs_uint Abs(cs_int v);
	static cs_uint Abs(cs_float v);
	static cs_double Abs(cs_double v);
	static cs_decimal Abs(cs_decimal v);

	static cs_int Ceil(cs_float v);
	static cs_int Ceil(cs_double v);
	static cs_int Ceil(cs_decimal v);

	static cs_int Floor(cs_double v);

	/// 三角函数
	static cs_double FastSin(cs_double x);

protected:
	CsMath();
	~CsMath();
};

#endif // _CSCORE_CSMATH_H_
