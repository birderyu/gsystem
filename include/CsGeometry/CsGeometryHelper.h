#ifndef _GEOMETRY_GEOMETRY_HELPER_H_
#define _GEOMETRY_GEOMETRY_HELPER_H_

#include "CsGeometryInterface.h"

class CS_API CsGeometryHelper
{
public:
	template<typename GeometryT> static CsSharedPointer<GeometryT> ConvertTo(CsGeometryP &geo);
	template<typename GeometryT> static CsSharedPointer<GeometryT> ConvertTo(CsPointP &point);

private:
	template<typename GeometryT_Src, typename GeometryT_Dst>
	static CsSharedPointer<GeometryT_Dst> ConvertSrcToDst(CsSharedPointer<GeometryT_Src> &geo);
};

#include "CsGeometryHelper.inl"

#endif // _GEOMETRY_GEOMETRY_HELPER_H_