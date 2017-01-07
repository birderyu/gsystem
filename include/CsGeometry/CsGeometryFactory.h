#ifndef _GEOMETRY_GEOMETRY_FACTORY_H_
#define _GEOMETRY_GEOMETRY_FACTORY_H_

#include "CsGeometry.h"

class GAPI CsGeometryFactory 
{
public:
	CsGeometryP CreatePoint2D(greal x, greal y) const;

#ifdef CS_GEOMETRY_HAS_Z
	CsGeometryP CreatePoint3D(greal x, greal y, greal z) const;
#endif
};

#endif // _GEOMETRY_GEOMETRY_FACTORY_H_