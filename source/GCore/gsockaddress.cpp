#include "gsockaddress.h"
#include "gsockaddress_ex.h"
#include "gstring.h"

GSockAddress::GSockAddress()
: m_pSockAddress_Ex(new GSockAddress_Ex())
{

}

GSockAddress::GSockAddress(const GString &sIP, gushort nPort)
: m_pSockAddress_Ex(new GSockAddress_Ex(sIP, nPort))
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