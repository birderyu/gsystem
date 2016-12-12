#ifndef _CORE_GEOMETRY_3D_H_
#define _CORE_GEOMETRY_3D_H_

#include "CsGeometry.h"

class CsGeometry3D;
typedef CsSharedPointer<CsGeometry3D> CsGeometry3DP;

class CS_API CsGeometry3D
	: public CsGeometry
{
public:
	virtual ~CsGeometry3D() = 0;
};

#endif // _CORE_GEOMETRY_3D_H_