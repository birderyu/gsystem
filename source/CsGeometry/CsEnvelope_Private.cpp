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
	return CsMath::Abs(m_tLeftTop.GetX() - m_tRightBottom.GetX());
}

cs_real CsEnvelope_Private::GetWidth() const
{
	return CsMath::Abs(m_tLeftTop.GetY() - m_tRightBottom.GetY());
}

cs_real CsEnvelope_Private::GetHeight() const
{
	return CsMath::Abs(m_tLeftTop.GetZ() - m_tRightBottom.GetZ());
}