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
	explicit GSockAddress(const GString &sIP, gushort nPort);
	~GSockAddress();
	gvoid SetIP(const GString sIP);
	gvoid SetIP(guint nIP);
	gvoid SetPortID(gushort nPort);

private:
	detail::GSockAddress_Ex *m_pSockAddress_Ex;
};

} // namespace gsystem

#endif // _CORE_SOCKET_ADDRESS_H_