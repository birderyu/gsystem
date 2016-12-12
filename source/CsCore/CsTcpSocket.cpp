#include "CsTcpSocket.h"
#include "CsTcpSocket_Ex.h"
#include "CsSockAddress.h"

CsTcpSocket::CsTcpSocket()
: CsSocket(new CsTcpSocket_Ex())
{
	CS_ASSERT(m_pSocket_Ex);
}

cs_bool CsTcpSocket::Open(cs_bool nResue)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Open(nResue);
}

cs_bool CsTcpSocket::Open(const CsSockAddress &tSockAddr, cs_bool nResue)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Open(tSockAddr.m_pSockAddress_Ex, nResue);
}

cs_void CsTcpSocket::Close()
{
	CS_ASSERT(m_pSocket_Ex);
	((CsTcpSocket_Ex*)m_pSocket_Ex)->Close();
}

cs_bool CsTcpSocket::Listen(cs_int nBackLog)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Listen(nBackLog);
}

cs_bool CsTcpSocket::Accept(const CsTcpSocket &pPeer)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Accept((CsTcpSocket_Ex*)pPeer.m_pSocket_Ex);
}

cs_bool CsTcpSocket::Connect(const CsSockAddress &tSockAddr)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Connect(tSockAddr.m_pSockAddress_Ex);
}

cs_int CsTcpSocket::Send(const cs_char *pBufData, cs_int nDataLen)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Send(pBufData, nDataLen);
}

cs_int CsTcpSocket::Recv(cs_char *pBufData, cs_int nDataLen, cs_int nWaitAll)
{
	CS_ASSERT(m_pSocket_Ex);
	return ((CsTcpSocket_Ex*)m_pSocket_Ex)->Recv(pBufData, nDataLen, nWaitAll);
}