#ifndef _GEOMETRY_POINT_H_
#define _GEOMETRY_POINT_H_

#include "CsGeometry.h"

class CS_API CsPoint
	: virtual public CsGeometry
{
public:
	virtual ~CsPoint() = 0;

	virtual cs_real &X() = 0;
	virtual cs_real  X() const = 0;
	virtual cs_real &Y() = 0;
	virtual cs_real  Y() const = 0;
	virtual cs_real &Z() = 0;
	virtual cs_real  Z() const = 0;

	virtual cs_void SetX(cs_real x) = 0;
	virtual cs_void SetY(cs_real y) = 0;
	virtual cs_void SetZ(cs_real z) = 0;
};

typedef CsSharedPointer<CsPoint> CsPointP;

#endif // _GEOMETRY_POINT_H_