#ifndef _CORE_TCP_SOCKET_EX_H_
#define _CORE_TCP_SOCKET_EX_H_

#include "CsSocket_Ex.h"

class CsTcpSocket_Ex 
	: public CsSocket_Ex
{
public:
	gbool Open(gbool nResue);
	gbool Open(CsSockAddress_Ex *pSockAddr, gbool nResue);
	gvoid Close();

	gbool Listen(gint nBackLog);
	gbool Accept(CsTcpSocket_Ex *pPeer);

	gbool Connect(CsSockAddress_Ex *pSockAddr);

	gint Send(const gchar *pBufData, gint nDataLen);
	gint Recv(gchar *pBufData, gint nDataLen, gint nWaitAll);
};

#endif // _CSCORE_CSTCPSOCKET_PRIVATE_H_