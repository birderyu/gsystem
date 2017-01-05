#include "CsCoordinate.h"
#include "CsNew.h"

#ifdef CS_GEOMETRY_HAS_Z
#	define CS_COORDINATE_X m_tCoord[0]
#	define CS_COORDINATE_Y m_tCoord[1]
#	define CS_COORDINATE_Z m_tCoord[2]
#else // !CS_GEOMETRY_HAS_Z
cs_real _cs_coordinate_z_ = 0;
#	define CS_COORDINATE_X m_tCoord[0]
#	define CS_COORDINATE_Y m_tCoord[1]
#	define CS_COORDINATE_Z CsGeometryGlobal::_g_n_coordinate_z_
#endif // CS_GEOMETRY_HAS_Z

CsCoordinate::CsCoordinate()
{
	CsMemSet(m_tCoord, 0, sizeof(cs_real)* CS_COORDINATE_SIZE);
}

CsCoordinate::CsCoordinate(cs_real x, cs_real y)
{
	CS_COORDINATE_X = x;
	CS_COORDINATE_Y = y;
	CS_COORDINATE_Z = 0;
}

CsCoordinate::CsCoordinate(cs_real x, cs_real y, cs_real z)
{
	CS_COORDINATE_X = x;
	CS_COORDINATE_Y = y;
	CS_COORDINATE_Z = z;
}

CsCoordinate::CsCoordinate(const cs_real *p_c, cs_size_t size)
{
	cs_size_t real_size = size < CS_COORDINATE_SIZE ? size : CS_COORDINATE_SIZE;
	CsMemCopy(m_tCoord, p_c, sizeof(cs_real)* real_size);
}

CsCoordinate::CsCoordinate(const CsCoordinate &coord)
{
	CsMemCopy(m_tCoord, coord.m_tCoord, sizeof(cs_real)* CS_COORDINATE_SIZE);
}

cs_real &CsCoordinate::X()
{
	return CS_COORDINATE_X;
}

cs_real CsCoordinate::X() const
{
	return CS_COORDINATE_X;
}

cs_real &CsCoordinate::Y()
{
	return CS_COORDINATE_Y;
}

cs_real CsCoordinate::Y() const
{
	return CS_COORDINATE_Y;
}

cs_real &CsCoordinate::Z()
{
	return CS_COORDINATE_Z;
}

cs_real CsCoordinate::Z() const
{
	return CS_COORDINATE_Z;
}

cs_void CsCoordinate::SetX(cs_real x)
{
	CS_COORDINATE_X = x;
}

cs_void CsCoordinate::SetY(cs_real y)
{
	CS_COORDINATE_Y = y;
}

cs_void CsCoordinate::SetZ(cs_real z)
{
	CS_COORDINATE_Z = z;
}

cs_uint CsCoordinate::Dimension() const
{
	return CS_COORDINATE_SIZE;
}

const cs_real * CsCoordinate::Cursor() const
{
	return m_tCoord;
}

#undef CS_COORDINATE_Z
#undef CS_COORDINATE_Y
#undef CS_COORDINATE_X