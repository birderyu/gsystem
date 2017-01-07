#ifndef _CORE_MATH_H_
#define _CORE_MATH_H_

#include "gglobal.h"

class GAPI GMath
{
public:
	/// 根号2
	static gdouble Cs_Sqrt2;

	/// 圆周率
	static gdouble Cs_PI;

	/// 圆周率除以2
	static gdouble Cs_PI_2;

	/// 圆周率除以4
	static gdouble Cs_PI_4;

	/// 圆周率的倒数
	static gdouble Cs_1_PI;

	/// 2除以圆周率
	static gdouble Cs_2_PI;

	/// 自然常数
	static gdouble Cs_E;
	static gdouble Cs_Log2E;
	static gdouble Cs_Log10E;
	static gdouble Cs_Ln2;
	static gdouble Cs_Ln10;

	template<typename ValueT>
	static ValueT Max(const ValueT &v1, const ValueT &v2);

	template<typename ValueT>
	static ValueT Min(const ValueT &v1, const ValueT &v2);

	/// 数字比较
	static gbool Equals(gfloat v1, gfloat v2, gfloat precision);
	static gbool Equals(gdouble v1, gdouble v2, gdouble precision);

	/// 取绝对值
	static guint Abs(gint v);
	static gfloat Abs(gfloat v);
	static gdouble Abs(gdouble v);
	static gdecimal Abs(gdecimal v);

	static gint Ceil(gfloat v);
	static gint Ceil(gdouble v);
	static gint Ceil(gdecimal v);

	static gfloat Log(gfloat);
	static gdouble Log(gdouble);
	static gdecimal Log(gdecimal);

	static gfloat Exp(gfloat);
	static gdouble Exp(gdouble);
	static gdecimal Exp(gdecimal);

	static gint Floor(gdouble v);

	/// 三角函数
	static gdouble FastSin(gdouble x);

	// 平方根
	static gfloat Sqrt(gfloat v);
	static gdouble Sqrt(gdouble v);
#ifdef CS_HAS_DECIMAL
	static gdecimal Sqrt(gdecimal v);
#endif // CS_HAS_DECIMAL

private:
	GMath() {}
	GMath(const GMath &) {}
	~GMath() {}
};

#include "gmath.inl"

#endif // _CORE_MATH_H_
