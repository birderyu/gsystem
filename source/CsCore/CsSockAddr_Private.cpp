#include "CsSockAddr_Private.h"
#include "CsSockAddr.h"
#include "CsString.h"

CsSockAddr_Private::CsSockAddr_Private(CsSockAddr *pPublic)
: CsObject_Private(pPublic)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = 0;
	m_tSocketAddr.sin_port = 0;
}

CsSockAddr_Private::CsSockAddr_Private(CsSockAddr *pPublic, const CsString &sIP, cs_ushort nPort)
: CsObject_Private(pPublic)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.GetCStr());
	m_tSocketAddr.sin_port = htons(nPort);
}

CsSockAddr_Private::~CsSockAddr_Private()
{

}

void CsSockAddr_Private::SetIP(const CsString &sIP)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.GetCStr());
}

void CsSockAddr_Private::SetIP(const cs_uint nIP)
{
	m_tSocketAddr.sin_addr.s_addr = nIP;
}

void CsSockAddr_Private::SetPortID(const cs_ushort nPort)
{
	m_tSocketAddr.sin_port = htons(nPort);
}