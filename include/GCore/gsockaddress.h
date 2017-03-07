#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "gobject.h"

G_BEGIN_NAMESPACE
class GString;
class GSockAddress_Ex;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

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
	GSockAddress_Ex *m_pSockAddress_Ex;
};

G_END_NAMESPACE

#endif // _CORE_SOCKET_ADDRESS_H_