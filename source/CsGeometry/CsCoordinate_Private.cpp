#include "CsCoordinate_Private.h"
#include "CsCoordinate.h"

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic)
: CsObject_Private(pPublic), m_X(0), m_Y(0), m_Z(0)
{

}

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY)
: CsObject_Private(pPublic), m_X(nX), m_Y(nY), m_Z(0)
{

}

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const cs_real nX, const cs_real nY, const cs_real nZ)
: CsObject_Private(pPublic), m_X(nX), m_Y(nY), m_Z(nZ)
{

}

CsCoordinate_Private::CsCoordinate_Private(CsCoordinate *pPublic, const CsCoordinate_Private &tCoord)
: CsObject_Private(pPublic), m_X(tCoord.GetX()), m_Y(tCoord.GetY()), m_Z(tCoord.GetZ())
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

cs_real CsCoordinate_Private::GetZ() const
{
	return m_Z;
}

cs_bool CsCoordinate_Private::SetZ(const cs_real nZ)
{
	m_Z = nZ;
	return true;
}