#ifndef _GEOMETRY_GEOMETRY_FACTORY_H_
#define _GEOMETRY_GEOMETRY_FACTORY_H_

#include "CsGeometry.h"

class CS_API CsGeometryFactory 
{
public:
	CsGeometryP CreatePoint2D(cs_real x, cs_real y) const;

#ifdef CS_GEOMETRY_HAS_Z
	CsGeometryP CreatePoint3D(cs_real x, cs_real y, cs_real z) const;
#endif
};

#endif // _GEOMETRY_GEOMETRY_FACTORY_H_