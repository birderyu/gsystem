#include "CsUdpSocket.h"
#include "CsUdpSocket_Ex.h"
#include "CsSockAddress.h"

CsUdpSocket::CsUdpSocket()
: CsSocket(new CsUdpSocket_Ex())
{
	CS_ASSERT(m_pSocket_Ex);
}

cs_int CsUdpSocket::Open(cs_bool nResue)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsUdpSocket_Ex*)m_pSocket_Ex)->Open(nResue);
}

cs_int CsUdpSocket::Open(const CsSockAddress &tSockAddr, cs_bool nResue)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsUdpSocket_Ex*)m_pSocket_Ex)->Open(tSockAddr.m_pSockAddress_Ex, nResue);
}

void CsUdpSocket::Close()
{
	CS_ASSERT(m_pSocket_Ex);
	((CsUdpSocket_Ex*)m_pSocket_Ex)->Close();
}

cs_int CsUdpSocket::SendTo(const cs_char *pBufData, cs_int nLen, const CsSockAddress &tPeer)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsUdpSocket_Ex*)m_pSocket_Ex)->SendTo(pBufData, nLen, tPeer.m_pSockAddress_Ex);
}

cs_int CsUdpSocket::RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress &tPeer)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsUdpSocket_Ex*)m_pSocket_Ex)->RecvFrom(pBufData, nMaxLen, tPeer.m_pSockAddress_Ex);
}