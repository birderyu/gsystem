#include "gudpsocket.h"
#include "gudpsocket_ex.h"
#include "gsockaddress.h"

GUdpSocket::GUdpSocket()
: GSocket(new GUdpSocket_Ex())
{
	GASSERT(m_pSocket_Ex);
}

gbool GUdpSocket::Open(gbool nResue)
{
	GASSERT(m_pSocket_Ex);
	return ((GUdpSocket_Ex*)m_pSocket_Ex)->Open(nResue);
}

gbool GUdpSocket::Open(const GSockAddress &tSockAddr, gbool nResue)
{
	GASSERT(m_pSocket_Ex);
	return ((GUdpSocket_Ex*)m_pSocket_Ex)->Open(tSockAddr.m_pSockAddress_Ex, nResue);
}

gvoid GUdpSocket::Close()
{
	GASSERT(m_pSocket_Ex);
	((GUdpSocket_Ex*)m_pSocket_Ex)->Close();
}

gbool GUdpSocket::SendTo(const gchar *pBufData, gint nLen, const GSockAddress &tPeer)
{
	GASSERT(m_pSocket_Ex);
	return ((GUdpSocket_Ex*)m_pSocket_Ex)->SendTo(pBufData, nLen, tPeer.m_pSockAddress_Ex);
}

gint GUdpSocket::RecvFrom(gchar *pBufData, gint nMaxLen, GSockAddress &tPeer)
{
	GASSERT(m_pSocket_Ex);
	return ((GUdpSocket_Ex*)m_pSocket_Ex)->RecvFrom(pBufData, nMaxLen, tPeer.m_pSockAddress_Ex);
}