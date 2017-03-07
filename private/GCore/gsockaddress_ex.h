#ifndef _CORE_SOCKETADDRESS_EX_H_
#define _CORE_SOCKETADDRESS_EX_H_

#include "gglobal_ex.h"

#ifdef G_SYSTEM_WINDOWS

#ifndef  _WINSOCK_DEPRECATED_NO_WARNINGS
#	define  _WINSOCK_DEPRECATED_NO_WARNINGS
#endif // _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET				gsocket;
#define GOpenSocket			socket
#define GCloseSocket		closesocket
#define GControlSocketIO	ioctlsocket
#else // !G_SYSTEM_WINDOWS
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
typedef gint gsocket;
#define GOpenSocket			socket
#define GCloseSocket		close
#define GControlSocketIO	ioctl
#endif // G_SYSTEM_WINDOWS

#define GBindSocket			bind
#define GListenSocket		listen
#define GAcceptSocket		accept
#define GConnectSocket		connect
#define GSendSocket			send
#define GRecvSocket			recv
#define GSendToSocket		sendto
#define GRecvFromSocket		recvfrom
#define GSetSocketOpt		setsockopt
#define GGetSocketOpt		getsockopt

class GString;

class GSockAddress_Ex
{
	friend class GSocket_Ex;
	friend class GTcpSocket_Ex;
	friend class GUdpSocket_Ex;

public:
	GSockAddress_Ex();
	GSockAddress_Ex(const GString &sIP, gushort nPort);

	gvoid SetIP(const GString &sIP);
	gvoid SetIP(guint nIP);
	gvoid SetPortID(gushort nPort);

private:
	sockaddr_in m_tSocketAddr;
};

#endif // _CORE_SOCKETADDRESS_EX_H_