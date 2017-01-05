#ifndef _GEOMETRY_GEOMETRY_FACTORY_H_
#define _GEOMETRY_GEOMETRY_FACTORY_H_

#include "CsGeometry.h"
#include "CsPoint.h"

class CS_API CsGeometryFactory 
{
public:
	CsPointP CreatePoint(cs_real x, cs_real y) const;
};

#endif // _GEOMETRY_GEOMETRY_FACTORY_H_