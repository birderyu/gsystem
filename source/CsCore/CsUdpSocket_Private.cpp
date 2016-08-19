#include "CsUdpSocket_Private.h"
#include "CsUdpSocket.h"

CsUdpSocket_Private::CsUdpSocket_Private(CsUdpSocket *pPublic)
: CsSocket_Private(pPublic)
{

}

CsUdpSocket_Private::~CsUdpSocket_Private()
{

}

cs_int CsUdpSocket_Private::Open(cs_bool nResue)
{
	m_hSocket = _OpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((int)m_hSocket < 0)
	{
		return -1;
	}
	SetReuseAddr(nResue);
	return 0;
}

cs_int CsUdpSocket_Private::Open(CsSockAddr_Private *pSockAddr, cs_bool nResue)
{
	if (!pSockAddr)
	{
		return -1;
	}
	if (Open(nResue) < 0)
	{
		return -1;
	}
	if (_BindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
		return -1;
	}
	return 0;
}

void CsUdpSocket_Private::Close()
{
	if ((int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_int CsUdpSocket_Private::SendTo(const void *pBufData, cs_int nLen, CsSockAddr_Private *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	int nRet = _SendToSocket(m_hSocket, (const cs_char*)pBufData,
		nLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), nAddrLen);
	if (nRet < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsUdpSocket_Private::RecvFrom(void *pBufData, cs_int nMaxLen, CsSockAddr_Private *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	int n = _RecvFromSocket(m_hSocket, (char*)pBufData,
		nMaxLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), &nAddrLen);
	if (n < 0)
	{
		return -1;
	}
	return n;
}