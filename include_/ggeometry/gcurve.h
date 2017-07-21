#ifndef _GEOMETRY_CURVE_H_
#define _GEOMETRY_CURVE_H_

#include "ggeometry.h"
#include "gpoint.h"

class GAPI GCurve
	: virtual public GGeometry
{
public:
	/****************************************************************************
	**
	** GCurve
	**
	** @name	Length
	** @brief	获取当前几何对象的长度
	** @return	{greal} 长度值，默认单位为米
	**
	****************************************************************************/
	virtual greal Length() const = 0;

	virtual GPointPtr StartPoint() = 0;
	virtual const GPointPtr StartPoint() const = 0;
	virtual GPointPtr EndPoint() = 0;
	virtual const GPointPtr EndPoint() const = 0;

	virtual gsize PointCount() const = 0;
	virtual GPointPtr GetPointAt(gsize pos) = 0;
	virtual const GPointPtr GetPointAt(gsize pos) const = 0;
	virtual gvoid SetPointAt(gsize pos, const GPointPtr &poi) = 0;

	// 是否闭合
	virtual gbool IsClosed() const = 0;
};

#endif // _GEOMETRY_CURVE_H_