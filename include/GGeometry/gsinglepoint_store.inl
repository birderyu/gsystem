#ifndef _GEOMETRY_SINGLE_POINT_STORE_INLINE_
#define _GEOMETRY_SINGLE_POINT_STORE_INLINE_

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize()
{
	GMemSet(m_aCoord, 0, sizeof(greal)* DIMENSION);
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize(greal x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
	m_aCoord[2] = 0;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize(greal x, greal y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = 0;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = z;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize(const GCoordinate &c)
{
	gsize real_size = DIMENSION < G_COORDINATE_SIZE ? DIMENSION : G_COORDINATE_SIZE;
	GMemCopy(m_aCoord, c.Cursor(), sizeof(greal)* real_size);
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::Initialize(const GSinglePoint_Store<DIMENSION> &p_s)
{
	GMemCopy(m_aCoord, p_s.m_aCoord, sizeof(greal)* DIMENSION);
}

template<gsize DIMENSION>
inline greal &GSinglePoint_Store<DIMENSION>::X()
{
	return m_aCoord[0];
}

template<gsize DIMENSION>
inline greal GSinglePoint_Store<DIMENSION>::X() const
{
	return m_aCoord[0];
}

template<gsize DIMENSION>
inline greal &GSinglePoint_Store<DIMENSION>::Y()
{
	return m_aCoord[1];
}

template<gsize DIMENSION>
inline greal GSinglePoint_Store<DIMENSION>::Y() const
{
	return m_aCoord[1];
}

template<gsize DIMENSION>
inline greal &GSinglePoint_Store<DIMENSION>::Z()
{
	return m_aCoord[2];
}

template<gsize DIMENSION>
inline greal GSinglePoint_Store<DIMENSION>::Z() const
{
	return m_aCoord[2];
}

template<gsize DIMENSION>
inline GCoordinate GSinglePoint_Store<DIMENSION>::Coordinate() const
{
	return GCoordinate(m_aCoord, DIMENSION);
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::SetX(greal x)
{
	m_aCoord[0] = x;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::SetY(greal y)
{
	m_aCoord[1] = y;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::SetZ(greal z)
{
	m_aCoord[2] = z;
}

template<gsize DIMENSION>
inline gvoid GSinglePoint_Store<DIMENSION>::SetCoordinate(const GCoordinate &c)
{
	gsize real_size = DIMENSION < G_COORDINATE_SIZE ? DIMENSION : G_COORDINATE_SIZE;
	GMemCopy(m_aCoord, c.Cursor(), sizeof(greal)* real_size);
}

//////////////////////////////////////////////////////////////////////////

template<>
inline gvoid GSinglePoint_Store<1>::Initialize(greal x)
{
	m_aCoord[0] = x;
}

template<>
inline gvoid GSinglePoint_Store<1>::Initialize(greal x, greal y)
{
	m_aCoord[0] = x;
}

template<>
inline gvoid GSinglePoint_Store<1>::Initialize(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
}

template<>
inline greal &GSinglePoint_Store<1>::Y()
{
	return GGeometryGlobal::_g_n_coordinate_y_;
}

template<>
inline greal GSinglePoint_Store<1>::Y() const
{
	return GGeometryGlobal::_g_n_coordinate_y_;
}

template<>
inline greal &GSinglePoint_Store<1>::Z()
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline greal GSinglePoint_Store<1>::Z() const
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline gvoid GSinglePoint_Store<1>::SetY(greal y)
{
	
}

template<>
inline gvoid GSinglePoint_Store<1>::SetZ(greal z)
{
	
}

//////////////////////////////////////////////////////////////////////////

template<>
inline gvoid GSinglePoint_Store<2>::Initialize(greal x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
}

template<>
inline gvoid GSinglePoint_Store<2>::Initialize(greal x, greal y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
inline gvoid GSinglePoint_Store<2>::Initialize(greal x, greal y, greal z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
inline greal &GSinglePoint_Store<2>::Z()
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline greal GSinglePoint_Store<2>::Z() const
{
	return GGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline gvoid GSinglePoint_Store<2>::SetZ(greal z)
{

}

#endif // _GEOMETRY_SINGLE_POINT_STORE_INLINE_