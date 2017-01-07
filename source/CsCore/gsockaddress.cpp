#include "gsockaddress.h"
#include "CsSockAddress_Ex.h"
#include "gstring.h"

GSockAddress::GSockAddress()
: m_pSockAddress_Ex(new CsSockAddress_Ex())
{

}

GSockAddress::GSockAddress(const GString &sIP, gushort nPort)
: m_pSockAddress_Ex(new CsSockAddress_Ex(sIP, nPort))
{

}

GSockAddress::~GSockAddress()
{
	delete m_pSockAddress_Ex;
}

gvoid GSockAddress::SetIP(const GString sIP)
{
	GASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetIP(sIP);
}

gvoid GSockAddress::SetIP(const guint nIP)
{
	GASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetIP(nIP);
}

gvoid GSockAddress::SetPortID(const gushort nPort)
{
	GASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetPortID(nPort);
}