#ifndef _GEOMETRY_GEOMETRY_CONVERT_H_
#define _GEOMETRY_GEOMETRY_CONVERT_H_

#include "CsGeometry.h"
#include "CsPoint.h"

class CS_API CsGeometryConvert
{
public:
	static CsPointP ToPoint(const CsGeometryP &geo);
};

#endif // _GEOMETRY_GEOMETRY_CONVERT_H_