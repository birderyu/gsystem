#include "gtcpsocket.h"
#include "CsTcpSocket_Ex.h"
#include "gsockaddress.h"

GTcpSocket::GTcpSocket()
: GSocket(new CsTcpSocket_Ex())
{
	GASSERT(m_pSocket_Ex);
}

gbool GTcpSocket::Open(gbool nResue)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Open(nResue);
}

gbool GTcpSocket::Open(const GSockAddress &tSockAddr, gbool nResue)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Open(tSockAddr.m_pSockAddress_Ex, nResue);
}

gvoid GTcpSocket::Close()
{
	GASSERT(m_pSocket_Ex);
	((CsTcpSocket_Ex*)m_pSocket_Ex)->Close();
}

gbool GTcpSocket::Listen(gint nBackLog)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Listen(nBackLog);
}

gbool GTcpSocket::Accept(const GTcpSocket &pPeer)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Accept((CsTcpSocket_Ex*)pPeer.m_pSocket_Ex);
}

gbool GTcpSocket::Connect(const GSockAddress &tSockAddr)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Connect(tSockAddr.m_pSockAddress_Ex);
}

gint GTcpSocket::Send(const gchar *pBufData, gint nDataLen)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Send(pBufData, nDataLen);
}

gint GTcpSocket::Recv(gchar *pBufData, gint nDataLen, gint nWaitAll)
{
	GASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Recv(pBufData, nDataLen, nWaitAll);
}