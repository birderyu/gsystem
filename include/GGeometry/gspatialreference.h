#ifndef _GEOMETRY_SPATIAL_REFERENCE_H_
#define _GEOMETRY_SPATIAL_REFERENCE_H_

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

enum class GCoordinateSystemType
{
	/// \brief 未知类型
	Unknown = -1,

	/// \brief 地心坐标系统
	Geocentric = 0x0001,

	/// \brief 地理坐标系统
	Geographic = 0x0002,

	/// \brief 投影坐标系统
	Projected = 0x0004
};

class GSpatialReference
{
public:
	gint GetSRID() const;
	GCoordinateSystemType GetCoordinateSystemType() const;
};

}
}

#endif // _GEOMETRY_SPATIAL_REFERENCE_H_