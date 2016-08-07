#ifndef _CSCORE_CSSOCKET_ADDRESS_H_
#define _CSCORE_CSSOCKET_ADDRESS_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsString;

class CsCore_Export CsSockAddress :public CsObject
{
	friend class CsSocket;
	friend class CsTcpSocket;
	friend class CsUdpSocket;

public:
	explicit CsSockAddress();
	explicit CsSockAddress(const CsString &sIP, cs_ushort nPort);
	~CsSockAddress();
	void SetIP(const CsString sIP);
	void SetIP(const cs_uint nIP);
	void SetPortID(const cs_ushort nPort);

public:
	enum { CLASSCODE = CORE_CLASSCODE_SOCKET_ADDRESS, };
};

#endif // _CSCORE_CSSOCKET_ADDRESS_H_