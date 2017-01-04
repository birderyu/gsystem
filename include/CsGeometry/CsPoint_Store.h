#ifndef _GEOMETRY_POINT_STORE_H_
#define _GEOMETRY_POINT_STORE_H_

#include "CsGeometryGlobal.h"

class CsPoint_Store_2D
{
public:
	cs_bool Initialize();
	cs_bool Initialize(cs_real x, cs_real y);
	cs_bool Initialize(const CsPoint_Store_2D &);

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