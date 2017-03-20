#ifndef _CORE_SOCKET_EX_H_
#define _CORE_SOCKET_EX_H_

#include "gsockaddress_ex.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GSocket_Ex
{
public:
	GSocket_Ex();
	virtual ~GSocket_Ex() = 0;

	gbool SetRecvTimeout(gint msecs);
	gint  GetRecvTimeout() const;

	gbool SetSendTimeout(gint msecs);
	gint  GetSendTimeout() const;

	gbool SetReuseAddress(gbool resue);

	gbool GetPeerAddr(GSockAddress_Ex &addr) const;
	gbool GetLocalAddr(GSockAddress_Ex &addr) const;

protected:
	// 套接字的句柄
	gsocket m_hSocket;
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_SOCKET_EX_H_