#include "CsSocket.h"
#include "CsSocket_Private.h"
#include "CsSockAddr.h"
#include "CsSockAddr_Private.h"

CsSocket::CsSocket(CsObject_Private *pPrivate)
:CsObject(pPrivate)
{

}

CsSocket::~CsSocket()
{

}

cs_int CsSocket::SetRecvTimeout(const cs_int nMsecs)
{
	CS_PRIVATE(CsSocket);
	return pPrivate->SetRecvTimeout(nMsecs);
}

cs_int CsSocket::GetRecvTimeout() const
{
	CS_PRIVATE(CsSocket);
	return pPrivate->GetRecvTimeout();
}

cs_int CsSocket::SetSendTimeout(cs_int nMsecs)
{
	CS_PRIVATE(CsSocket);
	return pPrivate->SetSendTimeout(nMsecs);
}

cs_int CsSocket::GetSendTimeout() const
{
	CS_PRIVATE(CsSocket);
	return pPrivate->GetSendTimeout();
}

cs_int CsSocket::SetReuseAddr(const cs_bool nResue)
{
	CS_PRIVATE(CsSocket);
	return pPrivate->SetReuseAddr(nResue);
}

cs_int CsSocket::GetPeerAddr(CsSockAddr &tSockAddr) const
{
	CS_PRIVATE(CsSocket);
	return pPrivate->GetPeerAddr((CsSockAddr_Private*)tSockAddr.m_pPrivate);
}

cs_int CsSocket::GetLocalAddr(CsSockAddr &tSockAddr) const
{
	CS_PRIVATE(CsSocket);
	return pPrivate->GetLocalAddr((CsSockAddr_Private*)tSockAddr.m_pPrivate);
}