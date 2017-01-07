#ifndef _GEOMETRY_POINT_IMPLEMENT_H_
#define _GEOMETRY_POINT_IMPLEMENT_H_

#include "gpoint.h"
#include "gsinglepoint_store.h"
#include "genvelope.h"
#include "gcoordinatesequence.h"

template<gsize DIMENSION>
class GPoint_Impl
	: virtual public GPoint
{
public:
	GPoint_Impl(const GGeometryFactory *factory);
	GPoint_Impl(const GGeometryFactory *factory, greal x);
	GPoint_Impl(const GGeometryFactory *factory, greal x, greal y);
	GPoint_Impl(const GGeometryFactory *factory, greal x, greal y, greal z);
	GPoint_Impl(const GGeometryFactory *factory, const GCoordinate &c);
	GPoint_Impl(const GPoint_Impl<DIMENSION> &p);

	const GGeometryFactory *Factory() const;
	gbool Valid() const;
	gint GeometryType() const;
	guint Dimension() const;
	GEnvelope Envelope() const;
	GCoordinateSequence CoordinateSequence() const;

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
	GSinglePoint_Store<DIMENSION> m_tStore;
	const GGeometryFactory *m_pFactory;
};

#include "gpoint_impl.inl"

#endif // _GEOMETRY_POINT_IMPLEMENT_H_