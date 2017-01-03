#ifndef _CORE_UDPSOCKET_H_
#define _CORE_UDPSOCKET_H_

#include "CsSocket.h"

class CS_API CsUdpSocket final
	: public CsSocket
{
public:
	CsUdpSocket();

	cs_bool Open(cs_bool nResue = false);
	cs_bool Open(const CsSockAddress &tSockAddr, cs_bool nResue = false);
	cs_void Close();

	cs_bool SendTo(const cs_char *pBufData, cs_int nLen, const CsSockAddress &tPeer);
	cs_int RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress &tPeer);
};

#endif // _CORE_UDPSOCKET_H_