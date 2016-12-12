#include "CsTcpSocket_Ex.h"
#include "CsTcpSocket.h"

cs_bool CsTcpSocket_Ex::Open(cs_bool nResue)
{
	m_hSocket = CsOpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((cs_int)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

cs_bool CsTcpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue)
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

cs_void CsTcpSocket_Ex::Close()
{
	if ((cs_int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_bool CsTcpSocket_Ex::Listen(cs_int nBackLog)
{
	if (CsListenSocket(m_hSocket, nBackLog) < 0)
	{
		return false;
	}
	return true;
}

cs_bool CsTcpSocket_Ex::Accept(CsTcpSocket_Ex *pPeer)
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

cs_bool CsTcpSocket_Ex::Connect(CsSockAddress_Ex *pSockAddr)
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

cs_int CsTcpSocket_Ex::Send(const cs_char *pBufData, cs_int nDataLen)
{
	return CsSendSocket(m_hSocket, pBufData, nDataLen, 0);
}

cs_int CsTcpSocket_Ex::Recv(cs_char *pBufData, cs_int nDataLen, cs_int nWaitAll)
{
	int nFlags = nWaitAll ? MSG_WAITALL : 0;
	return CsRecvSocket(m_hSocket, pBufData, nDataLen, nFlags);
}