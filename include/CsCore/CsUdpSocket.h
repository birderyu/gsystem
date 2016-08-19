#ifndef _CSCORE_CSUDPSOCKET_H_
#define _CSCORE_CSUDPSOCKET_H_

#include "CsSocket.h"

class CS_CORE_EXPORT CsUdpSocket :public CsSocket
{
public:
	CsUdpSocket();
	virtual ~CsUdpSocket();

	cs_int Open(cs_bool nResue = false);
	cs_int Open(const CsSockAddr &tSockAddr, cs_bool nResue = false);
	void Close();
	cs_int SendTo(const void *pBufData, cs_int nLen, const CsSockAddr &tPeer);
	cs_int RecvFrom(void *pBufData, cs_int nMaxLen, CsSockAddr &tPeer);

public:
	enum { CLASSCODE = CORE_CLASSCODE_UDPSOCKET, };
};

#endif // _CSCORE_CSUDPSOCKET_H_