#include "CsUdpSocket_Ex.h"

cs_bool CsUdpSocket_Ex::Open(cs_bool nResue)
{
	m_hSocket = CsOpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((cs_int)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

cs_bool CsUdpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (Open(nResue) < 0)
	{
		return false;
	}
	if (CsBindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
		return false;
	}
	return true;
}

cs_void CsUdpSocket_Ex::Close()
{
	if ((cs_int)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

cs_bool CsUdpSocket_Ex::SendTo(const cs_char *pBufData, cs_int nLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return false;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	cs_int nRet = CsSendToSocket(m_hSocket, pBufData,
		nLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), nAddrLen);
	if (nRet < 0)
	{
		return false;
	}
	return true;
}

cs_int CsUdpSocket_Ex::RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	cs_int nAddrLen = sizeof(sockaddr_in);
	cs_int n = CsRecvFromSocket(m_hSocket, pBufData,
		nMaxLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), &nAddrLen);
	if (n < 0)
	{
		return -1;
	}
	return n;
}