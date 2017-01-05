#ifndef _GEOMETRY_SEGMENT_STORE_H_
#define _GEOMETRY_SEGMENT_STORE_H_

#include "CsGeometryGlobal.h"

class CsSegment_Store_2D
{
public:
	cs_bool Initialize();
	cs_bool Initialize(cs_real x, cs_real y);
	cs_bool Initialize(const CsSegment_Store_2D &);

	cs_real &StartX();
	cs_real  StartX() const;
	cs_real &StartY();
	cs_real  StartY() const;

	cs_real &EndX();
	cs_real  EndX() const;
	cs_real &EndY();
	cs_real  EndY() const;

	cs_void SetStartX(cs_real x);
	cs_void SetStartY(cs_real y);

	cs_void SetEndX(cs_real x);
	cs_void SetEndY(cs_real y);

private:
	cs_real m_tCoord[4];
};

#endif // _GEOMETRY_SEGMENT_STORE_H_