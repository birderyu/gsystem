#include "CsUdpSocket.h"
#include "CsUdpSocket_Private.h"
#include "CsSockAddr.h"

CsUdpSocket::CsUdpSocket()
: CsSocket(new CsUdpSocket_Private(this))
{

}

CsUdpSocket::~CsUdpSocket()
{

}

cs_int CsUdpSocket::Open(cs_bool nResue)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->Open(nResue);
}

cs_int CsUdpSocket::Open(const CsSockAddr &tSockAddr, cs_bool nResue)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->Open((CsSockAddr_Private*)tSockAddr.m_pPrivate, nResue);
}

void CsUdpSocket::Close()
{
	CS_PRIVATE(CsUdpSocket);
	pPrivate->Close();
}

cs_int CsUdpSocket::SendTo(const void *pBufData, cs_int nLen, const CsSockAddr &tPeer)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->SendTo(pBufData, nLen, (CsSockAddr_Private*)tPeer.m_pPrivate);
}

cs_int CsUdpSocket::RecvFrom(void *pBufData, cs_int nMaxLen, CsSockAddr &tPeer)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->RecvFrom(pBufData, nMaxLen, (CsSockAddr_Private*)tPeer.m_pPrivate);
}