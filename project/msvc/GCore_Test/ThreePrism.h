#ifndef _THREE_PRISM_VOLUME_H_
#define _THREE_PRISM_VOLUME_H_

#include <cmath>

// 求一个不规则三棱柱的体积
// 三棱柱的顶面和底面可以不平行，但侧面需要竖直
double VolumeThreePrism(double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xa1, double ya1, double za1,
	double xb1, double yb1, double zb1,
	double xc1, double yc1, double zc1);

/*
int main(int argc, char *argv[])
{
	// 三棱柱 a_b_c-a1_b1_c1
	double v = VolumeThreePrism(
		-1, 0, -1,	// a  (x, y, z)
		1, 0, 0,	// b  (x, y, z)
		0, 1, 0,	// c  (x, y, z)
		-1, 0, 1,	// a1 (x, y, z)
		1, 0, 1,	// b1 (x, y, z)
		0, 1, 2);	// c1 (x, y, z)
	system("pause");
}
*/

// 判断两个双精度浮点是否相等
bool doubleEquals(double v1, double v2);

// 获取三个double的最大值
double maxOf(double x1, double x2, double x3);

// 获取三个double的最小值
double minOf(double x1, double x2, double x3);

// 求两个点的距离
double getDistanceOfTwoPoints(
	double xa, double ya, double za,
	double xb, double yb, double zb);

// 求一个三角形的面积
double getAreaOfTriangle(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc);

// 求角ABC的余弦值
double getCosOfAngle( 
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc);

// 求一个不规则三棱柱的体积
// 要求up面在上，down面在下
double getVolumeOfThreePrism(
	double up_xa, double up_ya, double up_za,
	double up_xb, double up_yb, double up_zb,
	double up_xc, double up_yc, double up_zc,
	double down_xa, double down_ya, double down_za,
	double down_xb, double down_yb, double down_zb,
	double down_xc, double down_yc, double down_zc);

// 求一个特殊五面体a-b-c-d-e的体积
// a、b、c三个点位于同一个平面，d位于b的下面（或上面），e位于c下面（或上面）
double getVolumeOfFivePoints(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xd, double yd, double zd,
	double xe, double ye, double ze);

// 求一个一般三棱锥的体积
double getVolumeOfThreePyramid(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xd, double yd, double zd);

//////////////////////////////////////////////////////////////////////////
// 双精度浮点比较的精度值
#define DOUBLE_PRECISION 0.000001

#define MAX_OF(a,b)  (((a) > (b)) ? (a) : (b))
#define MIN_OF(a,b)  (((a) < (b)) ? (a) : (b))

inline double VolumeThreePrism(double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xa1, double ya1, double za1,
	double xb1, double yb1, double zb1,
	double xc1, double yc1, double zc1)
{
	// 判断哪一个面是up面，哪一个面是down面
	return 
	xa > xa1 ? 
		getVolumeOfThreePrism(
			xa, ya, za,
			xb, yb, zb,
			xc, yc, zc,
			xa1, ya1, za1,
			xb1, yb1, zb1,
			xc1, yc1, zc1)
		:
		getVolumeOfThreePrism(
			xa1, ya1, za1,
			xb1, yb1, zb1,
			xc1, yc1, zc1,
			xa, ya, za,
			xb, yb, zb,
			xc, yc, zc);
}

inline bool doubleEquals(double v1, double v2)
{
	return v1 - v2 <= DOUBLE_PRECISION
		&& v1 - v2 >= -DOUBLE_PRECISION;
}

inline double maxOf(double x1, double x2, double x3)
{
	return MAX_OF(MAX_OF(x1, x2), x3);
}

inline double minOf(double x1, double x2, double x3)
{
	return MIN_OF(MIN_OF(x1, x2), x3);
}

inline double getDistanceOfTwoPoints(double xa, double ya, double za,
	double xb, double yb, double zb)
{
	return std::sqrt((xb - xa) * (xb - xa) 
		+ (yb - ya) * (yb - ya)
		+ (zb - za) * (zb - za));
}

double getAreaOfTriangle(double xa, double ya, double za, 
	double xb, double yb, double zb, 
	double xc, double yc, double zc)
{
	// 海伦公式
	double ab = getDistanceOfTwoPoints(xa, ya, za, xb, yb, zb);
	double bc = getDistanceOfTwoPoints(xb, yb, zb, xc, yc, zc);
	double ca = getDistanceOfTwoPoints(xc, yc, zc, xa, ya, za);
	double p = (ab + bc + ca) / 2.0;
	return std::sqrt(p * (p - ab) * (p - bc) * (p - ca));
}

double getCosOfAngle(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc)
{
	// 构建两个向量ba，bc
	double v1_x = xb - xa;
	double v1_y = yb - ya;
	double v1_z = zb - za;
	double v2_x = xb - xc;
	double v2_y = yb - yc;
	double v2_z = zb - zc;

	// 向量夹角的余弦值等于向量的点乘积除以模的乘积
	double v1_m = std::sqrt(v1_x * v1_x + v1_y * v1_y + v1_z * v1_z);
	double v2_m = std::sqrt(v2_x * v2_x + v2_y * v2_y + v2_z * v2_z);
	double p = v1_x * v2_x + v1_y * v2_y + v1_z * v2_z;
	return p / (v1_m * v2_m);
}

double getVolumeOfThreePrism(double up_xa, double up_ya, double up_za,
	double up_xb, double up_yb, double up_zb,
	double up_xc, double up_yc, double up_zc,
	double down_xa, double down_ya, double down_za,
	double down_xb, double down_yb, double down_zb,
	double down_xc, double down_yc, double down_zc)
{
	// 判断上下面是否水平
	bool up_horizontal = doubleEquals(up_za, up_zb) && doubleEquals(up_za, up_zc);
	bool down_horizontal = doubleEquals(down_za, down_zb) && doubleEquals(down_za, down_zc);

	if (up_horizontal && down_horizontal)
	{
		// 上下面水平，退化为一个标准的三棱柱
		return getAreaOfTriangle(
			up_xa, up_ya, up_za, 
			up_xb, up_yb, up_zb, 
			up_xc, up_yc, up_zc) 
			* (up_za - down_zc);
	}

	// 使用填补法，填补成一个较大的标准三棱柱
	double max_z = maxOf(up_za, up_zb, up_zc);
	double min_z = minOf(down_za, down_zb, down_zc);
	double v_total = getAreaOfTriangle(
		up_xa, up_ya, max_z,
		up_xb, up_yb, max_z,
		up_xc, up_yc, max_z)
		* (max_z - min_z);

	// v_up和v_down分别为上下补充的体积
	// 当上（或下）表面水平时，v_up（或v_down）为0
	// 否则，为一个五面体（或三棱锥）的体积
	double v_up = 0;
	if (!up_horizontal)
	{
		// 以下的操作，目的是为了满足a-b-c在同一个水平面，且d位于b的下面，e位于c下面
		if (doubleEquals(max_z, up_za))
		{
			v_up = getVolumeOfFivePoints(
				up_xa, up_ya, max_z,
				up_xb, up_yb, max_z,
				up_xc, up_yc, max_z,
				up_xb, up_yb, up_zb,
				up_xc, up_yc, up_zc);
		}
		else if (doubleEquals(max_z, up_zb))
		{
			v_up = getVolumeOfFivePoints(
				up_xb, up_yb, max_z,
				up_xa, up_ya, max_z,
				up_xc, up_yc, max_z,
				up_xa, up_ya, up_za,
				up_xc, up_yc, up_zc);
		}
		else
		{
			v_up = getVolumeOfFivePoints(
				up_xc, up_yc, max_z,
				up_xa, up_ya, max_z,
				up_xb, up_yb, max_z,
				up_xa, up_ya, up_za,
				up_xb, up_yb, up_zb);
		}
	}
	double v_down = 0;
	if (!down_horizontal)
	{
		if (doubleEquals(min_z, down_za))
		{
			v_down = getVolumeOfFivePoints(
				down_xa, down_ya, min_z,
				down_xb, down_yb, min_z,
				down_xc, down_yc, min_z,
				down_xb, down_yb, down_zb,
				down_xc, down_yc, down_zc);
		}
		else if (doubleEquals(min_z, up_zb))
		{
			v_down = getVolumeOfFivePoints(
				down_xb, down_yb, min_z,
				down_xa, down_ya, min_z,
				down_xc, down_yc, min_z,
				down_xa, down_ya, down_za,
				down_xc, down_yc, down_zc);
		}
		else
		{
			v_down = getVolumeOfFivePoints(
				down_xc, down_yc, min_z,
				down_xa, down_ya, min_z,
				down_xb, down_yb, min_z,
				down_xa, down_ya, down_za,
				down_xb, down_yb, down_zb);
		}
	}
	return v_total - v_up - v_down;
}

double getVolumeOfFivePoints(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xd, double yd, double zd,
	double xe, double ye, double ze)
{
	// a、b、c三个点位于同一个平面，d位于b的下面（或上面），e位于c下面（或上面）
	if (doubleEquals(zb, zd))
	{
		// 退化为一个三棱锥
		return getAreaOfTriangle(
			xa, ya, za,
			xb, yb, zb,
			xc, yc, zc) * std::abs(zc - ze) / 3.0;
	}
	else if (doubleEquals(zc, ze))
	{
		// 退化为一个三棱锥
		return getAreaOfTriangle(
			xa, ya, za,
			xb, yb, zb,
			xc, yc, zc) * std::abs(zb - zd) / 3.0;
	}

	return (getAreaOfTriangle(
		xa, ya, za,
		xb, yb, zb,
		xc, yc, zc) * std::abs(zc - ze) / 3.0)
		+ getVolumeOfThreePyramid(
			xa, ya, za,
			xb, yb, zb,
			xd, yd, zd,
			xe, ye, ze);
}

double getVolumeOfThreePyramid(
	double xa, double ya, double za,
	double xb, double yb, double zb,
	double xc, double yc, double zc,
	double xd, double yd, double zd)
{
	// b和c的z轴相等
	double a = getDistanceOfTwoPoints(xa, ya, za, xd, yd, zd); // AD
	double b = getDistanceOfTwoPoints(xb, yb, zb, xd, yd, zd); // BD
	double c = getDistanceOfTwoPoints(xc, yc, zc, xd, yd, zd); // CD
	double cos_a = getCosOfAngle( // ADC
		xa, ya, za,
		xd, yd, zd,
		xc, yc, zc);
	double cos_b = getCosOfAngle( // ADB
		xa, ya, za,
		xd, yd, zd,
		xb, yb, zb);
	double cos_c = getCosOfAngle( // BDC
		xb, yb, zb,
		xd, yd, zd,
		xc, yc, zc);
	return (1.0 / 6.0)* a * b * c * (std::sqrt(
		1 - cos_a * cos_a - cos_b * cos_b - cos_c * cos_c + 2 * cos_a * cos_b * cos_c));
}

#undef MIN_OF
#undef MAX_OF
#undef DOUBLE_PRECISION 0.000001

#endif // _THREE_PRISM_VOLUME_H_