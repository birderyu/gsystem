#ifndef _GEOMETRY_SINGLE_POINT_STORE_H_
#define _GEOMETRY_SINGLE_POINT_STORE_H_

#include "CsGeometryGlobal.h"
#include "CsCoordinate.h"
#include "gbytes.h"

template<gsize DIMENSION>
class CsSinglePoint_Store
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION, };

public:
	gvoid Initialize();
	gvoid Initialize(greal x);
	gvoid Initialize(greal x, greal y);
	gvoid Initialize(greal x, greal y, greal z);
	gvoid Initialize(const CsCoordinate &c);
	gvoid Initialize(const CsSinglePoint_Store<DIMENSION> &p_s);

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;
	CsCoordinate Coordinate() const;

	gvoid SetX(greal x);
	gvoid SetY(greal y);
	gvoid SetZ(greal z);
	gvoid SetCoordinate(const CsCoordinate &c);

	//cs_void Import(const CsBytes &byte);
	//cs_void Export(CsBytes &byte) const;

private:
	greal m_aCoord[COORD_VALUE_SIZE];
};

#include "CsSinglePoint_Store.inl"

#endif // _GEOMETRY_SINGLE_POINT_STORE_H_
