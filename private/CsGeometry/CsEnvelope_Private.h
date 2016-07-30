#ifndef _CSGEO_CSENVELOPE_PRIVATE_H_
#define _CSGEO_CSENVELOPE_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsCoordinate.h"
class CsEnvelope;

class CsEnvelope_Private :public CsObject_Private
{
public:
	CsEnvelope_Private(CsEnvelope *pPublic);
	~CsEnvelope_Private();
	cs_real GetLength() const;
	cs_real GetWidth() const;
	cs_real GetHeight() const;

private:
	CsCoordinate m_tLeftTop;
	CsCoordinate m_tRightBottom;
};

#endif // _CSGEO_CSENVELOPE_PRIVATE_H_