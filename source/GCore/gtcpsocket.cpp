#include "gtcpsocket.h"
#include "gtcpsocket_ex.h"
#include "gsocketaddress.h"

namespace gsystem { // gsystem

GTcpSocket::GTcpSocket()
: GSocket(new detail::GTcpSocket_Ex())
{
	GASSERT(m_pSocket_Ex);
}

gbool GTcpSocket::Open(gbool resue)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Open(resue);
}

gbool GTcpSocket::Open(const GSocketAddress &addr, gbool resue)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Open(addr.m_pSockAddress_Ex, resue);
}

gvoid GTcpSocket::Close()
{
	GASSERT(m_pSocket_Ex);
	((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Close();
}

gbool GTcpSocket::Listen(gint back_log)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Listen(back_log);
}

gbool GTcpSocket::Accept(const GTcpSocket &peer)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Accept((detail::GTcpSocket_Ex*)peer.m_pSocket_Ex);
}

gbool GTcpSocket::Connect(const GSocketAddress &addr)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Connect(addr.m_pSockAddress_Ex);
}

gint GTcpSocket::Send(gcbytes buf, gsize size)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Send(buf, size);
}

gint GTcpSocket::Recv(gbytes buf, gsize size, gbool wait_all)
{
	GASSERT(m_pSocket_Ex);
	return ((detail::GTcpSocket_Ex*)m_pSocket_Ex)->Recv(buf, size, wait_all);
}

} // namespace gsystem
