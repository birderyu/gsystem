/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gsocket.h
** @brief	套接字类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		GSocket
**
****************************************************************************/

#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "gglobal.h"

G_BEGIN_NAMESPACE
class GSocket_Ex;
class GSockAddress;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

/****************************************************************************
**
** gsocket.h
**
** @class		GSocket
** @brief		套接字类型
** @module		GCore
**
** 提供了跨平台的套接字类的实现，该类是一个抽象类，包含两个具体的实现：
** GTcpSocket {@see GTcpSocket} 和GUdpSocket {@see GUdpSocket}。
**
****************************************************************************/
class GAPI GSocket
{
public:
	/****************************************************************************
	**
	** GSocket
	**
	** @name		GSocket
	** @brief		构造函数（constructor）
	** @param[in]	socket_ex {GSocket_Ex *} 私有实现类的指针，由子类传入。
	**
	****************************************************************************/
	GSocket(GSocket_Ex *socket_ex);
	virtual ~GSocket() = 0;

	virtual gbool Open(gbool nResue = false) = 0;
	virtual gbool Open(const GSockAddress &tSockAddr, gbool nResue = false) = 0;
	virtual gvoid Close() = 0;

	gbool SetRecvTimeout(gint nMsecs);
	gint GetRecvTimeout() const;

	gbool SetSendTimeout(gint nMsecs);
	gint GetSendTimeout() const;

	gbool SetReuseAddress(gbool nResue);

	gbool GetPeerAddr(GSockAddress &tSockAddr) const;
	gbool GetLocalAddr(GSockAddress &tSockAddr) const;

protected:
	GSocket_Ex *m_pSocket_Ex;
};

G_END_NAMESPACE

#endif // _CORE_SOCKET_H_
