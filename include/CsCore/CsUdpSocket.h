#ifndef _CSCORE_CSUDPSOCKET_H_
#define _CSCORE_CSUDPSOCKET_H_

#include "CsSocket.h"

class CS_API CsUdpSocket 
	: public CsSocket
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_UDPSOCKET, };

public:
	CsUdpSocket();

	cs_int Open(cs_bool nResue = false);
	cs_int Open(const CsSockAddress &tSockAddr, cs_bool nResue = false);
	void Close();
	cs_int SendTo(const cs_char *pBufData, cs_int nLen, const CsSockAddress &tPeer);
	cs_int RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress &tPeer);
};

#endif // _CSCORE_CSUDPSOCKET_H_