#ifndef _CSGEO_CSGEOMETRY_H_
#define _CSGEO_CSGEOMETRY_H_

#include "CsGeoGlobal.h"
#include "CsObject.h"

class CsGeometry_Private;
class CsEnvelope;

class CsGeo_Export CsGeometry :public CsObject
{
public:
	CsGeometry(CsGeometry_Private *pPrivate);
	virtual ~CsGeometry() = 0;
	//CsEnvelope GetEnvelope();
	//virtual EM_GEO_TYPE GetGeometryType();

public:
	enum { CLASSCODE = GEO_CLASSCODE_GEOMETRY, };
};

#endif // _CSGEO_CSGEOMETRY_H_