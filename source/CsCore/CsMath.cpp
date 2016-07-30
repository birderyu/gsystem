#include "CsMath.h"
#include <cmath>

#define CS_SINE_TABLE_SIZE 256
extern const cs_real cs_sine_table[CS_SINE_TABLE_SIZE];

cs_real CsMath::Cs_Sqrt2	= 1.41421356237309504880;
cs_real CsMath::Cs_PI		= 3.14159265358979323846;
cs_real CsMath::Cs_PI_2		= 1.57079632679489661923;
cs_real CsMath::Cs_PI_4		= 0.78539816339744830962;
cs_real CsMath::Cs_1_PI		= 0.31830988618379067154;
cs_real CsMath::Cs_2_PI		= 0.63661977236758134308;
cs_real CsMath::Cs_E		= 2.7182818284590452354;
cs_real CsMath::Cs_Log2E	= 1.4426950408889634074;
cs_real CsMath::Cs_Log10E	= 0.43429448190325182765;
cs_real CsMath::Cs_Ln2		= 0.69314718055994530942;
cs_real CsMath::Cs_Ln10		= 2.30258509299404568402;

cs_uint CsMath::Abs(cs_int v)
{
	using std::abs;
	return abs(v);
}

cs_double CsMath::Abs(cs_double v)
{
	using std::abs;
	return abs(v);
}

cs_decimal CsMath::Abs(cs_decimal v)
{
	using std::abs;
	return abs(v);
}

cs_int CsMath::Ceil(cs_real v)
{
	using std::ceil;
	return cs_int(ceil(v));
}

cs_int CsMath::Floor(cs_real v)
{
	using std::floor;
	return int(floor(v));
}

cs_real CsMath::FastSin(cs_real x)
{
	/*
	// Would be more accurate with qRound, but slower.
	int si = int(x * (0.5 * CS_SINE_TABLE_SIZE / CsMath::Cs_PI));
	cs_real d = x - si * (2.0 * CsMath::Cs_PI / CS_SINE_TABLE_SIZE);
	int ci = si + CS_SINE_TABLE_SIZE / 4;
	si &= CS_SINE_TABLE_SIZE - 1;
	ci &= CS_SINE_TABLE_SIZE - 1;
	return cs_sine_table[si] + (cs_sine_table[ci] - 0.5 * cs_sine_table[si] * d) * d;
	*/
	return 0;
}

CsMath::CsMath()
{

}

CsMath::~CsMath()
{

}