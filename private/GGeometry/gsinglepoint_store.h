#ifndef _GEOMETRY_SINGLE_POINT_STORE_H_
#define _GEOMETRY_SINGLE_POINT_STORE_H_

#include "ggeometryglobal.h"
#include "gcoordinate.h"
#include "GCore/gbytes.h"

template<gsize DIMENSION>
class GSinglePoint_Store
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION, };

public:
	gvoid Initialize();
	gvoid Initialize(greal x);
	gvoid Initialize(greal x, greal y);
	gvoid Initialize(greal x, greal y, greal z);
	gvoid Initialize(const GCoordinate &c);
	gvoid Initialize(const GSinglePoint_Store<DIMENSION> &p_s);

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;
	GCoordinate Coordinate() const;

	gvoid SetX(greal x);
	gvoid SetY(greal y);
	gvoid SetZ(greal z);
	gvoid SetCoordinate(const GCoordinate &c);

	//gvoid Import(const GBytes &byte);
	//gvoid Export(GBytes &byte) const;

private:
	greal m_aCoord[COORD_VALUE_SIZE];
};

#include "gsinglepoint_store.inl"

#endif // _GEOMETRY_SINGLE_POINT_STORE_H_
