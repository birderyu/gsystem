#include "CsSockAddress.h"
#include "CsSockAddress_Ex.h"
#include "CsString.h"

CsSockAddress::CsSockAddress()
: m_pSockAddress_Ex(new CsSockAddress_Ex())
{

}

CsSockAddress::CsSockAddress(const CsString &sIP, cs_ushort nPort)
: m_pSockAddress_Ex(new CsSockAddress_Ex(sIP, nPort))
{

}

CsSockAddress::~CsSockAddress()
{
	delete m_pSockAddress_Ex;
}

cs_void CsSockAddress::SetIP(const CsString sIP)
{
	CS_ASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetIP(sIP);
}

cs_void CsSockAddress::SetIP(const cs_uint nIP)
{
	CS_ASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetIP(nIP);
}

cs_void CsSockAddress::SetPortID(const cs_ushort nPort)
{
	CS_ASSERT(m_pSockAddress_Ex);
	m_pSockAddress_Ex->SetPortID(nPort);
}