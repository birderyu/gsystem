#ifndef _GEOMETRY_GEOMETRY_COLLECTION_H_
#define _GEOMETRY_GEOMETRY_COLLECTION_H_

#include "CsGeometry.h"

class CS_API CsGeometryCollection
	: public CsGeometry
{
public:
	virtual ~CsGeometryCollection() = 0;
};

#endif // _GEOMETRY_GEOMETRY_COLLECTION_H_