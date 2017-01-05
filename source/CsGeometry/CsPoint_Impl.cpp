#include "CsPoint_Impl.h"
#include "CsEnvelope.h"
#include "CsCoordinateSequence.h"

CsPoint2D_Impl::CsPoint2D_Impl(const CsGeometryFactory *factory)
: m_pFactory(factory)
{
	m_tStore.Initialize();
}

CsPoint2D_Impl::CsPoint2D_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y)
: m_pFactory(factory)
{
	m_tStore.Initialize(x, y);
}

CsPoint2D_Impl::CsPoint2D_Impl(const CsGeometryFactory *factory, const CsCoordinate &c)
: m_pFactory(factory)
{
	m_tStore.Initialize(c);
}

CsPoint2D_Impl::CsPoint2D_Impl(const CsPoint2D_Impl &p)
: m_pFactory(p.m_pFactory)
{
	m_tStore.Initialize(p.m_tStore);
}

const CsGeometryFactory * CsPoint2D_Impl::GeometryFactory() const
{
	return m_pFactory;
}

cs_bool CsPoint2D_Impl::Valid() const
{
	return true;
}

cs_int CsPoint2D_Impl::GeometryType() const
{
	return GEOMETRY_TYPE_POINT;
}

cs_uint CsPoint2D_Impl::Dimension() const
{
	return GEOMETRY_DIMENSION_2;
}

cs_real CsPoint2D_Impl::Length() const
{
	return 0;
}

cs_real CsPoint2D_Impl::Area() const
{
	return 0;
}

cs_real CsPoint2D_Impl::Volume() const
{
	return 0;
}

CsEnvelope CsPoint2D_Impl::Envelope() const
{
	return CsEnvelope(X(), Y());
}

CsCoordinateSequence CsPoint2D_Impl::CoordinateSequence() const
{
	return CsCoordinateSequence(X(), Y());
}

cs_real &CsPoint2D_Impl::X()
{
	return m_tStore.X();
}

cs_real CsPoint2D_Impl::X() const
{
	return m_tStore.X();
}

cs_real &CsPoint2D_Impl::Y()
{
	return m_tStore.Y();
}

cs_real CsPoint2D_Impl::Y() const
{
	return m_tStore.Y();
}

cs_void CsPoint2D_Impl::SetX(cs_real x)
{
	m_tStore.SetX(x);
}

cs_void CsPoint2D_Impl::SetY(cs_real y)
{
	m_tStore.SetX(y);
}