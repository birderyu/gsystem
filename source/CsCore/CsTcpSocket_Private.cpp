#include "CsTcpSocket_Private.h"
#include "CsTcpSocket.h"

CsTcpSocket_Private::CsTcpSocket_Private(CsTcpSocket *pPublic)
: CsSocket_Private(pPublic)
{

}

CsTcpSocket_Private::~CsTcpSocket_Private()
{

}

cs_int CsTcpSocket_Private::Open(cs_bool nResue)
{
	m_hSocket = _OpenSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ((int)m_hSocket < 0)
	{
		return -1;
	}
	SetReuseAddr(nResue);
	return 0;
}

cs_int CsTcpSocket_Private::Open(CsSockAddress_Private *pSockAddr, cs_bool nResue)
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

void CsTcpSocket_Private::Close()
{
	if ((int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_int CsTcpSocket_Private::Listen(cs_int nBackLog)
{
	if (_ListenSocket(m_hSocket, nBackLog) < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsTcpSocket_Private::Accept(CsTcpSocket_Private *pPeer)
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

cs_int CsTcpSocket_Private::Connect(CsSockAddress_Private *pSockAddr)
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

cs_int CsTcpSocket_Private::Send(const void *pBufData, cs_int nDataLen)
{
	return _SendSocket(m_hSocket, (const cs_char*)pBufData, nDataLen, 0);
}

cs_int CsTcpSocket_Private::Recv(void *pBufData, cs_int nDataLen, cs_int nWaitAll)
{
	int nFlags = nWaitAll ? MSG_WAITALL : 0;
	return _RecvSocket(m_hSocket, (cs_char*)pBufData, nDataLen, nFlags);
}