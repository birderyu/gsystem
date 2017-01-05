#ifndef _GEOMETRY_POINT_2D_H_
#define _GEOMETRY_POINT_2D_H_

#include "CsGeometry.h"

class CS_API CsPoint2D
	: public CsGeometry
{
public:
	virtual ~CsPoint2D() = 0;

	virtual cs_real &X() = 0;
	virtual cs_real  X() const = 0;
	virtual cs_real &Y() = 0;
	virtual cs_real  Y() const = 0;

	virtual cs_void SetX(cs_real x) = 0;
	virtual cs_void SetY(cs_real y) = 0;
};

typedef CsPoint2D CsPoint;
typedef CsSharedPointer<CsPoint2D> CsPoint2DP;
typedef CsSharedPointer<CsPoint2D> CsPointP;

#endif // _GEOMETRY_POINT_2D_H_