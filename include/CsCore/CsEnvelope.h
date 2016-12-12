// 几何外包
#ifndef _CORE_ENVELOPE_H_
#define _CORE_ENVELOPE_H_

#include "CsGeometry.h"
#include "CsCoordinate.h"

class CS_API CsEnvelope
{
public:
	CsEnvelope();

	CsCoordinate Max() const;
	CsCoordinate Min() const;
	CsCoordinate Center() const;

	cs_real MaxX() const;
	cs_real MaxY() const;

	cs_real MinX() const;
	cs_real MinY() const;

	cs_real CenterX() const;
	cs_real CenterY() const;

	cs_real Length() const;
	cs_real Width() const;

	cs_void SetMax(const CsCoordinate &) const;
	cs_void SetMin(const CsCoordinate &) const;
	cs_void SetCenter(const CsCoordinate &) const;

	cs_void SetMaxX(cs_real);
	cs_void SetMaxY(cs_real);

	cs_void SetMinX(cs_real);
	cs_void SetMinY(cs_real);

	cs_void SetCenterX(cs_real);
	cs_void SetCenterY(cs_real);

	cs_void SetLength(cs_real);
	cs_void SetWidth(cs_real);

private:
	// MinX, MinY, MaxX, MaxY
	cs_real m_tMinCoord[4];
};

#endif // _CORE_ENVELOPE_H_