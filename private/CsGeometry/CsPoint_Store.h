#ifndef _GEOMETRY_POINT_STORE_H_
#define _GEOMETRY_POINT_STORE_H_

#include "CsGeometryGlobal.h"

class CsCoordinate;

class CsPoint2D_Store
{
public:
	cs_void Initialize();
	cs_void Initialize(cs_real x, cs_real y);
	cs_void Initialize(const CsCoordinate &c);
	cs_void Initialize(const CsPoint2D_Store &p_s);

	cs_real &X();
	cs_real  X() const;
	cs_real &Y();
	cs_real  Y() const;

	cs_void SetX(cs_real x);
	cs_void SetY(cs_real y);

private:
	cs_real m_tCoord[2];
};

#endif // _GEOMETRY_POINT_STORE_H_