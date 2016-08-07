#include "CsCoord_Private.h"
#include "CsCoord.h"

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic)
: CsObject_Private(pPublic), m_X(0), m_Y(0)
#ifdef CS_GEO_HAS_Z
, m_Z(0)
#endif // CS_GEO_HAS_Z
{

}

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY)
: CsObject_Private(pPublic), m_X(nX), m_Y(nY)
#ifdef CS_GEO_HAS_Z
, m_Z(0)
#endif // CS_GEO_HAS_Z
{

}

#ifdef CS_GEO_HAS_Z
CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY, const cs_real nZ)
: CsObject_Private(pPublic), m_X(nX), m_Y(nY), m_Z(nZ)
{

}
#endif // CS_GEO_HAS_Z

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const CsCoordinate_Private &tCoord)
: CsObject_Private(pPublic), m_X(tCoord.GetX()), m_Y(tCoord.GetY())
#ifdef CS_GEO_HAS_Z
, m_Z(tCoord.GetZ())
#endif // CS_GEO_HAS_Z
{

}

CsCoordinate_Private::~CsCoordinate_Private()
{

}

cs_real CsCoordinate_Private::GetX() const
{
	return m_X;
}

cs_bool CsCoordinate_Private::SetX(const cs_real nX)
{
	m_X = nX;
	return true;
}


cs_real CsCoordinate_Private::GetY() const
{
	return m_Y;
}

cs_bool CsCoordinate_Private::SetY(const cs_real nY)
{
	m_Y = nY;
	return true;
}

#ifdef CS_GEO_HAS_Z
cs_real CsCoordinate_Private::GetZ() const
{
	return m_Z;
}

cs_bool CsCoordinate_Private::SetZ(const cs_real nZ)
{
	m_Z = nZ;
	return true;
}
#endif // CS_GEO_HAS_Z