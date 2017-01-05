#ifndef _GEOMETRY_POINT_3D_H_
#define _GEOMETRY_POINT_3D_H_

#include "CsGeometryGlobal.h"

#ifdef CS_GEOMETRY_HAS_Z
#include "CsGeometry.h"

class CS_API CsPoint3D
	: public CsGeometry
{
public:
	virtual ~CsPoint3D() = 0;
};

#endif // CS_GEOMETRY_HAS_Z

#endif // _GEOMETRY_POINT_3D_H_