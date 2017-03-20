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

GSockAddress_Ex::GSockAddress_Ex(const GString &ip, guint16 port)
{
	m_tSocketAddr.sin_family = AF_INET;
	m_tSocketAddr.sin_addr.s_addr = inet_addr(ip.CString());
	m_tSocketAddr.sin_port = ::htons(port);
}

GSockAddress_Ex::GSockAddress_Ex(const GSockAddress_Ex &addr)
	: m_tSocketAddr(addr.m_tSocketAddr)
{

}

gvoid GSockAddress_Ex::SetIP(const GString &ip)
{
	m_tSocketAddr.sin_addr.s_addr = inet_addr(ip.CString());
}

gvoid GSockAddress_Ex::SetIP(guint ip)
{
	m_tSocketAddr.sin_addr.s_addr = ip;
}

gvoid GSockAddress_Ex::SetPortID(guint16 port)
{
	m_tSocketAddr.sin_port = ::htons(port);
}

} // namespace gsystem.detail
} // namespace gsystem
