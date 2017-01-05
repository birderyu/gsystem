#ifndef _GEOMETRY_SINGLE_POINT_STORE_INLINE_
#define _GEOMETRY_SINGLE_POINT_STORE_INLINE_

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize()
{
	CsMemSet(m_aCoord, 0, sizeof(cs_real)* DIMENSION);
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize(cs_real x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
	m_aCoord[2] = 0;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize(cs_real x, cs_real y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = 0;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize(cs_real x, cs_real y, cs_real z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
	m_aCoord[2] = z;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize(const CsCoordinate &c)
{
	cs_size_t real_size = DIMENSION < CS_COORDINATE_SIZE ? DIMENSION : CS_COORDINATE_SIZE;
	CsMemCopy(m_aCoord, c.Cursor(), sizeof(cs_real)* real_size);
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::Initialize(const CsSinglePoint_Store<DIMENSION> &p_s)
{
	CsMemCopy(m_aCoord, p_s.m_aCoord, sizeof(cs_real)* DIMENSION);
}

template<cs_size_t DIMENSION>
inline cs_real &CsSinglePoint_Store<DIMENSION>::X()
{
	return m_aCoord[0];
}

template<cs_size_t DIMENSION>
inline cs_real CsSinglePoint_Store<DIMENSION>::X() const
{
	return m_aCoord[0];
}

template<cs_size_t DIMENSION>
inline cs_real &CsSinglePoint_Store<DIMENSION>::Y()
{
	return m_aCoord[1];
}

template<cs_size_t DIMENSION>
inline cs_real CsSinglePoint_Store<DIMENSION>::Y() const
{
	return m_aCoord[1];
}

template<cs_size_t DIMENSION>
inline cs_real &CsSinglePoint_Store<DIMENSION>::Z()
{
	return m_aCoord[2];
}

template<cs_size_t DIMENSION>
inline cs_real CsSinglePoint_Store<DIMENSION>::Z() const
{
	return m_aCoord[2];
}

template<cs_size_t DIMENSION>
inline CsCoordinate CsSinglePoint_Store<DIMENSION>::Coordinate() const
{
	return CsCoordinate(m_aCoord, DIMENSION);
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::SetX(cs_real x)
{
	m_aCoord[0] = x;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::SetY(cs_real y)
{
	m_aCoord[1] = y;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::SetZ(cs_real z)
{
	m_aCoord[2] = z;
}

template<cs_size_t DIMENSION>
inline cs_void CsSinglePoint_Store<DIMENSION>::SetCoordinate(const CsCoordinate &c)
{
	cs_size_t real_size = DIMENSION < CS_COORDINATE_SIZE ? DIMENSION : CS_COORDINATE_SIZE;
	CsMemCopy(m_aCoord, c.Cursor(), sizeof(cs_real)* real_size);
}

//////////////////////////////////////////////////////////////////////////

template<>
inline cs_void CsSinglePoint_Store<1>::Initialize(cs_real x)
{
	m_aCoord[0] = x;
}

template<>
inline cs_void CsSinglePoint_Store<1>::Initialize(cs_real x, cs_real y)
{
	m_aCoord[0] = x;
}

template<>
inline cs_void CsSinglePoint_Store<1>::Initialize(cs_real x, cs_real y, cs_real z)
{
	m_aCoord[0] = x;
}

template<>
inline cs_real &CsSinglePoint_Store<1>::Y()
{
	return CsGeometryGlobal::_g_n_coordinate_y_;
}

template<>
inline cs_real CsSinglePoint_Store<1>::Y() const
{
	return CsGeometryGlobal::_g_n_coordinate_y_;
}

template<>
inline cs_real &CsSinglePoint_Store<1>::Z()
{
	return CsGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline cs_real CsSinglePoint_Store<1>::Z() const
{
	return CsGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline cs_void CsSinglePoint_Store<1>::SetY(cs_real y)
{
	
}

template<>
inline cs_void CsSinglePoint_Store<1>::SetZ(cs_real z)
{
	
}

//////////////////////////////////////////////////////////////////////////

template<>
inline cs_void CsSinglePoint_Store<2>::Initialize(cs_real x)
{
	m_aCoord[0] = x;
	m_aCoord[1] = 0;
}

template<>
inline cs_void CsSinglePoint_Store<2>::Initialize(cs_real x, cs_real y)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
inline cs_void CsSinglePoint_Store<2>::Initialize(cs_real x, cs_real y, cs_real z)
{
	m_aCoord[0] = x;
	m_aCoord[1] = y;
}

template<>
inline cs_real &CsSinglePoint_Store<2>::Z()
{
	return CsGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline cs_real CsSinglePoint_Store<2>::Z() const
{
	return CsGeometryGlobal::_g_n_coordinate_z_;
}

template<>
inline cs_void CsSinglePoint_Store<2>::SetZ(cs_real z)
{

}

#endif // _GEOMETRY_SINGLE_POINT_STORE_INLINE_