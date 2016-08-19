#ifndef _CSCORE_CSSOCKET_ADDRESS_H_
#define _CSCORE_CSSOCKET_ADDRESS_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsString;

class CS_CORE_EXPORT CsSockAddr :public CsObject
{
	friend class CsSocket;
	friend class CsTcpSocket;
	friend class CsUdpSocket;

public:
	explicit CsSockAddr();
	explicit CsSockAddr(const CsString &sIP, cs_ushort nPort);
	~CsSockAddr();
	void SetIP(const CsString sIP);
	void SetIP(const cs_uint nIP);
	void SetPortID(const cs_ushort nPort);

public:
	enum { CLASSCODE = CORE_CLASSCODE_SOCKET_ADDRESS, };
};

#endif // _CSCORE_CSSOCKET_ADDRESS_H_