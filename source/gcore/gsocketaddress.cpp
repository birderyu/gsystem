#include "gsocketaddress.h"
#include "gsockaddress_ex.h"
#include "gstring.h"

namespace gsystem { // gsystem

GSocketAddress::GSocketAddress()
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex())
{

}

GSocketAddress::GSocketAddress(const GString &ip, guint16 port)
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex(ip, port))
{

}

GSocketAddress::GSocketAddress(const GSocketAddress &addr)
	: m_pSockAddress_Ex(new detail::GSockAddress_Ex(*addr.m_pSockAddress_Ex))
{

}

GSocketAddress::GSocketAddress(GSocketAddress &&addr)
	: m_pSockAddress_Ex(addr.m_pSockAddress_Ex)
{
	addr.m_pSockAddress_Ex = GNULL;
}

GSocketAddress::~GSocketAddress()
{
	delete m_pSockAddress_Ex;
}

gvoid GSocketAddress::SetIP(const GString &ip)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetIP(ip);
}

gvoid GSocketAddress::SetIP(guint ip)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetIP(ip);
}

gvoid GSocketAddress::SetPortID(guint16 port)
{
	if (m_pSockAddress_Ex)
	{
		m_pSockAddress_Ex = new detail::GSockAddress_Ex;
	}
	m_pSockAddress_Ex->SetPortID(port);
}

} // namespace gsystem
