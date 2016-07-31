#ifndef _CSGEO_CSCOORDINATE_PRIVATE_H_
#define _CSGEO_CSCOORDINATE_PRIVATE_H_

#include "CsGeoGlobal.h"
#include "CsObject_Private.h"

class CsCoordinate;

class CsCoordinate_Private :public CsObject_Private
{
public:
	CsCoordinate_Private(CsCoordinate *pPublic);
	CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY);
#ifdef CS_GEO_HAS_Z
	CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY, const cs_real nZ);
#endif // CS_GEO_HAS_Z
	CsCoordinate_Private(CsCoordinate *pPublic, const CsCoordinate_Private &tCoord);
	~CsCoordinate_Private();

	cs_real GetX() const;
	cs_bool SetX(const cs_real nX);

	cs_real GetY() const;
	cs_bool SetY(const cs_real nY);

#ifdef CS_GEO_HAS_Z
	cs_real GetZ() const;
	cs_bool SetZ(const cs_real nZ);
#endif // CS_GEO_HAS_Z

private:
	cs_real m_X;
	cs_real m_Y;

#ifdef CS_GEO_HAS_Z
	cs_real m_Z;
#endif // CS_GEO_HAS_Z
};

#endif // _CSGEO_CSCOORDINATE_PRIVATE_H_