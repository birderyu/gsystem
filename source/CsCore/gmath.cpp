#include "gmath.h"
#include <cmath>

#define CS_SINE_TABLE_SIZE 256
extern const gdouble cs_sine_table[CS_SINE_TABLE_SIZE] = { 0 };

gdouble GMath::Cs_Sqrt2	= 1.41421356237309504880;
gdouble GMath::Cs_PI		= 3.14159265358979323846;
gdouble GMath::Cs_PI_2	= 1.57079632679489661923;
gdouble GMath::Cs_PI_4	= 0.78539816339744830962;
gdouble GMath::Cs_1_PI	= 0.31830988618379067154;
gdouble GMath::Cs_2_PI	= 0.63661977236758134308;
gdouble GMath::Cs_E		= 2.7182818284590452354;
gdouble GMath::Cs_Log2E	= 1.4426950408889634074;
gdouble GMath::Cs_Log10E	= 0.43429448190325182765;
gdouble GMath::Cs_Ln2		= 0.69314718055994530942;
gdouble GMath::Cs_Ln10	= 2.30258509299404568402;

guint GMath::Abs(gint v)
{
	using std::abs;
	return abs(v);
}

gfloat GMath::Abs(gfloat v)
{
	using std::abs;
	return abs(v);
}

gdouble GMath::Abs(gdouble v)
{
	using std::abs;
	return abs(v);
}

gdecimal GMath::Abs(gdecimal v)
{
	using std::abs;
	return abs(v);
}

gint GMath::Ceil(gfloat v)
{
	using std::ceil;
	return gint(ceil(v));
}

gint GMath::Ceil(gdouble v)
{
	using std::ceil;
	return gint(ceil(v));
}

gint GMath::Ceil(gdecimal v)
{
	using std::ceil;
	return gint(ceil(v));
}

gdouble GMath::Log(gdouble v)
{
	using std::log;
	return log(v);
}

gdecimal GMath::Log(gdecimal v)
{
	using std::log;
	return log(v);
}

gfloat GMath::Log(gfloat v)
{
	using std::log;
	return log(v);
}

gfloat GMath::Exp(gfloat x)
{
	using std::exp;
	return exp(x);
}

gdouble GMath::Exp(gdouble x)
{
	using std::exp;
	return exp(x);
}

gdecimal GMath::Exp(gdecimal x)
{
	using std::exp;
	return exp(x);
}

gdouble Log(gdouble v)
{
	using std::log;
	return log(v);
}

gdecimal Log(gdecimal v)
{
	using std::log;
	return log(v);
}

gint GMath::Floor(gdouble v)
{
	using std::floor;
	return int(floor(v));
}

gdouble GMath::FastSin(gdouble x)
{
	int si = int(x * (0.5 * CS_SINE_TABLE_SIZE / GMath::Cs_PI));
	gdouble d = x - si * (2.0 * GMath::Cs_PI / CS_SINE_TABLE_SIZE);
	int ci = si + CS_SINE_TABLE_SIZE / 4;
	si &= CS_SINE_TABLE_SIZE - 1;
	ci &= CS_SINE_TABLE_SIZE - 1;
	return cs_sine_table[si] + (cs_sine_table[ci] - 0.5 * cs_sine_table[si] * d) * d;
}

gfloat GMath::Sqrt(gfloat v)
{
	using std::sqrt;
	return sqrt(v);
}

gdouble GMath::Sqrt(gdouble v)
{
	using std::sqrt;
	return sqrt(v);
}

#ifdef CS_HAS_DECIMAL
gdecimal GMath::Sqrt(gdecimal v)
{
	using std::sqrt;
	return sqrt(v);
}
#endif // CS_HAS_DECIMAL