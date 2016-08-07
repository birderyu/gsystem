#ifndef _CSGEO_CSENVELOPE_PRIVATE_H_
#define _CSGEO_CSENVELOPE_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsCoord.h"
class CsEnvelope;

class CsEnvelope_Private :public CsObject_Private
{
public:
	CsEnvelope_Private(CsEnvelope *pPublic);
	~CsEnvelope_Private();
	cs_real GetLength() const;
	cs_real GetWidth() const;
#ifdef CS_GEO_HAS_Z
	cs_real GetHeight() const;
#endif // CS_GEO_HAS_Z

	cs_bool Union(CsEnvelope_Private *pEnvelope);
	cs_bool Intersection(CsEnvelope_Private *pEnvelope);

private:
	CsCoordinate m_tMax;
	CsCoordinate m_tMin;
};

#endif // _CSGEO_CSENVELOPE_PRIVATE_H_