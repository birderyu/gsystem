#include "genvelope.h"
#include "gcoordinate.h"
#include "gcoordinatesequence.h"
#include "GCore/gnew.h"

#ifdef G_GEOMETRY_HAS_Z
#	define G_ENVELOPE_MIN_X		m_tCoords[0]
#	define G_ENVELOPE_MIN_Y		m_tCoords[1]
#	define G_ENVELOPE_MIN_Z		m_tCoords[2]
#	define G_ENVELOPE_MAX_X		m_tCoords[3]
#	define G_ENVELOPE_MAX_Y		m_tCoords[4]
#	define G_ENVELOPE_MAX_Z		m_tCoords[5]
#	define G_ENVELOPE_CENTER_X ((m_tCoords[0] + m_tCoords[3]) / 2.0)
#	define G_ENVELOPE_CENTER_Y ((m_tCoords[1] + m_tCoords[4]) / 2.0)
#	define G_ENVELOPE_CENTER_Z ((m_tCoords[2] + m_tCoords[5]) / 2.0)
#	define G_ENVELOPE_LENGTH	(m_tCoords[3] - m_tCoords[0])
#	define G_ENVELOPE_WIDTH		(m_tCoords[4] - m_tCoords[1])
#	define G_ENVELOPE_HEIGHT	(m_tCoords[5] - m_tCoords[2])
#else // !G_GEOMETRY_HAS_Z
#	define G_ENVELOPE_MIN_X		m_tCoords[0]
#	define G_ENVELOPE_MIN_Y		m_tCoords[1]
#	define G_ENVELOPE_MIN_Z		GGeometryGlobal::_g_n_coordinate_z_
#	define G_ENVELOPE_MAX_X		m_tCoords[2]
#	define G_ENVELOPE_MAX_Y		m_tCoords[3]
#	define G_ENVELOPE_MAX_Z		GGeometryGlobal::_g_n_coordinate_z_
#	define G_ENVELOPE_CENTER_X	((m_tCoords[0] + m_tCoords[1]) / 2.0)
#	define G_ENVELOPE_CENTER_Y	((m_tCoords[2] + m_tCoords[3]) / 2.0)
#	define G_ENVELOPE_CENTER_Z	0
#	define G_ENVELOPE_LENGTH	(m_tCoords[1] - m_tCoords[0])
#	define G_ENVELOPE_WIDTH		(m_tCoords[3] - m_tCoords[2])
#	define G_ENVELOPE_HEIGHT	0
#endif // G_GEOMETRY_HAS_Z

GEnvelope::GEnvelope()
{
	GMemSet(m_tCoords, 0, sizeof(greal)* G_ENVELOPE_SIZE);
}

GEnvelope::GEnvelope(greal x, greal y)
{
	G_ENVELOPE_MIN_X = G_ENVELOPE_MAX_X = x;
	G_ENVELOPE_MIN_Y = G_ENVELOPE_MAX_Y = y;
	G_ENVELOPE_MIN_Z = G_ENVELOPE_MAX_Z = 0;
}

GEnvelope::GEnvelope(greal x, greal y, greal z)
{
	G_ENVELOPE_MIN_X = G_ENVELOPE_MAX_X = x;
	G_ENVELOPE_MIN_Y = G_ENVELOPE_MAX_Y = y;
	G_ENVELOPE_MIN_Z = G_ENVELOPE_MAX_Z = z;
}

GEnvelope::GEnvelope(greal min_x, greal min_y, greal max_x, greal max_y)
{
	G_ENVELOPE_MIN_X = min_x < max_x ? min_x : max_x;
	G_ENVELOPE_MIN_Y = min_y < max_y ? min_y : max_y;
	G_ENVELOPE_MAX_X = min_x > max_x ? min_x : max_x;
	G_ENVELOPE_MAX_Y = min_y > max_y ? min_y : max_y;
	G_ENVELOPE_MIN_Z = G_ENVELOPE_MAX_Z = 0;
}

GEnvelope::GEnvelope(greal min_x, greal min_y, greal min_z, greal max_x, greal max_y, greal max_z)
{
	G_ENVELOPE_MIN_X = min_x < max_x ? min_x : max_x;
	G_ENVELOPE_MIN_Y = min_y < max_y ? min_y : max_y;
	G_ENVELOPE_MIN_Z = min_z < max_z ? min_z : max_z;
	G_ENVELOPE_MAX_X = min_x > max_x ? min_x : max_x;
	G_ENVELOPE_MAX_Y = min_y > max_y ? min_y : max_y;
	G_ENVELOPE_MAX_Z = min_z > max_z ? min_z : max_z;
}

GEnvelope::GEnvelope(const GCoordinate &min_c, const GCoordinate &max_c)
{
	G_ENVELOPE_MIN_X = min_c.X() < max_c.X() ? min_c.X() : max_c.X();
	G_ENVELOPE_MIN_Y = min_c.Y() < max_c.Y() ? min_c.Y() : max_c.Y();
	G_ENVELOPE_MIN_Z = min_c.Z() < max_c.Z() ? min_c.Z() : max_c.Z();
	G_ENVELOPE_MAX_X = min_c.X() > max_c.X() ? min_c.X() : max_c.X();
	G_ENVELOPE_MAX_Y = min_c.Y() > max_c.Y() ? min_c.Y() : max_c.Y();
	G_ENVELOPE_MAX_Z = min_c.Z() > max_c.Z() ? min_c.Z() : max_c.Z();
}

GEnvelope::GEnvelope(const GCoordinateSequence &)
{

}

GEnvelope::GEnvelope(const GEnvelope &env)
{
	GMemCopy(m_tCoords, env.m_tCoords, sizeof(greal)* G_ENVELOPE_SIZE);
}

GCoordinate GEnvelope::Min() const
{
	return GCoordinate(G_ENVELOPE_MIN_X, G_ENVELOPE_MIN_Y, G_ENVELOPE_MIN_Z);
}

GCoordinate GEnvelope::Max() const
{
	return GCoordinate(G_ENVELOPE_MAX_X, G_ENVELOPE_MAX_Y, G_ENVELOPE_MAX_Z);
}

GCoordinate GEnvelope::Center() const
{
	return GCoordinate(G_ENVELOPE_CENTER_X, G_ENVELOPE_CENTER_Y, G_ENVELOPE_CENTER_Z);
}

greal GEnvelope::MinX() const
{
	return G_ENVELOPE_MIN_X;
}
greal GEnvelope::MinY() const
{
	return G_ENVELOPE_MIN_Y;
}

greal GEnvelope::MinZ() const
{
	return G_ENVELOPE_MIN_Z;
}

greal GEnvelope::MaxX() const
{
	return G_ENVELOPE_MAX_X;
}

greal GEnvelope::MaxY() const
{
	return G_ENVELOPE_MAX_Y;
}

greal GEnvelope::MaxZ() const
{
	return G_ENVELOPE_MAX_Z;
}

greal GEnvelope::CenterX() const
{
	return G_ENVELOPE_CENTER_X;
}

greal GEnvelope::CenterY() const
{
	return G_ENVELOPE_CENTER_Y;
}

greal GEnvelope::CenterZ() const
{
	return G_ENVELOPE_CENTER_Z;
}

greal GEnvelope::Length() const
{
	return G_ENVELOPE_LENGTH;
}

greal GEnvelope::Width() const
{
	return G_ENVELOPE_WIDTH;
}

greal GEnvelope::Height() const
{
	return G_ENVELOPE_HEIGHT;
}

gvoid GEnvelope::SetMin(const GCoordinate &c)
{
	G_ENVELOPE_MIN_X = c.X();
	G_ENVELOPE_MIN_Y = c.Y();
	G_ENVELOPE_MIN_Z = c.Z();
}

gvoid GEnvelope::SetMax(const GCoordinate &c)
{
	G_ENVELOPE_MAX_X = c.X();
	G_ENVELOPE_MAX_Y = c.Y();
	G_ENVELOPE_MAX_Z = c.Z();
}

gvoid GEnvelope::SetCenter(const GCoordinate &c)
{
	SetCenterX(c.X());
	SetCenterY(c.Y());
	SetCenterZ(c.Z());
}

gvoid GEnvelope::SetMinX(greal min_x)
{
	G_ENVELOPE_MIN_X = min_x;
}

gvoid GEnvelope::SetMinY(greal min_y)
{
	G_ENVELOPE_MIN_Y = min_y;
}

gvoid GEnvelope::SetMinZ(greal min_z)
{
	G_ENVELOPE_MIN_Z = min_z;
}

gvoid GEnvelope::SetMaxX(greal max_x)
{
	G_ENVELOPE_MAX_X = max_x;
}

gvoid GEnvelope::SetMaxY(greal max_y)
{
	G_ENVELOPE_MAX_Y = max_y;
}

gvoid GEnvelope::SetMaxZ(greal max_z)
{
	G_ENVELOPE_MAX_Z = max_z;
}

gvoid GEnvelope::SetCenterX(greal c_x)
{
	greal length = G_ENVELOPE_LENGTH;
	G_ENVELOPE_MAX_X = c_x + length / 2.0;
	G_ENVELOPE_MIN_X = c_x - length / 2.0;
}

gvoid GEnvelope::SetCenterY(greal c_y)
{
	greal width = G_ENVELOPE_WIDTH;
	G_ENVELOPE_MAX_Y = c_y + width / 2.0;
	G_ENVELOPE_MIN_Y = c_y - width / 2.0;
}

gvoid GEnvelope::SetCenterZ(greal c_z)
{
	greal height = G_ENVELOPE_HEIGHT;
	G_ENVELOPE_MAX_Z = c_z + height / 2.0;
	G_ENVELOPE_MIN_Z = c_z - height / 2.0;
}

gvoid GEnvelope::SetLength(greal l)
{
	greal center_x = G_ENVELOPE_CENTER_X;
	G_ENVELOPE_MAX_X = center_x + l / 2.0;
	G_ENVELOPE_MIN_X = center_x - l / 2.0;
}

gvoid GEnvelope::SetWidth(greal w)
{
	greal center_y = G_ENVELOPE_CENTER_X;
	G_ENVELOPE_MAX_Y = center_y + w / 2.0;
	G_ENVELOPE_MIN_Y = center_y - w / 2.0;
}

gvoid GEnvelope::SetHeight(greal h)
{
	greal center_z = G_ENVELOPE_CENTER_X;
	G_ENVELOPE_MAX_Y = center_z + h / 2.0;
	G_ENVELOPE_MIN_Y = center_z - h / 2.0;
}

guint GEnvelope::Dimension() const
{
	return G_ENVELOPE_SIZE / 2;
}

#undef G_ENVELOPE_HEIGHT
#undef G_ENVELOPE_WIDTH
#undef G_ENVELOPE_LENGTH
#undef G_ENVELOPE_CENTER_Z
#undef G_ENVELOPE_CENTER_Y
#undef G_ENVELOPE_CENTER_Z
#undef G_ENVELOPE_MAX_Z
#undef G_ENVELOPE_MAX_Y
#undef G_ENVELOPE_MAX_X
#undef G_ENVELOPE_MIN_Z
#undef G_ENVELOPE_MIN_Y
#undef G_ENVELOPE_MIN_X