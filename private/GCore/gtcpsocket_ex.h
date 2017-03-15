#ifndef _CORE_TCP_SOCKET_EX_H_
#define _CORE_TCP_SOCKET_EX_H_

#include "gsocket_ex.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GTcpSocket_Ex 
	: public GSocket_Ex
{
public:
	gbool Open(gbool nResue);
	gbool Open(GSockAddress_Ex *pSockAddr, gbool nResue);
	gvoid Close();

	gbool Listen(gint nBackLog);
	gbool Accept(GTcpSocket_Ex *pPeer);

	gbool Connect(GSockAddress_Ex *pSockAddr);

	gint Send(const gchar *pBufData, gint nDataLen);
	gint Recv(gchar *pBufData, gint nDataLen, gint nWaitAll);
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_TCP_SOCKET_EX_H_