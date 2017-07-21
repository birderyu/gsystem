#include "gcoordinate.h"
#include "GCore/gnew.h"

#ifdef G_GEOMETRY_HAS_Z
#	define G_COORDINATE_X m_tCoord[0]
#	define G_COORDINATE_Y m_tCoord[1]
#	define G_COORDINATE_Z m_tCoord[2]
#else // !G_GEOMETRY_HAS_Z
greal _G_COORDINATE_z_ = 0;
#	define G_COORDINATE_X m_tCoord[0]
#	define G_COORDINATE_Y m_tCoord[1]
#	define G_COORDINATE_Z GGeometryGlobal::_g_n_coordinate_z_
#endif // G_GEOMETRY_HAS_Z

GCoordinate::GCoordinate()
{
	GMemSet(m_tCoord, 0, sizeof(greal)* G_COORDINATE_SIZE);
}

GCoordinate::GCoordinate(greal x, greal y)
{
	G_COORDINATE_X = x;
	G_COORDINATE_Y = y;
	G_COORDINATE_Z = 0;
}

GCoordinate::GCoordinate(greal x, greal y, greal z)
{
	G_COORDINATE_X = x;
	G_COORDINATE_Y = y;
	G_COORDINATE_Z = z;
}

GCoordinate::GCoordinate(const greal *p_c, gsize size)
{
	gsize real_size = size < G_COORDINATE_SIZE ? size : G_COORDINATE_SIZE;
	GMemCopy(m_tCoord, p_c, sizeof(greal)* real_size);
}

GCoordinate::GCoordinate(const GCoordinate &coord)
{
	GMemCopy(m_tCoord, coord.m_tCoord, sizeof(greal)* G_COORDINATE_SIZE);
}

greal &GCoordinate::X()
{
	return G_COORDINATE_X;
}

greal GCoordinate::X() const
{
	return G_COORDINATE_X;
}

greal &GCoordinate::Y()
{
	return G_COORDINATE_Y;
}

greal GCoordinate::Y() const
{
	return G_COORDINATE_Y;
}

greal &GCoordinate::Z()
{
	return G_COORDINATE_Z;
}

greal GCoordinate::Z() const
{
	return G_COORDINATE_Z;
}

gvoid GCoordinate::SetX(greal x)
{
	G_COORDINATE_X = x;
}

gvoid GCoordinate::SetY(greal y)
{
	G_COORDINATE_Y = y;
}

gvoid GCoordinate::SetZ(greal z)
{
	G_COORDINATE_Z = z;
}

guint GCoordinate::Dimension() const
{
	return G_COORDINATE_SIZE;
}

const greal * GCoordinate::Cursor() const
{
	return m_tCoord;
}

#undef G_COORDINATE_Z
#undef G_COORDINATE_Y
#undef G_COORDINATE_X