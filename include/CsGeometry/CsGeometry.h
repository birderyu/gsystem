#ifndef _CSGEO_CSGEOMETRY_H_
#define _CSGEO_CSGEOMETRY_H_

#include "CsGeoGlobal.h"
#include "CsObject.h"

class CsEnvelope;

class CsGeo_Export CsGeometry :public CsObject
{
public:
	CsGeometry();
	virtual ~CsGeometry();
	//CsEnvelope GetEnvelope();

public:
	enum { CLASSCODE = GEO_CLASSCODE_GEOMETRY, };
};

#endif // _CSGEO_CSGEOMETRY_H_