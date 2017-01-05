#ifndef _GEOMETRY_SINGLE_POINT_STORE_H_
#define _GEOMETRY_SINGLE_POINT_STORE_H_

#include "CsGeometryGlobal.h"
#include "CsCoordinate.h"
#include "CsBytes.h"

template<cs_size_t DIMENSION>
class CsSinglePoint_Store
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION, };

public:
	cs_void Initialize();
	cs_void Initialize(cs_real x);
	cs_void Initialize(cs_real x, cs_real y);
	cs_void Initialize(cs_real x, cs_real y, cs_real z);
	cs_void Initialize(const CsCoordinate &c);
	cs_void Initialize(const CsSinglePoint_Store<DIMENSION> &p_s);

	cs_real &X();
	cs_real  X() const;
	cs_real &Y();
	cs_real  Y() const;
	cs_real &Z();
	cs_real  Z() const;
	CsCoordinate Coordinate() const;

	cs_void SetX(cs_real x);
	cs_void SetY(cs_real y);
	cs_void SetZ(cs_real z);
	cs_void SetCoordinate(const CsCoordinate &c);

	//cs_void Import(const CsBytes &byte);
	//cs_void Export(CsBytes &byte) const;

private:
	cs_real m_aCoord[COORD_VALUE_SIZE];
};

#include "CsSinglePoint_Store.inl"

#endif // _GEOMETRY_SINGLE_POINT_STORE_H_
