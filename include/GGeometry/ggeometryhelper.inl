#ifndef _GEOMETRY_GEOMETRY_HELPER_INLINE_
#define _GEOMETRY_GEOMETRY_HELPER_INLINE_

template<typename GeometryT>
inline GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GGeometryP &geo)
{
	return GGeometryHelper::ConvertSrcToDst<GGeometry, GeometryT>(geo);
}

template<typename GeometryT>
inline GSharedPointer<GeometryT> GGeometryHelper::ConvertTo(GPointP &point)
{
	return GGeometryHelper::ConvertSrcToDst<GPoint, GeometryT>(point);
}

template<typename GeometryT_Src, typename GeometryT_Dst>
inline GSharedPointer<GeometryT_Dst> GGeometryHelper::ConvertSrcToDst(GSharedPointer<GeometryT_Src> &geo)
{
	if (geo.IsNull())
	{
		return GSharedPointer<GeometryT_Dst>(NULL);
	}
	GeometryT_Dst *new_geo = dynamic_cast<GeometryT_Dst *>(&geo);
	if (!new_geo)
	{
		return GSharedPointer<GeometryT_Dst>(NULL);
	}
	return GSharedPointer<GeometryT_Dst>(new_geo, geo.Add());
}

#endif // _GEOMETRY_GEOMETRY_HELPER_INLINE_