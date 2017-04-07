#ifndef _GEOMETRY_GEOMETRY_GLOBAL_H_
#define _GEOMETRY_GEOMETRY_GLOBAL_H_

#include "GCore/gglobal.h"

#define G_GEOMETRY_HAS_Z

#ifdef G_GEOMETRY_HAS_Z
#	define G_COORDINATE_SIZE	3
#	define G_ENVELOPE_SIZE		6
#	define G_COORDINATE_X_POS	0
#	define G_COORDINATE_Y_POS	1
#	define G_COORDINATE_Z_POS	2
#else // !G_GEOMETRY_HAS_Z
#	define G_COORDINATE_SIZE	2
#	define G_ENVELOPE_SIZE		4
#	define G_COORDINATE_X_POS	0
#	define G_COORDINATE_Y_POS	1
#endif // G_GEOMETRY_HAS_Z

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

// 维度 * 4
enum class GDimension
{
	_0_ = 0,
	_1_ = 1,
	_2_ = 2,
	_3_ = 3,
	_4_ = 4,
};

enum class GCoordinateType
{
	Plane = 0,
	Sphere = 1,
};

enum class GGeometryType
{
	Null = 0,
	Point,
	LineString,
	Polygon,
	MulitPoint,
	MulitLineString,
	MulitPolygon,
};

enum G_GEOMETRY_DIMENSION
{
	GEOMETRY_DIMENSION_0 = 0,	/**< 零维 */
	GEOMETRY_DIMENSION_1 = 1,	/**< 一维 */
	GEOMETRY_DIMENSION_2 = 2,	/**< 二维 */
	GEOMETRY_DIMENSION_3 = 3,	/**< 三维 */
};

// 坐标类型 * 2
enum G_GEOMETRY_COORDINATE
{
	GEOMETRY_COORDINATE_PLANE	= 0,	/**< 平面 */
	GEOMETRY_COORDINATE_SPHERE	= 1,	/**< 球面 */
};

// 几何类型 * 32
enum G_GEOMETRY_TYPE
{
	GEOMETRY_TYPE_NULL = 0,
	GEOMETRY_TYPE_POINT,
	GEOMETRY_TYPE_CURVE,		// 线模型
	GEOMETRY_TYPE_SURFACE,		// 面模型
	GEOMETRY_TYPE_BODY,			// 体模型
	GEOMETRY_TYPE_COLLECTION,	// 集合模型

	// 线模型实例
	GEOMETRY_TYPE_SEGMENT,	// 线段
	GEOMETRY_TYPE_LINE,		// 直线
	GEOMETRY_TYPE_POLYLINE, // 折线
	GEOMETRY_TYPE_RING,		// 环

	// 面模型实例
	GEOMETRY_TYPE_POLYLGON,
	GEOMETRY_TYPE_TRIANGLE,		// 三角形
	GEOMETRY_TYPE_QUADRANGLE,	// 四边形
	GEOMETRY_TYPE_1, // 矩形
	GEOMETRY_TYPE_2, // 正方形
	GEOMETRY_TYPE_3, // 圆形
	GEOMETRY_TYPE_4, // 椭圆形

	// 体模型实例
	GEOMETRY_TYPE_POLYHEDRON,	// 多面体
	GEOMETRY_TYPE_TETRAHEDRON,	// 四面体
	GEOMETRY_TYPE_HEXAHEDRON,	// 六面体
	GEOMETRY_TYPE_5,	// 立方体
	GEOMETRY_TYPE_6,	// 椭球体
	GEOMETRY_TYPE_7,	// 球体

	// 集合模型实例
	GEOMETRY_TYPE_MULTI_POINT,
	GEOMETRY_TYPE_MULTI_POLYLINE,
	GEOMETRY_TYPE_MULTI_POLYLGON,
	GEOMETRY_TYPE_MULTI_POLYHEDRON,
};

struct GGeometryGlobal
{
	static greal _g_n_coordinate_x_;
	static greal _g_n_coordinate_y_;
	static greal _g_n_coordinate_z_;
};

}
}

#endif // _GEOMETRY_GEOMETRY_GLOBAL_H_