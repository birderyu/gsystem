#ifndef _GEOMETRY_GEOMETRY_FACTORY_H_
#define _GEOMETRY_GEOMETRY_FACTORY_H_

#include "ggeometry.h"

class GAPI GGeometryFactory 
{
public:
	GGeometryP CreatePoint2D(greal x, greal y) const;

#ifdef G_GEOMETRY_HAS_Z
	GGeometryP CreatePoint3D(greal x, greal y, greal z) const;
#endif
};

#endif // _GEOMETRY_GEOMETRY_FACTORY_H_