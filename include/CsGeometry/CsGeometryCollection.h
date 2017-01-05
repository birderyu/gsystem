#ifndef _GEOMETRY_GEOMETRY_COLLECTION_H_
#define _GEOMETRY_GEOMETRY_COLLECTION_H_

#include "CsGeometry.h"

class CS_API CsGeometryCollection
	: public CsGeometry
{
public:
	virtual ~CsGeometryCollection() = 0;

	/****************************************************************************
	**
	** CsGeometryCollection
	**
	** @name	Size
	** @brief	获取当前几何对象的数量
	** @return	{cs_size_t} 数量
	**
	****************************************************************************/
	virtual cs_size_t Size() const = 0;

	virtual CsGeometryP GetAt(cs_size_t pos) = 0;
	virtual const CsGeometryP GetAt(cs_size_t pos) const = 0;
	virtual cs_void SetAt(cs_size_t pos, const CsGeometryP &geo) = 0;
};

#endif // _GEOMETRY_GEOMETRY_COLLECTION_H_