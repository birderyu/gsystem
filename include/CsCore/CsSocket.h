#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "CsObject.h"

class CsSocket_Ex;
class CsSockAddress;

class CS_API CsSocket 
	: public CsObject
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_SOCKET, };

public:
	virtual ~CsSocket() = 0;

	cs_int SetRecvTimeout(const cs_int nMsecs);
	cs_int GetRecvTimeout() const;

	cs_int SetSendTimeout(const cs_int nMsecs);
	cs_int GetSendTimeout() const;

	cs_int SetReuseAddr(const cs_bool nResue);

	cs_int GetPeerAddr(CsSockAddress &tSockAddr) const;
	cs_int GetLocalAddr(CsSockAddress &tSockAddr) const;

protected:
	CsSocket(CsSocket_Ex *);
	CsSocket_Ex *m_pSocket_Ex;
};

#endif // _CSCORE_CSSOCKET_H_
