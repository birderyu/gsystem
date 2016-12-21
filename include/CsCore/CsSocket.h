#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "CsObject.h"

class CsSocket_Ex;
class CsSockAddress;

class CS_API CsSocket 
{
public:
	virtual ~CsSocket() = 0;

	virtual cs_bool Open(cs_bool nResue = false) = 0;
	virtual cs_bool Open(const CsSockAddress &tSockAddr, cs_bool nResue = false) = 0;
	virtual cs_void Close() = 0;

	cs_bool SetRecvTimeout(cs_int nMsecs);
	cs_int	GetRecvTimeout() const;

	cs_bool SetSendTimeout(cs_int nMsecs);
	cs_int	GetSendTimeout() const;

	cs_bool SetReuseAddress(cs_bool nResue);

	cs_bool GetPeerAddr(CsSockAddress &tSockAddr) const;
	cs_bool GetLocalAddr(CsSockAddress &tSockAddr) const;

protected:
	CsSocket(CsSocket_Ex *);
	CsSocket_Ex *m_pSocket_Ex;
};

#endif // _CSCORE_CSSOCKET_H_
