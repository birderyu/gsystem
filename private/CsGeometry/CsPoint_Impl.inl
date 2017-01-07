#ifndef _GEOMETRY_POINT_IMPLEMENT_INLINE_
#define _GEOMETRY_POINT_IMPLEMENT_INLINE_

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory)
: m_pFactory(factory)
{
	m_tStore.Initialize();
}

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, greal x)
: m_pFactory(factory)
{
	m_tStore.Initialize(x);
}

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, greal x, greal y)
: m_pFactory(factory)
{
	m_tStore.Initialize(x, y);
}

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, greal x, greal y, greal z)
: m_pFactory(factory)
{
	m_tStore.Initialize(x, y, z);
}

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, const CsCoordinate &c)
: m_pFactory(factory)
{
	m_tStore.Initialize(c);
}

template<gsize DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsPoint_Impl<DIMENSION> &p)
: m_pFactory(p.m_pFactory)
{
	m_tStore.Initialize(p.m_tStore);
}

template<gsize DIMENSION>
inline const CsGeometryFactory * CsPoint_Impl<DIMENSION>::GeometryFactory() const
{
	return m_pFactory;
}

template<gsize DIMENSION>
inline gbool CsPoint_Impl<DIMENSION>::Valid() const
{
	return true;
}

template<gsize DIMENSION>
inline gint CsPoint_Impl<DIMENSION>::GeometryType() const
{
	return GEOMETRY_TYPE_POINT;
}

template<gsize DIMENSION>
inline guint CsPoint_Impl<DIMENSION>::Dimension() const
{
	return GEOMETRY_DIMENSION_2;
}

template<gsize DIMENSION>
inline CsEnvelope CsPoint_Impl<DIMENSION>::Envelope() const
{
	return CsEnvelope(X(), Y());
}

template<gsize DIMENSION>
inline CsCoordinateSequence CsPoint_Impl<DIMENSION>::CoordinateSequence() const
{
	return CsCoordinateSequence(X(), Y());
}

template<gsize DIMENSION>
inline greal &CsPoint_Impl<DIMENSION>::X()
{
	return m_tStore.X();
}

template<gsize DIMENSION>
inline greal CsPoint_Impl<DIMENSION>::X() const
{
	return m_tStore.X();
}

template<gsize DIMENSION>
inline greal &CsPoint_Impl<DIMENSION>::Y()
{
	return m_tStore.Y();
}

template<gsize DIMENSION>
inline greal CsPoint_Impl<DIMENSION>::Y() const
{
	return m_tStore.Y();
}

template<gsize DIMENSION>
inline greal &CsPoint_Impl<DIMENSION>::Z()
{
	return m_tStore.Z();
}

template<gsize DIMENSION>
inline greal CsPoint_Impl<DIMENSION>::Z() const
{
	return m_tStore.Z();
}

template<gsize DIMENSION>
inline gvoid CsPoint_Impl<DIMENSION>::SetX(greal x)
{
	m_tStore.SetX(x);
}

template<gsize DIMENSION>
inline gvoid CsPoint_Impl<DIMENSION>::SetY(greal y)
{
	m_tStore.SetX(y);
}

template<gsize DIMENSION>
inline gvoid CsPoint_Impl<DIMENSION>::SetZ(greal z)
{
	m_tStore.SetZ(z);
}

#endif // _GEOMETRY_POINT_IMPLEMENT_INLINE_