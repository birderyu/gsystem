#include "gudpsocket.h"
#include "gudpsocket_ex.h"
#include "gsocketaddress.h"

namespace gsystem { // gsystem

GUdpSocket::GUdpSocket()
: GSocket(new detail::GUdpSocket_Ex())
{
	GASSERT(m_pSocket_Ex);
}

gbool GUdpSocket::Open(gbool resue)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GUdpSocket_Ex*)m_pSocket_Ex)->Open(resue);
}

gbool GUdpSocket::Open(const GSocketAddress &addr, gbool resue)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GUdpSocket_Ex*)m_pSocket_Ex)->Open(addr.m_pSockAddress_Ex, resue);
}

gvoid GUdpSocket::Close()
{
	GASSERT(m_pSocket_Ex);
	((detail::GUdpSocket_Ex*)m_pSocket_Ex)->Close();
}

gbool GUdpSocket::SendTo(gcbytes buf, gsize size, const GSocketAddress &peer)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GUdpSocket_Ex*)m_pSocket_Ex)->SendTo(buf, size, peer.m_pSockAddress_Ex);
}

gint GUdpSocket::RecvFrom(gbytes buf, gsize max_size, GSocketAddress &peer)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GUdpSocket_Ex*)m_pSocket_Ex)->RecvFrom(buf, max_size, peer.m_pSockAddress_Ex);
}

} // namespace gsystem
