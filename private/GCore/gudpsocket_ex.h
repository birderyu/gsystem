#ifndef _CORE_UDP_SOCKET_EX_H_
#define _CORE_UDP_SOCKET_EX_H_

#include "gsocket_ex.h"

class GUdpSocket_Ex 
	: public GSocket_Ex
{
public:
	gbool Open(gbool nResue);
	gbool Open(GSockAddress_Ex *pSockAddr, gbool nResue);
	gvoid Close();

	gbool SendTo(const gchar *pBufData, gint nLen, GSockAddress_Ex *pPeer);
	gint RecvFrom(gchar *pBufData, gint nMaxLen, GSockAddress_Ex *pPeer);
};

#endif // _CORE_UDP_SOCKET_EX_H_