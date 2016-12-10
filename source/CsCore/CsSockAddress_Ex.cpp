#include "CsSockAddress_Ex.h"
#include "CsString.h"

CsSockAddress_Ex::CsSockAddress_Ex()
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = 0;
	m_tSocketAddr.sin_port = 0;
}

CsSockAddress_Ex::CsSockAddress_Ex(const CsString &sIP, cs_ushort nPort)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.CString());
	m_tSocketAddr.sin_port = htons(nPort);
}

void CsSockAddress_Ex::SetIP(const CsString &sIP)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.CString());
}

void CsSockAddress_Ex::SetIP(cs_uint nIP)
{
	m_tSocketAddr.sin_addr.s_addr = nIP;
}

void CsSockAddress_Ex::SetPortID(cs_ushort nPort)
{
	m_tSocketAddr.sin_port = htons(nPort);
}