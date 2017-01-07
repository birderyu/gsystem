#ifndef _GEOMETRY_POINT_IMPLEMENT_H_
#define _GEOMETRY_POINT_IMPLEMENT_H_

#include "CsPoint.h"
#include "CsSinglePoint_Store.h"
#include "CsEnvelope.h"
#include "CsCoordinateSequence.h"

template<gsize DIMENSION>
class CsPoint_Impl
	: virtual public CsPoint
{
public:
	CsPoint_Impl(const CsGeometryFactory *factory);
	CsPoint_Impl(const CsGeometryFactory *factory, greal x);
	CsPoint_Impl(const CsGeometryFactory *factory, greal x, greal y);
	CsPoint_Impl(const CsGeometryFactory *factory, greal x, greal y, greal z);
	CsPoint_Impl(const CsGeometryFactory *factory, const CsCoordinate &c);
	CsPoint_Impl(const CsPoint_Impl<DIMENSION> &p);

	const CsGeometryFactory *GeometryFactory() const;
	gbool Valid() const;
	gint GeometryType() const;
	guint Dimension() const;
	CsEnvelope Envelope() const;
	CsCoordinateSequence CoordinateSequence() const;

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;
	gvoid SetX(greal x);
	gvoid SetY(greal y);
	gvoid SetZ(greal z);

private:
	CsSinglePoint_Store<DIMENSION> m_tStore;
	const CsGeometryFactory *m_pFactory;
};

#include "CsPoint_Impl.inl"

#endif // _GEOMETRY_POINT_IMPLEMENT_H_