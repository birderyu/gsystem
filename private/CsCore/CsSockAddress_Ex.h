#ifndef _CORE_SOCKETADDRESS_EX_H_
#define _CORE_SOCKETADDRESS_EX_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET TSocket;
#define CsOpenSocket		socket
#define CsCloseSocket		closesocket
#define CsControlSocketIO	ioctlsocket
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
typedef gint TSocket;
#define CsOpenSocket		socket
#define CsCloseSocket		close
#define CsControlSocketIO	ioctl
#endif
#define CsBindSocket		bind
#define CsListenSocket		listen
#define CsAcceptSocket		accept
#define CsConnectSocket		connect
#define CsSendSocket		send
#define CsRecvSocket		recv
#define CsSendToSocket		sendto
#define CsRecvFromSocket	recvfrom
#define CsSetSocketOpt		setsockopt
#define CsGetSocketOpt		getsockopt

#include "CsGlobal_Ex.h"

class GString;

class CsSockAddress_Ex
{
	friend class CsSocket_Ex;
	friend class CsTcpSocket_Ex;
	friend class CsUdpSocket_Ex;

public:
	CsSockAddress_Ex();
	CsSockAddress_Ex(const GString &sIP, gushort nPort);

	gvoid SetIP(const GString &sIP);
	gvoid SetIP(guint nIP);
	gvoid SetPortID(gushort nPort);

private:
	sockaddr_in m_tSocketAddr;
};

#endif // _CORE_SOCKETADDRESS_EX_H_