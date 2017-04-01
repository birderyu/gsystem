#ifndef _GEOMETRY_GEOMETRY_HELPER_INLINE_
#define _GEOMETRY_GEOMETRY_HELPER_INLINE_

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

template<typename GeometryT>
GINLINE GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GGeometryPtr &geo)
{
	return geo.DynamicConvertTo<GeometryT>();
}

template<typename GeometryT>
GINLINE GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GPointPtr &point)
{
	return point.DynamicConvertTo<GeometryT>();
}

}
}

#endif // _GEOMETRY_GEOMETRY_HELPER_INLINE_