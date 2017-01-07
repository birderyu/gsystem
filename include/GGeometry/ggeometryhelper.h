#ifndef _GEOMETRY_GEOMETRY_HELPER_H_
#define _GEOMETRY_GEOMETRY_HELPER_H_

#include "ggeometryinterface.h"

class GAPI GGeometryHelper
{
public:
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GGeometryP &geo);
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GPointP &point);

private:
	template<typename GeometryT_Src, typename GeometryT_Dst>
	static GSharedPointer<GeometryT_Dst> ConvertSrcToDst(GSharedPointer<GeometryT_Src> &geo);
};

#include "ggeometryhelper.inl"

#endif // _GEOMETRY_GEOMETRY_HELPER_H_