#include "CsTcpSocket_Ex.h"
#include "CsTcpSocket.h"

cs_int CsTcpSocket_Ex::Open(cs_bool nResue)
{
	m_hSocket = _OpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((int)m_hSocket < 0)
	{
		return -1;
	}
	SetReuseAddr(nResue);
	return 0;
}

cs_int CsTcpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue)
{
	if (!pSockAddr)
	{
		return -1;
	}
	if (Open(nResue) < 0)
	{
		return -1;
	}
	if (_BindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr_in)) < 0)
	{
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
		return -1;
	}
	return 0;
}

cs_void CsTcpSocket_Ex::Close()
{
	if ((cs_int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_int CsTcpSocket_Ex::Listen(cs_int nBackLog)
{
	if (_ListenSocket(m_hSocket, nBackLog) < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsTcpSocket_Ex::Accept(CsTcpSocket_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	sockaddr_in tSocketAddr;
	socklen_t nSocketAddrLen = sizeof(sockaddr_in);
	TSocket tPeerHandle = _AcceptSocket(m_hSocket,
		(sockaddr*)&tSocketAddr, &nSocketAddrLen);
#ifdef _WIN32
	if (tPeerHandle == 0xFFFFFFFF)
	{
		return -1;
	}
#else
	if (tPeerHandle < 0)
	{
		return -1;
	}
#endif
	pPeer->m_hSocket = tPeerHandle;
	return 0;
}

cs_int CsTcpSocket_Ex::Connect(CsSockAddress_Ex *pSockAddr)
{
	if (!pSockAddr)
	{
		return -1;
	}
	if (_ConnectSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsTcpSocket_Ex::Send(const cs_char *pBufData, cs_int nDataLen)
{
	return _SendSocket(m_hSocket, pBufData, nDataLen, 0);
}

cs_int CsTcpSocket_Ex::Recv(cs_char *pBufData, cs_int nDataLen, cs_int nWaitAll)
{
	int nFlags = nWaitAll ? MSG_WAITALL : 0;
	return _RecvSocket(m_hSocket, pBufData, nDataLen, nFlags);
}