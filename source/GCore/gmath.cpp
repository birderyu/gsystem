#include "gmath.h"
#include <cmath>

#define G_SINE_TABLE_SIZE 256
extern const gdouble g_sine_table[G_SINE_TABLE_SIZE] = { 0 };

gdouble GMath::SQRT_2	= 1.41421356237309504880;
gdouble GMath::PI		= 3.14159265358979323846;
gdouble GMath::PI_2		= 1.57079632679489661923;
gdouble GMath::PI_4		= 0.78539816339744830962;
gdouble GMath::_1_PI	= 0.31830988618379067154;
gdouble GMath::_2_PI	= 0.63661977236758134308;
gdouble GMath::E		= 2.7182818284590452354;
gdouble GMath::LOG_2_E	= 1.4426950408889634074;
gdouble GMath::LOG_10_E	= 0.43429448190325182765;
gdouble GMath::LN_2		= 0.69314718055994530942;
gdouble GMath::LN_10	= 2.30258509299404568402;

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
	int si = int(x * (0.5 * G_SINE_TABLE_SIZE / GMath::PI));
	gdouble d = x - si * (2.0 * GMath::PI / G_SINE_TABLE_SIZE);
	int ci = si + G_SINE_TABLE_SIZE / 4;
	si &= G_SINE_TABLE_SIZE - 1;
	ci &= G_SINE_TABLE_SIZE - 1;
	return g_sine_table[si] + (g_sine_table[ci] - 0.5 * g_sine_table[si] * d) * d;
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

#ifdef G_HAS_DECIMAL
gdecimal GMath::Sqrt(gdecimal v)
{
	using std::sqrt;
	return sqrt(v);
}
#endif // G_HAS_DECIMAL

#undef G_SINE_TABLE_SIZE