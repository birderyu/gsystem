#include "CsSockAddr.h"
#include "CsSockAddr_Private.h"
#include "CsString.h"

CsSockAddress::CsSockAddress()
: CsObject(new CsSockAddress_Private(this))
{

}

CsSockAddress::CsSockAddress(const CsString &sIP, cs_ushort nPort)
: CsObject(new CsSockAddress_Private(this, sIP, nPort))
{

}

CsSockAddress::~CsSockAddress()
{

}

void CsSockAddress::SetIP(const CsString sIP)
{
	CS_PRIVATE(CsSockAddress);
	pPrivate->SetIP(sIP);
}

void CsSockAddress::SetIP(const cs_uint nIP)
{
	CS_PRIVATE(CsSockAddress);
	pPrivate->SetIP(nIP);
}

void CsSockAddress::SetPortID(const cs_ushort nPort)
{
	CS_PRIVATE(CsSockAddress);
	pPrivate->SetPortID(nPort);
}