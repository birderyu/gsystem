#ifndef _CORE_UDP_SOCKET_EX_H_
#define _CORE_UDP_SOCKET_EX_H_

#include "CsSocket_Ex.h"

class CsUdpSocket_Ex 
	: public CsSocket_Ex
{
public:
	gbool Open(gbool nResue);
	gbool Open(CsSockAddress_Ex *pSockAddr, gbool nResue);
	gvoid Close();

	gbool SendTo(const gchar *pBufData, gint nLen, CsSockAddress_Ex *pPeer);
	gint RecvFrom(gchar *pBufData, gint nMaxLen, CsSockAddress_Ex *pPeer);
};

#endif // _CORE_UDP_SOCKET_EX_H_