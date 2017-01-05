#ifndef _GEOMETRY_POINT_IMPLEMENT_H_
#define _GEOMETRY_POINT_IMPLEMENT_H_

#include "CsPoint.h"
#include "CsSinglePoint_Store.h"
#include "CsEnvelope.h"
#include "CsCoordinateSequence.h"

template<cs_size_t DIMENSION>
class CsPoint_Impl
	: virtual public CsPoint
{
public:
	CsPoint_Impl(const CsGeometryFactory *factory);
	CsPoint_Impl(const CsGeometryFactory *factory, cs_real x);
	CsPoint_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y);
	CsPoint_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y, cs_real z);
	CsPoint_Impl(const CsGeometryFactory *factory, const CsCoordinate &c);
	CsPoint_Impl(const CsPoint_Impl<DIMENSION> &p);

	const CsGeometryFactory *GeometryFactory() const;
	cs_bool Valid() const;
	cs_int GeometryType() const;
	cs_uint Dimension() const;
	CsEnvelope Envelope() const;
	CsCoordinateSequence CoordinateSequence() const;

	cs_real &X();
	cs_real  X() const;
	cs_real &Y();
	cs_real  Y() const;
	cs_real &Z();
	cs_real  Z() const;
	cs_void SetX(cs_real x);
	cs_void SetY(cs_real y);
	cs_void SetZ(cs_real z);

private:
	CsSinglePoint_Store<DIMENSION> m_tStore;
	const CsGeometryFactory *m_pFactory;
};

#include "CsPoint_Impl.inl"

#endif // _GEOMETRY_POINT_IMPLEMENT_H_