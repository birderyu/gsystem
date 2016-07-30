#include "CsSockAddress_Private.h"
#include "CsSockAddress.h"
#include "CsString.h"

CsSockAddress_Private::CsSockAddress_Private(CsSockAddress *pPublic)
: CsObject_Private(pPublic)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = 0;
	m_tSocketAddr.sin_port = 0;
}

CsSockAddress_Private::CsSockAddress_Private(CsSockAddress *pPublic, const CsString &sIP, cs_ushort nPort)
: CsObject_Private(pPublic)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.GetCStr());
	m_tSocketAddr.sin_port = htons(nPort);
}

CsSockAddress_Private::~CsSockAddress_Private()
{

}

void CsSockAddress_Private::SetIP(const CsString &sIP)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.GetCStr());
}

void CsSockAddress_Private::SetIP(const cs_uint nIP)
{
	m_tSocketAddr.sin_addr.s_addr = nIP;
}

void CsSockAddress_Private::SetPortID(const cs_ushort nPort)
{
	m_tSocketAddr.sin_port = htons(nPort);
}