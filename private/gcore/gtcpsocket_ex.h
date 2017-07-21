#ifndef _CORE_TCP_SOCKET_EX_H_
#define _CORE_TCP_SOCKET_EX_H_

#include "gsocket_ex.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GTcpSocket_Ex 
	: public GSocket_Ex
{
public:
	gbool Open(gbool resue);
	gbool Open(GSockAddress_Ex *addr, gbool resue);
	gvoid Close();

	gbool Listen(gint back_log);
	gbool Accept(GTcpSocket_Ex *peer);

	gbool Connect(GSockAddress_Ex *addr);

	gint Send(gcbytes buf, gsize size);
	gint Recv(gbytes buf, gsize size, gbool wait_all);
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_TCP_SOCKET_EX_H_