#ifndef _GEOMETRY_CURVE_H_
#define _GEOMETRY_CURVE_H_

#include "CsGeometry.h"
#include "CsPoint.h"

class GAPI CsCurve
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsCurve
	**
	** @name	Length
	** @brief	获取当前几何对象的长度
	** @return	{cs_real} 长度值，默认单位为米
	**
	****************************************************************************/
	virtual greal Length() const = 0;

	virtual CsPointP StartPoint() = 0;
	virtual const CsPointP StartPoint() const = 0;
	virtual CsPointP EndPoint() = 0;
	virtual const CsPointP EndPoint() const = 0;

	virtual gsize PointCount() const = 0;
	virtual CsPointP GetPointAt(gsize pos) = 0;
	virtual const CsPointP GetPointAt(gsize pos) const = 0;
	virtual gvoid SetPointAt(gsize pos, const CsPointP &poi) = 0;

	// 是否闭合
	virtual gbool IsClosed() const = 0;
};

#endif // _GEOMETRY_CURVE_H_