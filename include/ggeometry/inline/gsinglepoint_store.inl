#ifndef _GEOMETRY_SINGLE_POINT_STORE_INLINE_
#define _GEOMETRY_SINGLE_POINT_STORE_INLINE_

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store()
{
	GMemSet(m_aCoord, 0, sizeof(greal)* DIMENSION);
}

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store(greal x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
	m_aCoord[2] = 0;
}

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store(greal x, greal y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = 0;
}

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = z;
}

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store(const GCoordinate &c)
{
	gsize real_size = DIMENSION < G_COORDINATE_SIZE ? DIMENSION : G_COORDINATE_SIZE;
	GMemCopy(m_aCoord, c.Cursor(), sizeof(greal) * real_size);
}

template<gsize DIMENSION>
GINLINE GSinglePoint_Store<DIMENSION>::GSinglePoint_Store(const GSinglePoint_Store<DIMENSION> &p_s)
{
	GMemCopy(m_aCoord, p_s.m_aCoord, sizeof(greal) * DIMENSION);
}

template<gsize DIMENSION>
GINLINE greal &GSinglePoint_Store<DIMENSION>::X()
{
	return m_aCoord[0];
}

template<gsize DIMENSION>
GINLINE greal GSinglePoint_Store<DIMENSION>::X() const
{
	return m_aCoord[0];
}

template<gsize DIMENSION>
GINLINE greal &GSinglePoint_Store<DIMENSION>::Y()
{
	return m_aCoord[1];
}

template<gsize DIMENSION>
GINLINE greal GSinglePoint_Store<DIMENSION>::Y() const
{
	return m_aCoord[1];
}

template<gsize DIMENSION>
GINLINE greal &GSinglePoint_Store<DIMENSION>::Z()
{
	return m_aCoord[2];
}

template<gsize DIMENSION>
GINLINE greal GSinglePoint_Store<DIMENSION>::Z() const
{
	return m_aCoord[2];
}

template<gsize DIMENSION>
GINLINE GCoordinate GSinglePoint_Store<DIMENSION>::Coordinate() const
{
	return GCoordinate(m_aCoord, DIMENSION);
}

template<gsize DIMENSION>
GINLINE gvoid GSinglePoint_Store<DIMENSION>::SetX(greal x)
{
	m_aCoord[0] = x;
}

template<gsize DIMENSION>
GINLINE gvoid GSinglePoint_Store<DIMENSION>::SetY(greal y)
{
	m_aCoord[1] = y;
}

template<gsize DIMENSION>
GINLINE gvoid GSinglePoint_Store<DIMENSION>::SetZ(greal z)
{
	m_aCoord[2] = z;
}

template<gsize DIMENSION>
GINLINE gvoid GSinglePoint_Store<DIMENSION>::SetCoordinate(const GCoordinate &c)
{
	gsize real_size = DIMENSION < G_COORDINATE_SIZE ? DIMENSION : G_COORDINATE_SIZE;
	GMemCopy(m_aCoord, c.Cursor(), sizeof(greal)* real_size);
}

//////////////////////////////////////////////////////////////////////////

template<>
GINLINE GSinglePoint_Store<1>::GSinglePoint_Store(greal x)
{
	m_aCoord[0] = x;
}

template<>
GINLINE GSinglePoint_Store<1>::GSinglePoint_Store(greal x, greal y)
{
	m_aCoord[0] = x;
}

template<>
GINLINE GSinglePoint_Store<1>::GSinglePoint_Store(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
}

template<>
GINLINE greal &GSinglePoint_Store<1>::Y()
{
	return GGeometryGlobal::_g_n_coordinate_y_;
}

template<>
GINLINE greal GSinglePoint_Store<1>::Y() const
{
	return GGeometryGlobal::_g_n_coordinate_y_;
}

template<>
GINLINE greal &GSinglePoint_Store<1>::Z()
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
GINLINE greal GSinglePoint_Store<1>::Z() const
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
GINLINE gvoid GSinglePoint_Store<1>::SetY(greal y)
{
	
}

template<>
GINLINE gvoid GSinglePoint_Store<1>::SetZ(greal z)
{
	
}

//////////////////////////////////////////////////////////////////////////

template<>
GINLINE GSinglePoint_Store<2>::GSinglePoint_Store(greal x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
}

template<>
GINLINE GSinglePoint_Store<2>::GSinglePoint_Store(greal x, greal y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
GINLINE GSinglePoint_Store<2>::GSinglePoint_Store(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
GINLINE greal &GSinglePoint_Store<2>::Z()
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
GINLINE greal GSinglePoint_Store<2>::Z() const
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
GINLINE gvoid GSinglePoint_Store<2>::SetZ(greal z)
{

}

} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#endif // _GEOMETRY_SINGLE_POINT_STORE_INLINE_