#ifndef _GEOMETRY_BODY_H_
#define _GEOMETRY_BODY_H_

#include "CsGeometry.h"

class GAPI CsBody
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsBody
	**
	** @name	Volume
	** @brief	获取当前几何对象的体积
	** @return	{cs_real} 体积值，默认单位为立方米
	**
	****************************************************************************/
	virtual greal Volume() const = 0;
};

#endif // _GEOMETRY_BODY_H_