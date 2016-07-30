#ifndef _CSCORE_CSUDPSOCKET_H_
#define _CSCORE_CSUDPSOCKET_H_

#include "CsSocket.h"

class CsCore_Export CsUdpSocket :public CsSocket
{
public:
	CsUdpSocket();
	virtual ~CsUdpSocket();

	cs_int Open(cs_bool nResue = false);
	cs_int Open(const CsSockAddress &tSockAddr, cs_bool nResue = false);
	void Close();
	cs_int SendTo(const void *pBufData, cs_int nLen, const CsSockAddress &tPeer);
	cs_int RecvFrom(void *pBufData, cs_int nMaxLen, CsSockAddress &tPeer);

public:
	enum { CLASSCODE = CORE_CLASSCODE_UDPSOCKET, };
};

#endif // _CSCORE_CSUDPSOCKET_H_