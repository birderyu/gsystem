#ifndef _CORE_TCP_SOCKET_EX_H_
#define _CORE_TCP_SOCKET_EX_H_

#include "CsSocket_Ex.h"

class CsTcpSocket_Ex 
	: public CsSocket_Ex
{
public:
	cs_bool Open(cs_bool nResue);
	cs_bool Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue);
	cs_void Close();

	cs_bool Listen(cs_int nBackLog);
	cs_bool Accept(CsTcpSocket_Ex *pPeer);

	cs_bool Connect(CsSockAddress_Ex *pSockAddr);

	cs_int Send(const cs_char *pBufData, cs_int nDataLen);
	cs_int Recv(cs_char *pBufData, cs_int nDataLen, cs_int nWaitAll);
};

#endif // _CSCORE_CSTCPSOCKET_PRIVATE_H_