/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsSocket.h
** @brief	套接字类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		CsSocket
**
****************************************************************************/

#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "CsGlobal.h"

class CsSocket_Ex;
class CsSockAddress;

/****************************************************************************
**
** CsSocket.h
**
** @class		CsSocket
** @brief		套接字类型
** @module		CsCore
**
** 提供了跨平台的套接字类的实现，该类是一个抽象类，包含两个具体的实现：
** CsTcpSocket {@see CsTcpSocket} 和CsUdpSocket {@see CsUdpSocket}。
**
****************************************************************************/
class CS_API CsSocket 
{
public:
	/****************************************************************************
	**
	** CsObject
	**
	** @name		CsSocket
	** @brief		构造函数（constructor）
	** @param[in]	socket_ex {CsSocket_Ex *} 私有实现类的指针，由子类传入。
	**
	****************************************************************************/
	CsSocket(CsSocket_Ex *socket_ex);
	virtual ~CsSocket() = 0;

	virtual cs_bool Open(cs_bool nResue = false) = 0;
	virtual cs_bool Open(const CsSockAddress &tSockAddr, cs_bool nResue = false) = 0;
	virtual cs_void Close() = 0;

	cs_bool SetRecvTimeout(cs_int nMsecs);
	cs_int	GetRecvTimeout() const;

	cs_bool SetSendTimeout(cs_int nMsecs);
	cs_int	GetSendTimeout() const;

	cs_bool SetReuseAddress(cs_bool nResue);

	cs_bool GetPeerAddr(CsSockAddress &tSockAddr) const;
	cs_bool GetLocalAddr(CsSockAddress &tSockAddr) const;

protected:
	CsSocket_Ex *m_pSocket_Ex;
};

#endif // _CSCORE_CSSOCKET_H_
