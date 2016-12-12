#ifndef _GEOMETRY_COORDINATE_H_
#define _GEOMETRY_COORDINATE_H_

#include "CsGeometry.h"

class CS_API CsCoordinate
{
public:
	CsCoordinate();
	CsCoordinate(cs_real x, cs_real y);

	cs_real X() const;
	cs_real Y() const;

	cs_void SetX(cs_real);
	cs_void SetY(cs_real);
};

#endif // _GEOMETRY_COORDINATE_EX_H_