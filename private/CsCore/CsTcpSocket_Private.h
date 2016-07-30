#ifndef _CSCORE_CSTCPSOCKET_PRIVATE_H_
#define _CSCORE_CSTCPSOCKET_PRIVATE_H_

#include "CsSocket_Private.h"

class CsTcpSocket;

class CsTcpSocket_Private :public CsSocket_Private
{
public:
	CsTcpSocket_Private(CsTcpSocket *pPublic);
	virtual ~CsTcpSocket_Private();

	cs_int Open(cs_bool nResue);
	cs_int Open(CsSockAddress_Private *pSockAddr, cs_bool nResue);
	void Close();

	cs_int Listen(cs_int nBackLog);
	cs_int Accept(CsTcpSocket_Private *pPeer);

	cs_int Connect(CsSockAddress_Private *pSockAddr);

	cs_int Send(const void *pBufData, cs_int nDataLen);
	cs_int Recv(void *pBufData, cs_int nDataLen, cs_int nWaitAll);
};

#endif // _CSCORE_CSTCPSOCKET_PRIVATE_H_