#ifndef _CORE_SOCKET_ADDRESS_H_
#define _CORE_SOCKET_ADDRESS_H_

#include "gobject.h"

class GString;
class CsSockAddress_Ex;

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
	CsSockAddress_Ex *m_pSockAddress_Ex;
};

#endif // _CORE_SOCKET_ADDRESS_H_