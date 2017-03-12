#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "gobject.h"

namespace gnova { // gnova
	namespace extra { // gnova.extra
		class GSockAddress_Ex;
	} // namespace gnova.extra
} // namespace gnova

namespace gnova { // gnova

class GAPI GSockAddress 
{
	friend class GSocket;
	friend class GTcpSocket;
	friend class GUdpSocket;

public:
	explicit GSockAddress();
	explicit GSockAddress(const GString &sIP, gushort nPort);
	~GSockAddress();
	gvoid SetIP(const GString sIP);
	gvoid SetIP(guint nIP);
	gvoid SetPortID(gushort nPort);

private:
	extra::GSockAddress_Ex *m_pSockAddress_Ex;
};

} // namespace gnova

#endif // _CORE_SOCKET_ADDRESS_H_