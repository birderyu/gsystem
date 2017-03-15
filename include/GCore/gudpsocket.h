#ifndef _CORE_UDP_SOCKET_H_
#define _CORE_UDP_SOCKET_H_

#include "gsocket.h"

namespace gsystem { // gsystem

class GAPI GUdpSocket final
	: public GSocket
{
public:
	GUdpSocket();

	gbool Open(gbool nResue = false);
	gbool Open(const GSockAddress &tSockAddr, gbool nResue = false);
	gvoid Close();

	gbool SendTo(const gchar *pBufData, gint nLen, const GSockAddress &tPeer);
	gint RecvFrom(gchar *pBufData, gint nMaxLen, GSockAddress &tPeer);
};

} // namespace gsystem

#endif // _CORE_UDP_SOCKET_H_