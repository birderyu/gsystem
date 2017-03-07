#include "gudpsocket_ex.h"

gbool GUdpSocket_Ex::Open(gbool nResue)
{
	m_hSocket = GOpenSocket(AF_INET, SOCK_DGRAM, 0);
	if ((gint)m_hSocket < 0)
	{
		return false;
	}
	SetReuseAddress(nResue);
	return true;
}

gbool GUdpSocket_Ex::Open(GSockAddress_Ex *pSockAddr, gbool nResue)
{
	if (!pSockAddr)
	{
		return false;
	}
	if (!Open(nResue))
	{
		return false;
	}
	if (GBindSocket(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), sizeof(sockaddr)) < 0)
	{
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
		return false;
	}
	return true;
}

gvoid GUdpSocket_Ex::Close()
{
	if ((gint)m_hSocket >= 0)
	{
		shutdown(m_hSocket, 2);
		GCloseSocket(m_hSocket);
		m_hSocket = -1;
	}
}

gbool GUdpSocket_Ex::SendTo(const gchar *pBufData, gint nLen, GSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return false;
	}
	gint nAddrLen = sizeof(sockaddr_in);
	gint nRet = GSendToSocket(m_hSocket, pBufData,
		nLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), nAddrLen);
	if (nRet < 0)
	{
		return false;
	}
	return true;
}

gint GUdpSocket_Ex::RecvFrom(gchar *pBufData, gint nMaxLen, GSockAddress_Ex *pPeer)
{
	if (!pPeer)
	{
		return -1;
	}
	gint nAddrLen = sizeof(sockaddr_in);
	gint n = GRecvFromSocket(m_hSocket, pBufData,
		nMaxLen, 0, (sockaddr*)&(pPeer->m_tSocketAddr), &nAddrLen);
	if (n < 0)
	{
		return -1;
	}
	return n;
}