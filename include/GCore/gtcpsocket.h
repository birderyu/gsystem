#ifndef _CORE_TCP_SOCKET_H_
#define _CORE_TCP_SOCKET_H_

#include "gsocket.h"

namespace gsystem { // gsystem

class GAPI GTcpSocket final
	: public GSocket
{
public:
	GTcpSocket();

	gbool Open(gbool resue = false);
	gbool Open(const GSocketAddress &addr, gbool resue = false);
	gvoid Close();

	// 服务器
	gbool Listen(gint back_log = 16);
	gbool Accept(const GTcpSocket &peer);

	// 客户端
	gbool Connect(const GSocketAddress &addr);

	// 发送接收，返回值为字节的数量
	gint Send(gcbytes buf, gsize size);
	gint Recv(gbytes buf, gsize size, gbool wait_all = false);
};

} // namespace gsystem

#endif // _CORE_TCP_SOCKET_H_