#include "CsSocket.h"
#include "CsSocket_Ex.h"
#include "CsSockAddress.h"
#include "CsSockAddress_Ex.h"

CsSocket::CsSocket(CsSocket_Ex *pSocket_Ex)
:m_pSocket_Ex(pSocket_Ex)
{

}

CsSocket::~CsSocket()
{
	delete m_pSocket_Ex;
}

cs_int CsSocket::SetRecvTimeout(const cs_int nMsecs)
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetRecvTimeout(nMsecs);
}

cs_int CsSocket::GetRecvTimeout() const
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetRecvTimeout();
}

cs_int CsSocket::SetSendTimeout(cs_int nMsecs)
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetSendTimeout(nMsecs);
}

cs_int CsSocket::GetSendTimeout() const
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetSendTimeout();
}

cs_int CsSocket::SetReuseAddr(const cs_bool nResue)
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetReuseAddr(nResue);
}

cs_int CsSocket::GetPeerAddr(CsSockAddress &tSockAddr) const
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetPeerAddr(tSockAddr.m_pSockAddress_Ex);
}

cs_int CsSocket::GetLocalAddr(CsSockAddress &tSockAddr) const
{
	CS_ASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetLocalAddr(tSockAddr.m_pSockAddress_Ex);
}