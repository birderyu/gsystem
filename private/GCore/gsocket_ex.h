#ifndef _CORE_SOCKET_EX_H_
#define _CORE_SOCKET_EX_H_

#include "gsockaddress_ex.h"

class GSocket_Ex
{
public:
	GSocket_Ex();
	virtual ~GSocket_Ex() = 0;

	gbool SetRecvTimeout(gint nMsecs);
	gint  GetRecvTimeout() const;

	gbool SetSendTimeout(gint nMsecs);
	gint  GetSendTimeout() const;

	gbool SetReuseAddress(gbool nResue);

	gbool GetPeerAddr(GSockAddress_Ex *pSockAddr) const;
	gbool GetLocalAddr(GSockAddress_Ex *pSockAddr) const;

protected:
	// 套接字的句柄
	gsocket m_hSocket;
};

#endif // _CORE_SOCKET_EX_H_