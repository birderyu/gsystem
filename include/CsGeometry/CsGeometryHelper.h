#ifndef _GEOMETRY_GEOMETRY_HELPER_H_
#define _GEOMETRY_GEOMETRY_HELPER_H_

#include "CsGeometryInterface.h"

class GAPI CsGeometryHelper
{
public:
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(CsGeometryP &geo);
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(CsPointP &point);

private:
	template<typename GeometryT_Src, typename GeometryT_Dst>
	static GSharedPointer<GeometryT_Dst> ConvertSrcToDst(GSharedPointer<GeometryT_Src> &geo);
};

#include "CsGeometryHelper.inl"

#endif // _GEOMETRY_GEOMETRY_HELPER_H_