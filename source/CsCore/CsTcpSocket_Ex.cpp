#include "CsTcpSocket_Ex.h"
#include "gtcpsocket.h"

gbool CsTcpSocket_Ex::Open(gbool nResue)
{
	m_hSocket = CsOpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

gbool CsTcpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, gbool nResue)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (Open(nResue) < 0)
	{
		return false;
	}
	if (CsBindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr_in)) < 0)
	{
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
		return false;
	}
	return true;
}

gvoid CsTcpSocket_Ex::Close()
{
	if ((gint)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

gbool CsTcpSocket_Ex::Listen(gint nBackLog)
{
	if (CsListenSocket(m_hSocket, nBackLog) < 0)
	{
		return false;
	}
	return true;
}

gbool CsTcpSocket_Ex::Accept(CsTcpSocket_Ex *pPeer)
{
	if (!pPeer)
	{
		return false;
	}
	sockaddr_in tSocketAddr;
	socklen_t nSocketAddrLen = sizeof(sockaddr_in);
	TSocket tPeerHandle = CsAcceptSocket(m_hSocket,
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

gbool CsTcpSocket_Ex::Connect(CsSockAddress_Ex *pSockAddr)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (CsConnectSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		return false;
	}
	return true;
}

gint CsTcpSocket_Ex::Send(const gchar *pBufData, gint nDataLen)
{
	return CsSendSocket(m_hSocket, pBufData, nDataLen, 0);
}

gint CsTcpSocket_Ex::Recv(gchar *pBufData, gint nDataLen, gint nWaitAll)
{
	int nFlags = nWaitAll ? MSG_WAITALL : 0;
	return CsRecvSocket(m_hSocket, pBufData, nDataLen, nFlags);
}