#include "CsEnvelope.h"
#include "CsCoordinate.h"
#include "CsCoordinateSequence.h"
#include "GCore/gnew.h"

#ifdef CS_GEOMETRY_HAS_Z
#	define CS_ENVELOPE_MIN_X	m_tCoords[0]
#	define CS_ENVELOPE_MIN_Y	m_tCoords[1]
#	define CS_ENVELOPE_MIN_Z	m_tCoords[2]
#	define CS_ENVELOPE_MAX_X	m_tCoords[3]
#	define CS_ENVELOPE_MAX_Y	m_tCoords[4]
#	define CS_ENVELOPE_MAX_Z	m_tCoords[5]
#	define CS_ENVELOPE_CENTER_X ((m_tCoords[0] + m_tCoords[3]) / 2.0)
#	define CS_ENVELOPE_CENTER_Y ((m_tCoords[1] + m_tCoords[4]) / 2.0)
#	define CS_ENVELOPE_CENTER_Z ((m_tCoords[2] + m_tCoords[5]) / 2.0)
#	define CS_ENVELOPE_LENGTH	(m_tCoords[3] - m_tCoords[0])
#	define CS_ENVELOPE_WIDTH	(m_tCoords[4] - m_tCoords[1])
#	define CS_ENVELOPE_HEIGHT	(m_tCoords[5] - m_tCoords[2])
#else // !CS_GEOMETRY_HAS_Z
#	define CS_ENVELOPE_MIN_X	m_tCoords[0]
#	define CS_ENVELOPE_MIN_Y	m_tCoords[1]
#	define CS_ENVELOPE_MIN_Z	CsGeometryGlobal::_g_n_coordinate_z_
#	define CS_ENVELOPE_MAX_X	m_tCoords[2]
#	define CS_ENVELOPE_MAX_Y	m_tCoords[3]
#	define CS_ENVELOPE_MAX_Z	CsGeometryGlobal::_g_n_coordinate_z_
#	define CS_ENVELOPE_CENTER_X ((m_tCoords[0] + m_tCoords[1]) / 2.0)
#	define CS_ENVELOPE_CENTER_Y ((m_tCoords[2] + m_tCoords[3]) / 2.0)
#	define CS_ENVELOPE_CENTER_Z 0
#	define CS_ENVELOPE_LENGTH	(m_tCoords[1] - m_tCoords[0])
#	define CS_ENVELOPE_WIDTH	(m_tCoords[3] - m_tCoords[2])
#	define CS_ENVELOPE_HEIGHT	0
#endif // CS_GEOMETRY_HAS_Z

CsEnvelope::CsEnvelope()
{
	GMemSet(m_tCoords, 0, sizeof(greal)* CS_ENVELOPE_SIZE);
}

CsEnvelope::CsEnvelope(greal x, greal y)
{
	CS_ENVELOPE_MIN_X = CS_ENVELOPE_MAX_X = x;
	CS_ENVELOPE_MIN_Y = CS_ENVELOPE_MAX_Y = y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = 0;
}

CsEnvelope::CsEnvelope(greal x, greal y, greal z)
{
	CS_ENVELOPE_MIN_X = CS_ENVELOPE_MAX_X = x;
	CS_ENVELOPE_MIN_Y = CS_ENVELOPE_MAX_Y = y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = z;
}

CsEnvelope::CsEnvelope(greal min_x, greal min_y, greal max_x, greal max_y)
{
	CS_ENVELOPE_MIN_X = min_x < max_x ? min_x : max_x;
	CS_ENVELOPE_MIN_Y = min_y < max_y ? min_y : max_y;
	CS_ENVELOPE_MAX_X = min_x > max_x ? min_x : max_x;
	CS_ENVELOPE_MAX_Y = min_y > max_y ? min_y : max_y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = 0;
}

CsEnvelope::CsEnvelope(greal min_x, greal min_y, greal min_z, greal max_x, greal max_y, greal max_z)
{
	CS_ENVELOPE_MIN_X = min_x < max_x ? min_x : max_x;
	CS_ENVELOPE_MIN_Y = min_y < max_y ? min_y : max_y;
	CS_ENVELOPE_MIN_Z = min_z < max_z ? min_z : max_z;
	CS_ENVELOPE_MAX_X = min_x > max_x ? min_x : max_x;
	CS_ENVELOPE_MAX_Y = min_y > max_y ? min_y : max_y;
	CS_ENVELOPE_MAX_Z = min_z > max_z ? min_z : max_z;
}

CsEnvelope::CsEnvelope(const CsCoordinate &min_c, const CsCoordinate &max_c)
{
	CS_ENVELOPE_MIN_X = min_c.X() < max_c.X() ? min_c.X() : max_c.X();
	CS_ENVELOPE_MIN_Y = min_c.Y() < max_c.Y() ? min_c.Y() : max_c.Y();
	CS_ENVELOPE_MIN_Z = min_c.Z() < max_c.Z() ? min_c.Z() : max_c.Z();
	CS_ENVELOPE_MAX_X = min_c.X() > max_c.X() ? min_c.X() : max_c.X();
	CS_ENVELOPE_MAX_Y = min_c.Y() > max_c.Y() ? min_c.Y() : max_c.Y();
	CS_ENVELOPE_MAX_Z = min_c.Z() > max_c.Z() ? min_c.Z() : max_c.Z();
}

CsEnvelope::CsEnvelope(const CsCoordinateSequence &)
{

}

CsEnvelope::CsEnvelope(const CsEnvelope &env)
{
	GMemCopy(m_tCoords, env.m_tCoords, sizeof(greal)* CS_ENVELOPE_SIZE);
}

CsCoordinate CsEnvelope::Min() const
{
	return CsCoordinate(CS_ENVELOPE_MIN_X, CS_ENVELOPE_MIN_Y, CS_ENVELOPE_MIN_Z);
}

CsCoordinate CsEnvelope::Max() const
{
	return CsCoordinate(CS_ENVELOPE_MAX_X, CS_ENVELOPE_MAX_Y, CS_ENVELOPE_MAX_Z);
}

CsCoordinate CsEnvelope::Center() const
{
	return CsCoordinate(CS_ENVELOPE_CENTER_X, CS_ENVELOPE_CENTER_Y, CS_ENVELOPE_CENTER_Z);
}

greal CsEnvelope::MinX() const
{
	return CS_ENVELOPE_MIN_X;
}
greal CsEnvelope::MinY() const
{
	return CS_ENVELOPE_MIN_Y;
}

greal CsEnvelope::MinZ() const
{
	return CS_ENVELOPE_MIN_Z;
}

greal CsEnvelope::MaxX() const
{
	return CS_ENVELOPE_MAX_X;
}

greal CsEnvelope::MaxY() const
{
	return CS_ENVELOPE_MAX_Y;
}

greal CsEnvelope::MaxZ() const
{
	return CS_ENVELOPE_MAX_Z;
}

greal CsEnvelope::CenterX() const
{
	return CS_ENVELOPE_CENTER_X;
}

greal CsEnvelope::CenterY() const
{
	return CS_ENVELOPE_CENTER_Y;
}

greal CsEnvelope::CenterZ() const
{
	return CS_ENVELOPE_CENTER_Z;
}

greal CsEnvelope::Length() const
{
	return CS_ENVELOPE_LENGTH;
}

greal CsEnvelope::Width() const
{
	return CS_ENVELOPE_WIDTH;
}

greal CsEnvelope::Height() const
{
	return CS_ENVELOPE_HEIGHT;
}

gvoid CsEnvelope::SetMin(const CsCoordinate &c)
{
	CS_ENVELOPE_MIN_X = c.X();
	CS_ENVELOPE_MIN_Y = c.Y();
	CS_ENVELOPE_MIN_Z = c.Z();
}

gvoid CsEnvelope::SetMax(const CsCoordinate &c)
{
	CS_ENVELOPE_MAX_X = c.X();
	CS_ENVELOPE_MAX_Y = c.Y();
	CS_ENVELOPE_MAX_Z = c.Z();
}

gvoid CsEnvelope::SetCenter(const CsCoordinate &c)
{
	SetCenterX(c.X());
	SetCenterY(c.Y());
	SetCenterZ(c.Z());
}

gvoid CsEnvelope::SetMinX(greal min_x)
{
	CS_ENVELOPE_MIN_X = min_x;
}

gvoid CsEnvelope::SetMinY(greal min_y)
{
	CS_ENVELOPE_MIN_Y = min_y;
}

gvoid CsEnvelope::SetMinZ(greal min_z)
{
	CS_ENVELOPE_MIN_Z = min_z;
}

gvoid CsEnvelope::SetMaxX(greal max_x)
{
	CS_ENVELOPE_MAX_X = max_x;
}

gvoid CsEnvelope::SetMaxY(greal max_y)
{
	CS_ENVELOPE_MAX_Y = max_y;
}

gvoid CsEnvelope::SetMaxZ(greal max_z)
{
	CS_ENVELOPE_MAX_Z = max_z;
}

gvoid CsEnvelope::SetCenterX(greal c_x)
{
	greal length = CS_ENVELOPE_LENGTH;
	CS_ENVELOPE_MAX_X = c_x + length / 2.0;
	CS_ENVELOPE_MIN_X = c_x - length / 2.0;
}

gvoid CsEnvelope::SetCenterY(greal c_y)
{
	greal width = CS_ENVELOPE_WIDTH;
	CS_ENVELOPE_MAX_Y = c_y + width / 2.0;
	CS_ENVELOPE_MIN_Y = c_y - width / 2.0;
}

gvoid CsEnvelope::SetCenterZ(greal c_z)
{
	greal height = CS_ENVELOPE_HEIGHT;
	CS_ENVELOPE_MAX_Z = c_z + height / 2.0;
	CS_ENVELOPE_MIN_Z = c_z - height / 2.0;
}

gvoid CsEnvelope::SetLength(greal l)
{
	greal center_x = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_X = center_x + l / 2.0;
	CS_ENVELOPE_MIN_X = center_x - l / 2.0;
}

gvoid CsEnvelope::SetWidth(greal w)
{
	greal center_y = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_Y = center_y + w / 2.0;
	CS_ENVELOPE_MIN_Y = center_y - w / 2.0;
}

gvoid CsEnvelope::SetHeight(greal h)
{
	greal center_z = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_Y = center_z + h / 2.0;
	CS_ENVELOPE_MIN_Y = center_z - h / 2.0;
}

guint CsEnvelope::Dimension() const
{
	return CS_ENVELOPE_SIZE / 2;
}

#undef CS_ENVELOPE_HEIGHT
#undef CS_ENVELOPE_WIDTH
#undef CS_ENVELOPE_LENGTH
#undef CS_ENVELOPE_CENTER_Z
#undef CS_ENVELOPE_CENTER_Y
#undef CS_ENVELOPE_CENTER_Z
#undef CS_ENVELOPE_MAX_Z
#undef CS_ENVELOPE_MAX_Y
#undef CS_ENVELOPE_MAX_X
#undef CS_ENVELOPE_MIN_Z
#undef CS_ENVELOPE_MIN_Y
#undef CS_ENVELOPE_MIN_X