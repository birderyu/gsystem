#include "CsSockAddr.h"
#include "CsSockAddr_Private.h"
#include "CsString.h"

CsSockAddr::CsSockAddr()
: CsObject(new CsSockAddr_Private(this))
{

}

CsSockAddr::CsSockAddr(const CsString &sIP, cs_ushort nPort)
: CsObject(new CsSockAddr_Private(this, sIP, nPort))
{

}

CsSockAddr::~CsSockAddr()
{

}

void CsSockAddr::SetIP(const CsString sIP)
{
	CS_PRIVATE(CsSockAddr);
	pPrivate->SetIP(sIP);
}

void CsSockAddr::SetIP(const cs_uint nIP)
{
	CS_PRIVATE(CsSockAddr);
	pPrivate->SetIP(nIP);
}

void CsSockAddr::SetPortID(const cs_ushort nPort)
{
	CS_PRIVATE(CsSockAddr);
	pPrivate->SetPortID(nPort);
}