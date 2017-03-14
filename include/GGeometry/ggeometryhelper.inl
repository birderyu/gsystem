#ifndef _GEOMETRY_GEOMETRY_HELPER_INLINE_
#define _GEOMETRY_GEOMETRY_HELPER_INLINE_

namespace gnova { // gnova
namespace geom { // gnova.geom

template<typename GeometryT>
GINLINE GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GGeometryP &geo)
{
	return geo.DynamicConvertTo<GeometryT>();
}

template<typename GeometryT>
GINLINE GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GPointP &point)
{
	return point.DynamicConvertTo<GeometryT>();
}

}
}

#endif // _GEOMETRY_GEOMETRY_HELPER_INLINE_