#ifndef _CORE_SOCKET_EX_H_
#define _CORE_SOCKET_EX_H_

#include "CsSockAddress_Ex.h"

class CsSocket_Ex
{
public:
	CsSocket_Ex();
	virtual ~CsSocket_Ex() = 0;

	gbool SetRecvTimeout(gint nMsecs);
	gint  GetRecvTimeout() const;

	gbool SetSendTimeout(gint nMsecs);
	gint  GetSendTimeout() const;

	gbool SetReuseAddress(gbool nResue);

	gbool GetPeerAddr(CsSockAddress_Ex *pSockAddr) const;
	gbool GetLocalAddr(CsSockAddress_Ex *pSockAddr) const;

protected:
	// 套接字的句柄
	TSocket m_hSocket;
};

#endif // _CORE_SOCKET_EX_H_