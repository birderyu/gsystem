#ifndef _GEOMETRY_COORDINATE_H_
#define _GEOMETRY_COORDINATE_H_

#include "CsGeometryGlobal.h"
#include "GCore/gobject.h"

class GAPI CsCoordinate
	: public GObject
{
	friend class CsEnvelope;

public:
	CsCoordinate();
	CsCoordinate(greal x, greal y);
	CsCoordinate(greal x, greal y, greal z);
	CsCoordinate(const greal *p_c, gsize size);
	CsCoordinate(const CsCoordinate &coord);

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;

	gvoid SetX(greal);
	gvoid SetY(greal);
	gvoid SetZ(greal);

	guint Dimension() const;

	const greal *Cursor() const;

private:
	greal m_tCoord[CS_COORDINATE_SIZE];
};

#endif // _GEOMETRY_COORDINATE_EX_H_