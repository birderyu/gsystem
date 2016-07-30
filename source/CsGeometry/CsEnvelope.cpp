#include "CsEnvelope.h"
#include "CsEnvelope_Private.h"
#include "CsString.h"

CsEnvelope::CsEnvelope()
:CsObject(new CsEnvelope_Private(this))
{

}

CsEnvelope::~CsEnvelope()
{

}

CsString CsEnvelope::ToString() const
{
	return CsString();
}