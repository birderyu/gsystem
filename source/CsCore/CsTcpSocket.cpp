#include "CsTcpSocket.h"
#include "CsTcpSocket_Private.h"
#include "CsSockAddress.h"

CsTcpSocket::CsTcpSocket()
:CsSocket(new CsTcpSocket_Private(this))
{

}
CsTcpSocket::~CsTcpSocket()
{

}

cs_int CsTcpSocket::Open(cs_bool nResue)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Open(nResue);
}

cs_int CsTcpSocket::Open(const CsSockAddress &tSockAddr, cs_bool nResue)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Open((CsSockAddress_Private*)tSockAddr.m_pPrivate, nResue);
}

void CsTcpSocket::Close()
{
	CS_PRIVATE(CsTcpSocket);
	pPrivate->Close();
}

cs_int CsTcpSocket::Listen(cs_int nBackLog)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Listen(nBackLog);
}

cs_int CsTcpSocket::Accept(const CsTcpSocket &pPeer)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Accept((CsTcpSocket_Private*)pPeer.m_pPrivate);
}

cs_int CsTcpSocket::Connect(const CsSockAddress &tSockAddr)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Connect((CsSockAddress_Private*)tSockAddr.m_pPrivate);
}

cs_int CsTcpSocket::Send(const void *pBufData, cs_int nDataLen)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Send(pBufData, nDataLen);
}

cs_int CsTcpSocket::Recv(void *pBufData, cs_int nDataLen, cs_int nWaitAll)
{
	CS_PRIVATE(CsTcpSocket);
	return pPrivate->Recv(pBufData, nDataLen, nWaitAll);
}