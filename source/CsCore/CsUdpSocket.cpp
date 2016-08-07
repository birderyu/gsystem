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

cs_int CsUdpSocket::Open(const CsSockAddress &tSockAddr, cs_bool nResue)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->Open((CsSockAddress_Private*)tSockAddr.m_pPrivate, nResue);
}

void CsUdpSocket::Close()
{
	CS_PRIVATE(CsUdpSocket);
	pPrivate->Close();
}

cs_int CsUdpSocket::SendTo(const void *pBufData, cs_int nLen, const CsSockAddress &tPeer)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->SendTo(pBufData, nLen, (CsSockAddress_Private*)tPeer.m_pPrivate);
}

cs_int CsUdpSocket::RecvFrom(void *pBufData, cs_int nMaxLen, CsSockAddress &tPeer)
{
	CS_PRIVATE(CsUdpSocket);
	return pPrivate->RecvFrom(pBufData, nMaxLen, (CsSockAddress_Private*)tPeer.m_pPrivate);
}