#ifndef _CORE_UDP_SOCKET_EX_H_
#define _CORE_UDP_SOCKET_EX_H_

#include "gsocket_ex.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GUdpSocket_Ex 
	: public GSocket_Ex
{
public:
	gbool Open(gbool resue);
	gbool Open(GSockAddress_Ex *addr, gbool resue);
	gvoid Close();

	gbool SendTo(gcbytes buf, gsize size, GSockAddress_Ex *peer);
	gint RecvFrom(gbytes buf, gsize max_size, GSockAddress_Ex *peer);
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_UDP_SOCKET_EX_H_