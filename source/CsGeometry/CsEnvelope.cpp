#include "CsEnvelope.h"
#include "CsCoordinate.h"
#include "CsCoordinateSequence.h"
#include "CsNew.h"

#ifdef CS_GEOMETRY_COORDINATE_HAS_Z
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
#else // !CS_GEOMETRY_COORDINATE_HAS_Z
cs_real _cs_envelope_min_max_z_ = 0;
cs_real _cs_envelope_center_z_ = 0;
cs_real _cs_envelope_height_ = 0;
#	define CS_ENVELOPE_MIN_X	m_tCoords[0]
#	define CS_ENVELOPE_MIN_Y	m_tCoords[1]
#	define CS_ENVELOPE_MIN_Z	_cs_envelope_min_max_z_
#	define CS_ENVELOPE_MAX_X	m_tCoords[2]
#	define CS_ENVELOPE_MAX_Y	m_tCoords[3]
#	define CS_ENVELOPE_MAX_Z	_cs_envelope_min_max_z_
#	define CS_ENVELOPE_CENTER_X ((m_tCoords[0] + m_tCoords[1]) / 2.0)
#	define CS_ENVELOPE_CENTER_Y ((m_tCoords[2] + m_tCoords[3]) / 2.0)
#	define CS_ENVELOPE_CENTER_Z 0
#	define CS_ENVELOPE_LENGTH	(m_tCoords[1] - m_tCoords[0])
#	define CS_ENVELOPE_WIDTH	(m_tCoords[3] - m_tCoords[2])
#	define CS_ENVELOPE_HEIGHT	0
#endif // CS_GEOMETRY_COORDINATE_HAS_Z

CsEnvelope::CsEnvelope()
{
	CsMemSet(m_tCoords, 0, sizeof(cs_real)* CS_ENVELOPE_SIZE);
}

CsEnvelope::CsEnvelope(cs_real x, cs_real y)
{
	CS_ENVELOPE_MIN_X = CS_ENVELOPE_MAX_X = x;
	CS_ENVELOPE_MIN_Y = CS_ENVELOPE_MAX_Y = y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = 0;
}

CsEnvelope::CsEnvelope(cs_real x, cs_real y, cs_real z)
{
	CS_ENVELOPE_MIN_X = CS_ENVELOPE_MAX_X = x;
	CS_ENVELOPE_MIN_Y = CS_ENVELOPE_MAX_Y = y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = z;
}

CsEnvelope::CsEnvelope(cs_real min_x, cs_real min_y, cs_real max_x, cs_real max_y)
{
	CS_ENVELOPE_MIN_X = min_x < max_x ? min_x : max_x;
	CS_ENVELOPE_MIN_Y = min_y < max_y ? min_y : max_y;
	CS_ENVELOPE_MAX_X = min_x > max_x ? min_x : max_x;
	CS_ENVELOPE_MAX_Y = min_y > max_y ? min_y : max_y;
	CS_ENVELOPE_MIN_Z = CS_ENVELOPE_MAX_Z = 0;
}

CsEnvelope::CsEnvelope(cs_real min_x, cs_real min_y, cs_real min_z, cs_real max_x, cs_real max_y, cs_real max_z)
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
	CsMemCopy(m_tCoords, env.m_tCoords, sizeof(cs_real)* CS_ENVELOPE_SIZE);
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

cs_real CsEnvelope::MinX() const
{
	return CS_ENVELOPE_MIN_X;
}
cs_real CsEnvelope::MinY() const
{
	return CS_ENVELOPE_MIN_Y;
}

cs_real CsEnvelope::MinZ() const
{
	return CS_ENVELOPE_MIN_Z;
}

cs_real CsEnvelope::MaxX() const
{
	return CS_ENVELOPE_MAX_X;
}

cs_real CsEnvelope::MaxY() const
{
	return CS_ENVELOPE_MAX_Y;
}

cs_real CsEnvelope::MaxZ() const
{
	return CS_ENVELOPE_MAX_Z;
}

cs_real CsEnvelope::CenterX() const
{
	return CS_ENVELOPE_CENTER_X;
}

cs_real CsEnvelope::CenterY() const
{
	return CS_ENVELOPE_CENTER_Y;
}

cs_real CsEnvelope::CenterZ() const
{
	return CS_ENVELOPE_CENTER_Z;
}

cs_real CsEnvelope::Length() const
{
	return CS_ENVELOPE_LENGTH;
}

cs_real CsEnvelope::Width() const
{
	return CS_ENVELOPE_WIDTH;
}

cs_real CsEnvelope::Height() const
{
	return CS_ENVELOPE_HEIGHT;
}

cs_void CsEnvelope::SetMin(const CsCoordinate &c)
{
	CS_ENVELOPE_MIN_X = c.X();
	CS_ENVELOPE_MIN_Y = c.Y();
	CS_ENVELOPE_MIN_Z = c.Z();
}

cs_void CsEnvelope::SetMax(const CsCoordinate &c)
{
	CS_ENVELOPE_MAX_X = c.X();
	CS_ENVELOPE_MAX_Y = c.Y();
	CS_ENVELOPE_MAX_Z = c.Z();
}

cs_void CsEnvelope::SetCenter(const CsCoordinate &c)
{
	SetCenterX(c.X());
	SetCenterY(c.Y());
	SetCenterZ(c.Z());
}

cs_void CsEnvelope::SetMinX(cs_real min_x)
{
	CS_ENVELOPE_MIN_X = min_x;
}

cs_void CsEnvelope::SetMinY(cs_real min_y)
{
	CS_ENVELOPE_MIN_Y = min_y;
}

cs_void CsEnvelope::SetMinZ(cs_real min_z)
{
	CS_ENVELOPE_MIN_Z = min_z;
}

cs_void CsEnvelope::SetMaxX(cs_real max_x)
{
	CS_ENVELOPE_MAX_X = max_x;
}

cs_void CsEnvelope::SetMaxY(cs_real max_y)
{
	CS_ENVELOPE_MAX_Y = max_y;
}

cs_void CsEnvelope::SetMaxZ(cs_real max_z)
{
	CS_ENVELOPE_MAX_Z = max_z;
}

cs_void CsEnvelope::SetCenterX(cs_real c_x)
{
	cs_real length = CS_ENVELOPE_LENGTH;
	CS_ENVELOPE_MAX_X = c_x + length / 2.0;
	CS_ENVELOPE_MIN_X = c_x - length / 2.0;
}

cs_void CsEnvelope::SetCenterY(cs_real c_y)
{
	cs_real width = CS_ENVELOPE_WIDTH;
	CS_ENVELOPE_MAX_Y = c_y + width / 2.0;
	CS_ENVELOPE_MIN_Y = c_y - width / 2.0;
}

cs_void CsEnvelope::SetCenterZ(cs_real c_z)
{
	cs_real height = CS_ENVELOPE_HEIGHT;
	CS_ENVELOPE_MAX_Z = c_z + height / 2.0;
	CS_ENVELOPE_MIN_Z = c_z - height / 2.0;
}

cs_void CsEnvelope::SetLength(cs_real l)
{
	cs_real center_x = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_X = center_x + l / 2.0;
	CS_ENVELOPE_MIN_X = center_x - l / 2.0;
}

cs_void CsEnvelope::SetWidth(cs_real w)
{
	cs_real center_y = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_Y = center_y + w / 2.0;
	CS_ENVELOPE_MIN_Y = center_y - w / 2.0;
}

cs_void CsEnvelope::SetHeight(cs_real h)
{
	cs_real center_z = CS_ENVELOPE_CENTER_X;
	CS_ENVELOPE_MAX_Y = center_z + h / 2.0;
	CS_ENVELOPE_MIN_Y = center_z - h / 2.0;
}

cs_uint CsEnvelope::Dimension() const
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