#ifndef _GEOMETRY_SURFACE_H_
#define _GEOMETRY_SURFACE_H_

#include "CsGeometry.h"

class CS_API CsSurface
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsSurface
	**
	** @name	Area
	** @brief	获取当前几何对象的面积
	** @return	{cs_real} 面积值，默认单位为平方米
	**
	****************************************************************************/
	virtual cs_real Area() const = 0;
};

#endif // _GEOMETRY_SURFACE_H_