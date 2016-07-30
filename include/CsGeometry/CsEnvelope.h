#ifndef _CSGEO_CSENVELOPE_H_
#define _CSGEO_CSENVELOPE_H_

#include "CsGeoGlobal.h"
#include "CsObject.h"

class CsGeo_Export CsEnvelope :public CsObject
{
public:
	CsEnvelope();
	~CsEnvelope();
	CsString ToString() const;
};

#endif // _CSGEO_CSENVELOPE_H_