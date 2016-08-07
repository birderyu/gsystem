#include "CsCoord.h"
#include "CsCoord_Private.h"
#include "CsString.h"

CsCoordinate::CsCoordinate()
: CsObject(new CsCoordinate_Private(this))
{

}

CsCoordinate::CsCoordinate(const cs_real nX, const cs_real nY)
: CsObject(new CsCoordinate_Private(this, nX, nY))
{

}

#ifdef CS_GEO_HAS_Z
CsCoordinate::CsCoordinate(const cs_real nX, const cs_real nY, const cs_real nZ)
: CsObject(new CsCoordinate_Private(this, nX, nY, nZ))
{

}
#endif // CS_GEO_HAS_Z

CsCoordinate::CsCoordinate(const CsCoordinate &tCoord)
: CsObject(new CsCoordinate_Private(this, *(CsCoordinate_Private*)tCoord.m_pPrivate))
{

}

CsCoordinate::~CsCoordinate()
{

}

CsString CsCoordinate::ToString() const
{
#ifdef CS_GEO_HAS_Z
	return "(" + CsString::FromNum(GetX()) + ", " + CsString::FromNum(GetY()) + ", " + CsString::FromNum(GetZ()) + ")";
#else
	return "(" + CsString::FromNum(GetX()) + ", " + CsString::FromNum(GetY()) + ")";
#endif // CS_GEO_HAS_Z
	
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

#ifdef CS_GEO_HAS_Z
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
#endif // CS_GEO_HAS_Z
