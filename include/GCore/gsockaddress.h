#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "gobject.h"

namespace gsystem { // gsystem
	namespace detail { // gsystem.detail
		class GSockAddress_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

class GAPI GSockAddress 
{
	friend class GSocket;
	friend class GTcpSocket;
	friend class GUdpSocket;

public:
	explicit GSockAddress();
	explicit GSockAddress(const GString &ip, guint16 port);
	GSockAddress(const GSockAddress &addr);
	GSockAddress(GSockAddress &&addr);


	~GSockAddress();
	gvoid SetIP(const GString &ip);
	gvoid SetIP(guint ip);
	gvoid SetPortID(guint16 nPort);

private:
	detail::GSockAddress_Ex *m_pSockAddress_Ex;
};

} // namespace gsystem

#endif // _CORE_SOCKET_ADDRESS_H_