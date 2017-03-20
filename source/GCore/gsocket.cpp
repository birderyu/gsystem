#include "gsocket.h"
#include "gsocket_ex.h"
#include "gsockaddress.h"
#include "gsockaddress_ex.h"

namespace gsystem { // gsystem

GSocket::GSocket(detail::GSocket_Ex *pSocket_Ex)
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

GSockAddress GSocket::GetPeerAddr() const
{
	GASSERT(m_pSocket_Ex);
	GSockAddress addr;
	m_pSocket_Ex->GetPeerAddr(*addr.m_pSockAddress_Ex);
	return addr;
}

GSockAddress GSocket::GetLocalAddr() const
{
	GASSERT(m_pSocket_Ex);
	GSockAddress addr;
	m_pSocket_Ex->GetLocalAddr(*addr.m_pSockAddress_Ex);
	return addr;
}

} // namespace gsystem
