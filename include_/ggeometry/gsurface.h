#ifndef _GEOMETRY_SURFACE_H_
#define _GEOMETRY_SURFACE_H_

#include "ggeometry.h"

class GAPI GSurface
	: virtual public GGeometry
{
public:
	/****************************************************************************
	**
	** GSurface
	**
	** @name	Area
	** @brief	获取当前几何对象的面积
	** @return	{greal} 面积值，默认单位为平方米
	**
	****************************************************************************/
	virtual greal Area() const = 0;
};

#endif // _GEOMETRY_SURFACE_H_