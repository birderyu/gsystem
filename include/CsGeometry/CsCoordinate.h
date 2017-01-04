#ifndef _GEOMETRY_COORDINATE_H_
#define _GEOMETRY_COORDINATE_H_

#include "CsGeometryGlobal.h"
#include "CsObject.h"

class CS_API CsCoordinate
	: public CsObject
{
	friend class CsEnvelope;

public:
	CsCoordinate();
	CsCoordinate(cs_real x, cs_real y);
	CsCoordinate(cs_real x, cs_real y, cs_real z);
	CsCoordinate(const CsCoordinate &coord);

	cs_real &X();
	cs_real  X() const;
	cs_real &Y();
	cs_real  Y() const;
	cs_real &Z();
	cs_real  Z() const;

	cs_void SetX(cs_real);
	cs_void SetY(cs_real);
	cs_void SetZ(cs_real);

	cs_uint Dimension() const;

private:
	cs_real m_tCoord[CS_COORDINATE_SIZE];
};

#endif // _GEOMETRY_COORDINATE_EX_H_