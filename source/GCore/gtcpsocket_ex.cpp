#include "gtcpsocket_ex.h"
#include "gtcpsocket.h"

gbool GTcpSocket_Ex::Open(gbool nResue)
{
	m_hSocket = GOpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

gbool GTcpSocket_Ex::Open(GSockAddress_Ex *pSockAddr, gbool nResue)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (!Open(nResue))
	{
		return false;
	}
	if (GBindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr_in)) < 0)
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

gbool GTcpSocket_Ex::Listen(gint nBackLog)
{
	if (GListenSocket(m_hSocket, nBackLog) < 0)
	{
		return false;
	}
	return true;
}

gbool GTcpSocket_Ex::Accept(GTcpSocket_Ex *pPeer)
{
	if (!pPeer)
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
	pPeer->m_hSocket = tPeerHandle;
	return true;
}

gbool GTcpSocket_Ex::Connect(GSockAddress_Ex *pSockAddr)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (GConnectSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		return false;
	}
	return true;
}

gint GTcpSocket_Ex::Send(const gchar *pBufData, gint nDataLen)
{
	return GSendSocket(m_hSocket, pBufData, nDataLen, 0);
}

gint GTcpSocket_Ex::Recv(gchar *pBufData, gint nDataLen, gint nWaitAll)
{
	int nFlags = nWaitAll ? MSG_WAITALL : 0;
	return GRecvSocket(m_hSocket, pBufData, nDataLen, nFlags);
}