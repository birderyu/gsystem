#ifndef _GEOMETRY_POINT_IMPLEMENT_INLINE_
#define _GEOMETRY_POINT_IMPLEMENT_INLINE_

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory)
: m_pFactory(factory)
{
	m_tStore.Initialize();
}

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, cs_real x)
: m_pFactory(factory)
{
	m_tStore.Initialize(x);
}

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y)
: m_pFactory(factory)
{
	m_tStore.Initialize(x, y);
}

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, cs_real x, cs_real y, cs_real z)
: m_pFactory(factory)
{
	m_tStore.Initialize(x, y, z);
}

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsGeometryFactory *factory, const CsCoordinate &c)
: m_pFactory(factory)
{
	m_tStore.Initialize(c);
}

template<cs_size_t DIMENSION>
inline CsPoint_Impl<DIMENSION>::CsPoint_Impl(const CsPoint_Impl<DIMENSION> &p)
: m_pFactory(p.m_pFactory)
{
	m_tStore.Initialize(p.m_tStore);
}

template<cs_size_t DIMENSION>
inline const CsGeometryFactory * CsPoint_Impl<DIMENSION>::GeometryFactory() const
{
	return m_pFactory;
}

template<cs_size_t DIMENSION>
inline cs_bool CsPoint_Impl<DIMENSION>::Valid() const
{
	return true;
}

template<cs_size_t DIMENSION>
inline cs_int CsPoint_Impl<DIMENSION>::GeometryType() const
{
	return GEOMETRY_TYPE_POINT;
}

template<cs_size_t DIMENSION>
inline cs_uint CsPoint_Impl<DIMENSION>::Dimension() const
{
	return GEOMETRY_DIMENSION_2;
}

template<cs_size_t DIMENSION>
inline CsEnvelope CsPoint_Impl<DIMENSION>::Envelope() const
{
	return CsEnvelope(X(), Y());
}

template<cs_size_t DIMENSION>
inline CsCoordinateSequence CsPoint_Impl<DIMENSION>::CoordinateSequence() const
{
	return CsCoordinateSequence(X(), Y());
}

template<cs_size_t DIMENSION>
inline cs_real &CsPoint_Impl<DIMENSION>::X()
{
	return m_tStore.X();
}

template<cs_size_t DIMENSION>
inline cs_real CsPoint_Impl<DIMENSION>::X() const
{
	return m_tStore.X();
}

template<cs_size_t DIMENSION>
inline cs_real &CsPoint_Impl<DIMENSION>::Y()
{
	return m_tStore.Y();
}

template<cs_size_t DIMENSION>
inline cs_real CsPoint_Impl<DIMENSION>::Y() const
{
	return m_tStore.Y();
}

template<cs_size_t DIMENSION>
inline cs_real &CsPoint_Impl<DIMENSION>::Z()
{
	return m_tStore.Z();
}

template<cs_size_t DIMENSION>
inline cs_real CsPoint_Impl<DIMENSION>::Z() const
{
	return m_tStore.Z();
}

template<cs_size_t DIMENSION>
inline cs_void CsPoint_Impl<DIMENSION>::SetX(cs_real x)
{
	m_tStore.SetX(x);
}

template<cs_size_t DIMENSION>
inline cs_void CsPoint_Impl<DIMENSION>::SetY(cs_real y)
{
	m_tStore.SetX(y);
}

template<cs_size_t DIMENSION>
inline cs_void CsPoint_Impl<DIMENSION>::SetZ(cs_real z)
{
	m_tStore.SetZ(z);
}

#endif // _GEOMETRY_POINT_IMPLEMENT_INLINE_