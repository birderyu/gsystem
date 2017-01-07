#include "CsUdpSocket_Ex.h"

gbool CsUdpSocket_Ex::Open(gbool nResue)
{
	m_hSocket = CsOpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

gbool CsUdpSocket_Ex::Open(CsSockAddress_Ex *pSockAddr, gbool nResue)
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

gvoid CsUdpSocket_Ex::Close()
{
	if ((gint)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		CsCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

gbool CsUdpSocket_Ex::SendTo(const gchar *pBufData, gint nLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return false;
	}
	gint nAddrLen = sizeof(sockaddr_in);
	gint nRet = CsSendToSocket(m_hSocket, pBufData,
		nLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), nAddrLen);
	if (nRet < 0)
	{
		return false;
	}
	return true;
}

gint CsUdpSocket_Ex::RecvFrom(gchar *pBufData, gint nMaxLen, CsSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	gint nAddrLen = sizeof(sockaddr_in);
	gint n = CsRecvFromSocket(m_hSocket, pBufData,
		nMaxLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), &nAddrLen);
	if (n < 0)
	{
		return -1;
	}
	return n;
}