#include "gsockaddress_ex.h"
#include "gstring.h"

GSockAddress_Ex::GSockAddress_Ex()
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = 0;
	m_tSocketAddr.sin_port = 0;
}

GSockAddress_Ex::GSockAddress_Ex(const GString &sIP, gushort nPort)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.CString());
	m_tSocketAddr.sin_port = htons(nPort);
}

void GSockAddress_Ex::SetIP(const GString &sIP)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.CString());
}

void GSockAddress_Ex::SetIP(guint nIP)
{
	m_tSocketAddr.sin_addr.s_addr = nIP;
}

void GSockAddress_Ex::SetPortID(gushort nPort)
{
	m_tSocketAddr.sin_port = htons(nPort);
}