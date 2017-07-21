#ifndef _CORE_UDP_SOCKET_H_
#define _CORE_UDP_SOCKET_H_

#include "gsocket.h"

namespace gsystem { // gsystem

class GAPI GUdpSocket final
	: public GSocket
{
public:
	GUdpSocket();

	gbool Open(gbool resue = false);
	gbool Open(const GSocketAddress &addr, gbool resue = false);
	gvoid Close();

	gbool SendTo(gcbytes buf, gsize size, const GSocketAddress &peer);
	gint RecvFrom(gbytes buf, gsize max_size, GSocketAddress &peer);
};

} // namespace gsystem

#endif // _CORE_UDP_SOCKET_H_