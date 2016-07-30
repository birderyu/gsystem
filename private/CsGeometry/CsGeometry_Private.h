#ifndef _CSGEO_CSGEOMETRY_PRIVATE_H_
#define _CSGEO_CSGEOMETRY_PRIVATE_H_

#include "CsObject_Private.h"
class CsGeometry;
class CsEnvelope;

class CsGeometry_Private :public CsObject_Private
{
public:
	CsGeometry_Private(CsGeometry *pPublic);
	virtual ~CsGeometry_Private();
};

#endif // _CSGEO_CSGEOMETRY_PRIVATE_H_