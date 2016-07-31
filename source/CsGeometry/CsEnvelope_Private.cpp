#include "CsEnvelope_Private.h"
#include "CsEnvelope.h"
#include "CsMath.h"

CsEnvelope_Private::CsEnvelope_Private(CsEnvelope *pPublic)
:CsObject_Private(pPublic)
{

}

CsEnvelope_Private::~CsEnvelope_Private()
{

}

cs_real CsEnvelope_Private::GetLength() const
{
	return CsMath::Abs(m_tMax.GetX() - m_tMin.GetX());
}

cs_real CsEnvelope_Private::GetWidth() const
{
	return CsMath::Abs(m_tMax.GetY() - m_tMin.GetY());
}

#ifdef CS_GEO_HAS_Z
cs_real CsEnvelope_Private::GetHeight() const
{
	return CsMath::Abs(m_tMax.GetZ() - m_tMin.GetZ());
}
#endif // CS_GEO_HAS_Z