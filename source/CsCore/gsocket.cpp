#include "gsocket.h"
#include "CsSocket_Ex.h"
#include "gsockaddress.h"
#include "CsSockAddress_Ex.h"

GSocket::GSocket(CsSocket_Ex *pSocket_Ex)
:m_pSocket_Ex(pSocket_Ex)
{

}

GSocket::~GSocket()
{
	delete m_pSocket_Ex;
}

gbool GSocket::SetRecvTimeout(gint nMsecs)
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetRecvTimeout(nMsecs);
}

gint GSocket::GetRecvTimeout() const
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetRecvTimeout();
}

gbool GSocket::SetSendTimeout(gint nMsecs)
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetSendTimeout(nMsecs);
}

gint GSocket::GetSendTimeout() const
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetSendTimeout();
}

gbool GSocket::SetReuseAddress(gbool nResue)
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->SetReuseAddress(nResue);
}

gbool GSocket::GetPeerAddr(GSockAddress &tSockAddr) const
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetPeerAddr(tSockAddr.m_pSockAddress_Ex);
}

gbool GSocket::GetLocalAddr(GSockAddress &tSockAddr) const
{
	GASSERT(m_pSocket_Ex);
	return m_pSocket_Ex->GetLocalAddr(tSockAddr.m_pSockAddress_Ex);
}