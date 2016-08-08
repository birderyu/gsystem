#ifndef _CSCORE_CSSOCKET_H_
#define _CSCORE_CSSOCKET_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsSocket_Private;
class CsSockAddress;

class CS_CORE_EXPORT CsSocket :public CsObject
{
public:
	CsSocket(CsObject_Private *pPrivate);
	virtual ~CsSocket() = 0;

	cs_int SetRecvTimeout(const cs_int nMsecs);
	cs_int GetRecvTimeout() const;

	cs_int SetSendTimeout(const cs_int nMsecs);
	cs_int GetSendTimeout() const;

	cs_int SetReuseAddr(const cs_bool nResue);

	cs_int GetPeerAddr(CsSockAddress &tSockAddr) const;
	cs_int GetLocalAddr(CsSockAddress &tSockAddr) const;

public:
	enum { CLASSCODE = CORE_CLASSCODE_SOCKET, };
};

#endif // _CSCORE_CSSOCKET_H_
