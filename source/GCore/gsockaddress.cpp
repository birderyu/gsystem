#include "gsockaddress.h"
#include "gsockaddress_ex.h"
#include "gstring.h"

namespace gsystem { // gsystem

GSockAddress::GSockAddress()
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex())
{

}

GSockAddress::GSockAddress(const GString &ip, guint16 port)
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex(ip, port))
{

}

GSockAddress::GSockAddress(const GSockAddress &addr)
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex(*addr.m_pSockAddress_Ex))
{

}

GSockAddress::GSockAddress(GSockAddress &&addr)
	: m_pSockAddress_Ex(addr.m_pSockAddress_Ex)
{
	addr.m_pSockAddress_Ex = GNULL;
}

GSockAddress::~GSockAddress()
{
	delete m_pSockAddress_Ex;
}

gvoid GSockAddress::SetIP(const GString &ip)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetIP(ip);
}

gvoid GSockAddress::SetIP(guint ip)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetIP(ip);
}

gvoid GSockAddress::SetPortID(guint16 port)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetPortID(port);
}

} // namespace gsystem
