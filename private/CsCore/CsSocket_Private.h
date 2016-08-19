#ifndef _CSCORE_CSSOCKET_PRIVATE_H_
#define _CSCORE_CSSOCKET_PRIVATE_H_

#include "CsObject_Private.h"
#include "CsSockAddr_Private.h"

class CsSocket;

class CsSocket_Private :public CsObject_Private
{
public:
	CsSocket_Private(CsSocket *pPublic);
	virtual ~CsSocket_Private();
	cs_int SetRecvTimeout(const cs_int nMsecs);
	cs_int GetRecvTimeout() const;

	cs_int SetSendTimeout(const cs_int nMsecs);
	cs_int GetSendTimeout() const;

	cs_int SetReuseAddr(const cs_bool nResue);

	cs_int GetPeerAddr(CsSockAddr_Private *pSockAddr) const;
	cs_int GetLocalAddr(CsSockAddr_Private *pSockAddr) const;

protected:
	// 套接字的句柄
	TSocket m_hSocket;
};

#endif // _CSCORE_CSSOCKET_PRIVATE_H_