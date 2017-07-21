#include "gtcpsocket_ex.h"
#include "gtcpsocket.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

gbool GTcpSocket_Ex::Open(gbool resue)
{
	m_hSocket = GOpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(resue);
	return true;
}

gbool GTcpSocket_Ex::Open(GSockAddress_Ex *addr, gbool resue)
{
	if (!addr)
	{
		return false;
	}
	if (!Open(resue))
	{
		return false;
	}
	if (GBindSocket(m_hSocket, (sockaddr*)&(addr->m_tSocketAddr), sizeof(sockaddr_in)) < 0)
	{
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
		return false;
	}
	return true;
}

gvoid GTcpSocket_Ex::Close()
{
	if ((gint)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

gbool GTcpSocket_Ex::Listen(gint back_log)
{
	if (GListenSocket(m_hSocket, back_log) < 0)
	{
		return false;
	}
	return true;
}

gbool GTcpSocket_Ex::Accept(GTcpSocket_Ex *peer)
{
	if (!peer)
	{
		return false;
	}
	sockaddr_in tSocketAddr;
	socklen_t nSocketAddrLen = sizeof(sockaddr_in);
	gsocket tPeerHandle = GAcceptSocket(m_hSocket,
		(sockaddr*)&tSocketAddr, &nSocketAddrLen);
#ifdef _WIN32
	if (tPeerHandle == 0xFFFFFFFF)
	{
		return false;
	}
#else
	if (tPeerHandle < 0)
	{
		return false;
	}
#endif
	peer->m_hSocket = tPeerHandle;
	return true;
}

gbool GTcpSocket_Ex::Connect(GSockAddress_Ex *addr)
{
	if (!addr)
	{
		return false;
	}
	if (GConnectSocket(m_hSocket, (sockaddr*)&(addr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		return false;
	}
	return true;
}

gint GTcpSocket_Ex::Send(gcbytes buf, gsize size)
{
	return GSendSocket(m_hSocket, (const gchar *)buf, size, 0);
}

gint GTcpSocket_Ex::Recv(gbytes buf, gsize size, gbool wait_all)
{
	gint flags = wait_all ? MSG_WAITALL : 0;
	return GRecvSocket(m_hSocket, (gchar *)buf, size, flags);
}

} // namespace gsystem.detail
} // namespace gsystem
