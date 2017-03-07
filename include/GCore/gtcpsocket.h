#ifndef _CORE_TCP_SOCKET_H_
#define _CORE_TCP_SOCKET_H_

#include "gsocket.h"

G_BEGIN_NAMESPACE

class GAPI GTcpSocket final
	: public GSocket
{
public:
	GTcpSocket();

	gbool Open(gbool nResue = false);
	gbool Open(const GSockAddress &tSockAddr, gbool nResue = false);
	gvoid Close();

	// 服务器
	gbool Listen(gint nBackLog = 16);
	gbool Accept(const GTcpSocket &pPeer);

	// 客户端
	gbool Connect(const GSockAddress &tSockAddr);

	// 发送接收
	gint Send(const gchar *pBufData, gint nDataLen);
	gint Recv(gchar *pBufData, gint nDataLen, gint nWaitAll = 0);
};

G_END_NAMESPACE

#endif // _CORE_TCP_SOCKET_H_