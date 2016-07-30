#include "CsCoordinate.h"
#include "CsCoordinate_Private.h"
#include "CsString.h"

CsCoordinate::CsCoordinate()
: CsObject(new CsCoordinate_Private(this))
{

}

CsCoordinate::CsCoordinate(const cs_real nX, const cs_real nY)
: CsObject(new CsCoordinate_Private(this, nX, nY))
{

}

CsCoordinate::CsCoordinate(const cs_real nX, const cs_real nY, const cs_real nZ)
: CsObject(new CsCoordinate_Private(this, nX, nY, nZ))
{

}

CsCoordinate::CsCoordinate(const CsCoordinate &tCoord)
: CsObject(new CsCoordinate_Private(this, *(CsCoordinate_Private*)tCoord.m_pPrivate))
{

}

CsCoordinate::~CsCoordinate()
{

}

CsString CsCoordinate::ToString() const
{
	return "(" + CsString::FromNum(GetX()) + ", " + CsString::FromNum(GetY()) + ", " + CsString::FromNum(GetZ()) + ")";
}

cs_real CsCoordinate::GetX() const
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->GetX();
}

cs_bool CsCoordinate::SetX(const cs_real nX)
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->SetX(nX);
}

cs_real CsCoordinate::GetY() const
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->GetY();
}

cs_bool CsCoordinate::SetY(const cs_real nY)
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->SetY(nY);
}

cs_real CsCoordinate::GetZ() const
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->GetZ();
}

cs_bool CsCoordinate::SetZ(const cs_real nZ)
{
	CS_PRIVATE(CsCoordinate);
	return pPrivate->SetZ(nZ);
}
