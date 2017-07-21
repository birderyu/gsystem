/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gsocket.h
** @brief 套接字接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2015-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GSocketAddress;
	namespace detail { // gsystem.detail
		class GSocket_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 套接字
**
** 跨平台的套接字，该类是一个抽象类，包含两个具体的实现：GTcpSocket和GUdpSocket
**
********************************************************************************/
class GAPI GSocket
{
public:
	/****************************************************************************
	**
	** @name ~GSocket
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GSocket();

	/****************************************************************************
	**
	** @name Open
	** @brief 打开套接字
	** @param [in] resue {gbool} 端口是否可以重用，默认不可重用
	** @return {gbool} 若打开成功，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Open(gbool resue = false) = 0;

	/****************************************************************************
	**
	** @name Open
	** @brief 打开套接字
	** @param [in] addr {const GSocketAddress &} 地址
	** @param [in] resue {gbool} 端口是否可以重用，默认不可重用
	** @return {gbool} 若打开成功，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Open(const GSocketAddress &addr, gbool resue = false) = 0;

	/****************************************************************************
	**
	** @name Close
	** @brief 关闭套接字
	**
	****************************************************************************/
	virtual gvoid Close() = 0;

	gbool SetRecvTimeout(gint msecs);
	gint GetRecvTimeout() const;

	gbool SetSendTimeout(gint msecs);
	gint GetSendTimeout() const;

	gbool SetReuseAddress(gbool resue);

	GSocketAddress GetPeerAddr() const;
	GSocketAddress GetLocalAddr() const;

protected:
	/****************************************************************************
	**
	** @name GSocket
	** @brief 构造函数（constructor）
	** @param [in] socket_ex {GSocket_Ex *} 套接字私有实现类
	**
	****************************************************************************/
	GSocket(detail::GSocket_Ex *socket_ex);

protected:
	/****************************************************************************
	**
	** 套接字私有实现类
	**
	****************************************************************************/
	detail::GSocket_Ex *m_pSocket_Ex;
};

} // namespace gsystem

#endif // _CORE_SOCKET_H_
