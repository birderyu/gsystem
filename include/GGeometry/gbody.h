#ifndef _GEOMETRY_BODY_H_
#define _GEOMETRY_BODY_H_

#include "ggeometry.h"

class GAPI GBody
	: virtual public GGeometry
{
public:
	/****************************************************************************
	**
	** GBody
	**
	** @name	Volume
	** @brief	获取当前几何对象的体积
	** @return	{greal} 体积值，默认单位为立方米
	**
	****************************************************************************/
	virtual greal Volume() const = 0;
};

#endif // _GEOMETRY_BODY_H_