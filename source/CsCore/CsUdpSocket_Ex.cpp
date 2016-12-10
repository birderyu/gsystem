#include "CsUdpSocket_Ex.h"

cs_int CsUdpSocket_Ex::Open(cs_bool nResue)
{
	m_hSocket = _OpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((cs_int)m_hSocket < 0)
	{
		return -1;
	}
	SetReuseAddr(nResue);
	return 0;
}

cs_int CsUdpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue)
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

void CsUdpSocket_Ex::Close()
{
	if ((cs_int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		_CloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_int CsUdpSocket_Ex::SendTo(const cs_char *pBufData, cs_int nLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	cs_int nRet = _SendToSocket(m_hSocket, pBufData,
		nLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), nAddrLen);
	if (nRet < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsUdpSocket_Ex::RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	cs_int n = _RecvFromSocket(m_hSocket, pBufData,
		nMaxLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), &nAddrLen);
	if (n < 0)
	{
		return -1;
	}
	return n;
}