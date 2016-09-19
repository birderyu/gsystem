#ifndef _CSCORE_CSUDPSOCKET_PRIVATE_H_
#define _CSCORE_CSUDPSOCKET_PRIVATE_H_

#include "CsSocket_Private.h"

class CsUdpSocket;

class CsUdpSocket_Private :public CsSocket_Private
{
public:
	CsUdpSocket_Private(CsUdpSocket *pPublic);
	virtual ~CsUdpSocket_Private();

	cs_int Open(cs_bool nResue);
	cs_int Open(CsSockAddr_Private *pSockAddr, cs_bool nResue);
	cs_void Close();
	cs_int SendTo(cs_cpointer pBufData, cs_int nLen, CsSockAddr_Private *pPeer);
	cs_int RecvFrom(cs_pointer pBufData, cs_int nMaxLen, CsSockAddr_Private *pPeer);
};

#endif // _CSCORE_CSUDPSOCKET_PRIVATE_H_