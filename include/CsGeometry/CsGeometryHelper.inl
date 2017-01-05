#ifndef _GEOMETRY_GEOMETRY_HELPER_INLINE_
#define _GEOMETRY_GEOMETRY_HELPER_INLINE_

template<typename GeometryT>
inline CsSharedPointer<GeometryT> CsGeometryHelper::ConvertTo(CsGeometryP &geo)
{
	return CsGeometryHelper::ConvertSrcToDst<CsGeometry, GeometryT>(geo);
}

template<typename GeometryT>
inline CsSharedPointer<GeometryT> CsGeometryHelper::ConvertTo(CsPointP &point)
{
	return CsGeometryHelper::ConvertSrcToDst<CsPoint, GeometryT>(point);
}

template<typename GeometryT_Src, typename GeometryT_Dst>
inline CsSharedPointer<GeometryT_Dst> CsGeometryHelper::ConvertSrcToDst(CsSharedPointer<GeometryT_Src> &geo)
{
	if (geo.IsNull())
	{
		return CsSharedPointer<GeometryT_Dst>(NULL);
	}
	GeometryT_Dst *new_geo = dynamic_cast<GeometryT_Dst *>(&geo);
	if (!new_geo)
	{
		return CsSharedPointer<GeometryT_Dst>(NULL);
	}
	return CsSharedPointer<GeometryT_Dst>(new_geo, geo.Add());
}

#endif // _GEOMETRY_GEOMETRY_HELPER_INLINE_