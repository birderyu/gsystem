#include "gudpsocket_ex.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

gbool GUdpSocket_Ex::Open(gbool resue)
{
	m_hSocket = GOpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(resue);
	return true;
}

gbool GUdpSocket_Ex::Open(GSockAddress_Ex *addr, gbool resue)
{
	if (!addr)
	{
		return false;
	}
	if (!Open(resue))
	{
		return false;
	}
	if (GBindSocket(m_hSocket, (sockaddr*)&(addr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
		return false;
	}
	return true;
}

gvoid GUdpSocket_Ex::Close()
{
	if ((gint)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

gbool GUdpSocket_Ex::SendTo(gcbytes buf, gsize size, GSockAddress_Ex *peer)
{
	if (!peer)
	{
		return false;
	}
	gsize len = sizeof(sockaddr_in);
	gint ret = GSendToSocket(m_hSocket, (const gchar *)buf,
		size, 0, (sockaddr*)&(peer->m_tSocketAddr), len);
	if (ret < 0)
	{
		return false;
	}
	return true;
}

gint GUdpSocket_Ex::RecvFrom(gbytes buf, gsize max_size, GSockAddress_Ex *peer)
{
	if (!peer)
	{
		return -1;
	}
	gint len = sizeof(sockaddr_in);
	gint ret = GRecvFromSocket(m_hSocket, (gchar *)buf,
		max_size, 0, (sockaddr*)&(peer->m_tSocketAddr), &len);
	if (ret < 0)
	{
		return -1;
	}
	return ret;
}

} // namespace gsystem.detail
} // namespace gsystem
