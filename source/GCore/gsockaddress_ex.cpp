#include "gsockaddress_ex.h"
#include "gstring.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

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
	m_tSocketAddr.sin_port = ::htons(nPort);
}

gvoid GSockAddress_Ex::SetIP(const GString &sIP)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(sIP.CString());
}

gvoid GSockAddress_Ex::SetIP(guint nIP)
{
	m_tSocketAddr.sin_addr.s_addr = nIP;
}

gvoid GSockAddress_Ex::SetPortID(gushort nPort)
{
	m_tSocketAddr.sin_port = ::htons(nPort);
}

} // namespace gsystem.detail
} // namespace gsystem
