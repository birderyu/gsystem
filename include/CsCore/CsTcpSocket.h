#ifndef _CORE_TCPSOCKET_H_
#define _CORE_TCPSOCKET_H_

#include "CsSocket.h"

class CS_API CsTcpSocket final
	: public CsSocket
{
public:
	CsTcpSocket();

	cs_bool Open(cs_bool nResue = false);
	cs_bool Open(const CsSockAddress &tSockAddr, cs_bool nResue = false);
	cs_void Close();

	// 服务器
	cs_bool Listen(cs_int nBackLog = 16);
	cs_bool Accept(const CsTcpSocket &pPeer);

	// 客户端
	cs_bool Connect(const CsSockAddress &tSockAddr);

	// 发送接收
	cs_int Send(const cs_char *pBufData, cs_int nDataLen);
	cs_int Recv(cs_char *pBufData, cs_int nDataLen, cs_int nWaitAll = 0);
};

#endif // _CORE_TCPSOCKET_H_