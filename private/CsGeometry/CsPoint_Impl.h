#ifndef _GEOMETRY_POINT_IMPLEMENT_H_
#define _GEOMETRY_POINT_IMPLEMENT_H_

#include "CsPoint.h"
#include "CsPoint_Store.h"

class CsPoint2D_Impl
	: public CsPoint2D
{
public:
	CsPoint2D_Impl(const CsGeometryFactory *factory);
	CsPoint2D_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y);
	CsPoint2D_Impl(const CsGeometryFactory *factory, const CsCoordinate &c);
	CsPoint2D_Impl(const CsPoint2D_Impl &p);

	const CsGeometryFactory *GeometryFactory() const;
	cs_bool Valid() const;
	cs_int GeometryType() const;
	cs_uint Dimension() const;
	cs_real Length() const;
	cs_real Area() const;
	cs_real Volume() const;
	CsEnvelope Envelope() const;
	CsCoordinateSequence CoordinateSequence() const;

	cs_real &X();
	cs_real  X() const;
	cs_real &Y();
	cs_real  Y() const;
	cs_void SetX(cs_real x);
	cs_void SetY(cs_real y);

private:
	CsPoint2D_Store m_tStore;
	const CsGeometryFactory *m_pFactory;
};

typedef CsPoint2D_Impl CsPoint_Impl;

#endif // _GEOMETRY_POINT_IMPLEMENT_H_