#ifndef _GEOMETRY_POINT_IMPLEMENT_INLINE_
#define _GEOMETRY_POINT_IMPLEMENT_INLINE_

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GGeometryFactory *factory)
: m_pFactory(factory), m_tStore()
{

}

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GGeometryFactory *factory, greal x)
: m_pFactory(factory), m_tStore(x)
{
	
}

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GGeometryFactory *factory, greal x, greal y)
: m_pFactory(factory), m_tStore(x, y)
{
	
}

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GGeometryFactory *factory, greal x, greal y, greal z)
: m_pFactory(factory), m_tStore(x, y, z)
{
	
}

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GGeometryFactory *factory, const GCoordinate &c)
: m_pFactory(factory), m_tStore(c)
{
	
}

template<gsize DIMENSION>
GINLINE GPoint_Impl<DIMENSION>::GPoint_Impl(const GPoint_Impl<DIMENSION> &p)
: m_pFactory(p.m_pFactory), m_tStore(p.m_tStore)
{
	
}

template<gsize DIMENSION>
GINLINE const GGeometryFactory * GPoint_Impl<DIMENSION>::Factory() const
{
	return m_pFactory;
}

template<gsize DIMENSION>
GINLINE gbool GPoint_Impl<DIMENSION>::Valid() const
{
	return true;
}

template<gsize DIMENSION>
GINLINE gint GPoint_Impl<DIMENSION>::GeometryType() const
{
	return GEOMETRY_TYPE_POINT;
}

template<gsize DIMENSION>
GINLINE guint GPoint_Impl<DIMENSION>::Dimension() const
{
	return GEOMETRY_DIMENSION_2;
}

template<gsize DIMENSION>
GINLINE GEnvelope GPoint_Impl<DIMENSION>::Envelope() const
{
	return GEnvelope(X(), Y());
}

template<gsize DIMENSION>
GINLINE GCoordinateSequence GPoint_Impl<DIMENSION>::CoordinateSequence() const
{
	return GCoordinateSequence(X(), Y());
}

template<gsize DIMENSION>
GINLINE greal &GPoint_Impl<DIMENSION>::X()
{
	return m_tStore.X();
}

template<gsize DIMENSION>
GINLINE greal GPoint_Impl<DIMENSION>::X() const
{
	return m_tStore.X();
}

template<gsize DIMENSION>
GINLINE greal &GPoint_Impl<DIMENSION>::Y()
{
	return m_tStore.Y();
}

template<gsize DIMENSION>
GINLINE greal GPoint_Impl<DIMENSION>::Y() const
{
	return m_tStore.Y();
}

template<gsize DIMENSION>
GINLINE greal &GPoint_Impl<DIMENSION>::Z()
{
	return m_tStore.Z();
}

template<gsize DIMENSION>
GINLINE greal GPoint_Impl<DIMENSION>::Z() const
{
	return m_tStore.Z();
}

template<gsize DIMENSION>
GINLINE gvoid GPoint_Impl<DIMENSION>::SetX(greal x)
{
	m_tStore.SetX(x);
}

template<gsize DIMENSION>
GINLINE gvoid GPoint_Impl<DIMENSION>::SetY(greal y)
{
	m_tStore.SetX(y);
}

template<gsize DIMENSION>
GINLINE gvoid GPoint_Impl<DIMENSION>::SetZ(greal z)
{
	m_tStore.SetZ(z);
}

} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#endif // _GEOMETRY_POINT_IMPLEMENT_INLINE_