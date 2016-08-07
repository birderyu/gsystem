#ifndef _CSCORE_CSSOCKETADDRESS_PRIVATE_H_
#define _CSCORE_CSSOCKETADDRESS_PRIVATE_H_

#include "CsObject_Private.h"

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

class CsString;
class CsSockAddress;

class CsSockAddress_Private :public CsObject_Private
{
	friend class CsSocket_Private;
	friend class CsTcpSocket_Private;
	friend class CsUdpSocket_Private;

public:
	CsSockAddress_Private(CsSockAddress *pPublic);
	CsSockAddress_Private(CsSockAddress *pPublic, const CsString &sIP, cs_ushort nPort);
	~CsSockAddress_Private();
	void SetIP(const CsString &sIP);
	void SetIP(const cs_uint nIP);
	void SetPortID(const cs_ushort nPort);

private:
	sockaddr_in m_tSocketAddr;
};

#endif // _CSCORE_CSSOCKETADDRESS_PRIVATE_H_