#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GString;
	namespace detail { // gsystem.detail
		class GSockAddress_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

class GAPI GSocketAddress 
{
	friend class GSocket;
	friend class GTcpSocket;
	friend class GUdpSocket;

public:
	explicit GSocketAddress();
	explicit GSocketAddress(const GString &ip, guint16 port);
	GSocketAddress(const GSocketAddress &addr);
	GSocketAddress(GSocketAddress &&addr);


	~GSocketAddress();
	gvoid SetIP(const GString &ip);
	gvoid SetIP(guint ip);
	gvoid SetPortID(guint16 nPort);

private:
	detail::GSockAddress_Ex *m_pSockAddress_Ex;
};

} // namespace gsystem

#endif // _CORE_SOCKET_ADDRESS_H_