#ifndef _CORE_SOCKETADDRESS_PRIVATE_H_
#define _CORE_SOCKETADDRESS_PRIVATE_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET TSocket;
#define _OpenSocket			socket
#define _CloseSocket		closesocket
#define _ControlSocketIO	ioctlsocket
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
typedef cs_int TSocket;
#define _OpenSocket			socket
#define _CloseSocket		close
#define _ControlSocketIO	ioctl
#endif
#define _BindSocket		bind
#define _ListenSocket	listen
#define _AcceptSocket	accept
#define _ConnectSocket	connect
#define _SendSocket		send
#define _RecvSocket		recv
#define _SendToSocket	sendto
#define _RecvFromSocket	recvfrom
#define _SetSocketOpt	setsockopt
#define _GetSocketOpt	getsockopt

#include "CsGlobal_Ex.h"

class CsString;

class CsSockAddress_Ex
{
	friend class CsSocket_Ex;
	friend class CsTcpSocket_Ex;
	friend class CsUdpSocket_Ex;

public:
	CsSockAddress_Ex();
	CsSockAddress_Ex(const CsString &sIP, cs_ushort nPort);

	cs_void SetIP(const CsString &sIP);
	cs_void SetIP(cs_uint nIP);
	cs_void SetPortID(cs_ushort nPort);

private:
	sockaddr_in m_tSocketAddr;
};

#endif // _CORE_SOCKETADDRESS_PRIVATE_H_