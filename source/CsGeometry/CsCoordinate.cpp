#include "CsCoordinate.h"
#include "gnew.h"

#ifdef CS_GEOMETRY_HAS_Z
#	define CS_COORDINATE_X m_tCoord[0]
#	define CS_COORDINATE_Y m_tCoord[1]
#	define CS_COORDINATE_Z m_tCoord[2]
#else // !CS_GEOMETRY_HAS_Z
greal _cs_coordinate_z_ = 0;
#	define CS_COORDINATE_X m_tCoord[0]
#	define CS_COORDINATE_Y m_tCoord[1]
#	define CS_COORDINATE_Z CsGeometryGlobal::_g_n_coordinate_z_
#endif // CS_GEOMETRY_HAS_Z

CsCoordinate::CsCoordinate()
{
	GMemSet(m_tCoord, 0, sizeof(greal)* CS_COORDINATE_SIZE);
}

CsCoordinate::CsCoordinate(greal x, greal y)
{
	CS_COORDINATE_X = x;
	CS_COORDINATE_Y = y;
	CS_COORDINATE_Z = 0;
}

CsCoordinate::CsCoordinate(greal x, greal y, greal z)
{
	CS_COORDINATE_X = x;
	CS_COORDINATE_Y = y;
	CS_COORDINATE_Z = z;
}

CsCoordinate::CsCoordinate(const greal *p_c, gsize size)
{
	gsize real_size = size < CS_COORDINATE_SIZE ? size : CS_COORDINATE_SIZE;
	GMemCopy(m_tCoord, p_c, sizeof(greal)* real_size);
}

CsCoordinate::CsCoordinate(const CsCoordinate &coord)
{
	GMemCopy(m_tCoord, coord.m_tCoord, sizeof(greal)* CS_COORDINATE_SIZE);
}

greal &CsCoordinate::X()
{
	return CS_COORDINATE_X;
}

greal CsCoordinate::X() const
{
	return CS_COORDINATE_X;
}

greal &CsCoordinate::Y()
{
	return CS_COORDINATE_Y;
}

greal CsCoordinate::Y() const
{
	return CS_COORDINATE_Y;
}

greal &CsCoordinate::Z()
{
	return CS_COORDINATE_Z;
}

greal CsCoordinate::Z() const
{
	return CS_COORDINATE_Z;
}

gvoid CsCoordinate::SetX(greal x)
{
	CS_COORDINATE_X = x;
}

gvoid CsCoordinate::SetY(greal y)
{
	CS_COORDINATE_Y = y;
}

gvoid CsCoordinate::SetZ(greal z)
{
	CS_COORDINATE_Z = z;
}

guint CsCoordinate::Dimension() const
{
	return CS_COORDINATE_SIZE;
}

const greal * CsCoordinate::Cursor() const
{
	return m_tCoord;
}

#undef CS_COORDINATE_Z
#undef CS_COORDINATE_Y
#undef CS_COORDINATE_X