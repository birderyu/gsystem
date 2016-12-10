#ifndef _CORE_SOCKET_EX_H_
#define _CORE_SOCKET_EX_H_

#include "CsSockAddress_Ex.h"

class CsSocket_Ex
{
public:
	CsSocket_Ex();
	virtual ~CsSocket_Ex() = 0  ;
	cs_int SetRecvTimeout(cs_int nMsecs);
	cs_int GetRecvTimeout() const;

	cs_int SetSendTimeout(cs_int nMsecs);
	cs_int GetSendTimeout() const;

	cs_int SetReuseAddr(cs_bool nResue);

	cs_int GetPeerAddr(CsSockAddress_Ex *pSockAddr) const;
	cs_int GetLocalAddr(CsSockAddress_Ex *pSockAddr) const;

protected:
	// 套接字的句柄
	TSocket m_hSocket;
};

#endif // _CORE_SOCKET_EX_H_