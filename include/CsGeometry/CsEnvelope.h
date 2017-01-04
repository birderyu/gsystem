// 几何外包
#ifndef _GEOMETRY_ENVELOPE_H_
#define _GEOMETRY_ENVELOPE_H_
// 注意：坐标结构中存储了Z值，对于仅用于二维的数据场景，会有大量的数据冗余
// 因此，该结构只能作为一个传输结构，不能作为存储结构。

#include "CsGeometryGlobal.h"
#include "CsObject.h"

class CsCoordinate;
class CsCoordinateSequence;

class CS_API CsEnvelope
	: public CsObject
{
public:
	CsEnvelope();
	CsEnvelope(cs_real x, cs_real y);
	CsEnvelope(cs_real x, cs_real y, cs_real z);
	CsEnvelope(cs_real min_x, cs_real min_y, cs_real max_x, cs_real max_y);
	CsEnvelope(cs_real min_x, cs_real min_y, cs_real min_z, cs_real max_x, cs_real max_y, cs_real max_z);
	CsEnvelope(const CsCoordinate &min_c, const CsCoordinate &max_c);
	CsEnvelope(const CsCoordinateSequence &);
	CsEnvelope(const CsEnvelope &);

	CsCoordinate Min() const;
	CsCoordinate Max() const;
	CsCoordinate Center() const;

	cs_real MinX() const;
	cs_real MinY() const;
	cs_real MinZ() const;

	cs_real MaxX() const;
	cs_real MaxY() const;
	cs_real MaxZ() const;

	cs_real CenterX() const;
	cs_real CenterY() const;
	cs_real CenterZ() const;

	cs_real Length() const;
	cs_real Width() const;
	cs_real Height() const;

	cs_void SetMin(const CsCoordinate &);
	cs_void SetMax(const CsCoordinate &);
	cs_void SetCenter(const CsCoordinate &);

	cs_void SetMinX(cs_real);
	cs_void SetMinY(cs_real);
	cs_void SetMinZ(cs_real);

	cs_void SetMaxX(cs_real);
	cs_void SetMaxY(cs_real);
	cs_void SetMaxZ(cs_real);

	cs_void SetCenterX(cs_real);
	cs_void SetCenterY(cs_real);
	cs_void SetCenterZ(cs_real);

	cs_void SetLength(cs_real);
	cs_void SetWidth(cs_real);
	cs_void SetHeight(cs_real);

	cs_uint Dimension() const;

private:
	// MinX, MinY(, MinZ), MaxX, MaxY(, MaxZ)
	cs_real m_tCoords[CS_ENVELOPE_SIZE];
};

#endif // _GEOMETRY_ENVELOPE_H_