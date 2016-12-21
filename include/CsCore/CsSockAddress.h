#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "CsObject.h"

class CsString;
class CsSockAddress_Ex;

class CS_API CsSockAddress 
{
	friend class CsSocket;
	friend class CsTcpSocket;
	friend class CsUdpSocket;

public:
	explicit CsSockAddress();
	explicit CsSockAddress(const CsString &sIP, cs_ushort nPort);
	~CsSockAddress();
	cs_void SetIP(const CsString sIP);
	cs_void SetIP(cs_uint nIP);
	cs_void SetPortID(cs_ushort nPort);

private:
	CsSockAddress_Ex *m_pSockAddress_Ex;
};

#endif // _CORE_SOCKET_ADDRESS_H_