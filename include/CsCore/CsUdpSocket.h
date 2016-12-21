#ifndef _CSCORE_CSUDPSOCKET_H_
#define _CSCORE_CSUDPSOCKET_H_

#include "CsSocket.h"

class CS_API CsUdpSocket 
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

#endif // _CSCORE_CSUDPSOCKET_H_