#include "gsocket_ex.h"
#include "gsocket.h"
#include "gsockaddress_ex.h"

#ifdef G_SYSTEM_WINDOWS
// Windows下使用Socket需要先初始化
#pragma comment(lib,"ws2_32")
class GSocketInit
{
public:
	GSocketInit()
	{
		WSADATA tWsaData;
		int nResult = WSAStartup(MAKEWORD(2, 2), &tWsaData);
		if (nResult != NO_ERROR)
		{

		}
	}
	~GSocketInit()
	{
		WSACleanup();
	}
};
static GSocketInit g_tSocket_Init_Win32;
#endif // G_SYSTEM_WINDOWS

GSocket_Ex::GSocket_Ex()
: m_hSocket(-1)
{

}

GSocket_Ex::~GSocket_Ex()
{

}

gbool GSocket_Ex::SetRecvTimeout(gint nMsecs)
{
#ifdef _WIN32
	if (GSetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(gchar*)&nMsecs, sizeof(gint)) < 0)
	{
		return  false;
	}
	return true;
#else
	timeval tTimeValue;
	tTimeValue.tv_sec = nMsecs / 1000;
	tTimeValue.tv_usec = nMsecs % 1000 * 1000;
	if (GSetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(gchar*)&tTimeValue, sizeof(timeval)) < 0)
	{
		return false;
	}
	return true;
#endif
}

gint GSocket_Ex::GetRecvTimeout() const
{
#ifdef _WIN32
	gint nArgs = 0;
	socklen_t tArgsLen = sizeof(gint);
	if (GGetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(gchar*)&nArgs, &tArgsLen) < 0)
	{
		return  -1;
	}
	return nArgs;
#else
	timeval tTimeValue;
	socklen_t tTimeValueLen = sizeof(tTimeValue);
	if (GGetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(gchar*)&tTimeValue, &tTimeValueLen) < 0)
	{
		return  -1;
	}
	return tTimeValue.tv_sec * 1000 + tTimeValue.tv_usec / 1000;
#endif
}

gbool GSocket_Ex::SetSendTimeout(gint nMsecs)
{
#ifdef _WIN32
	if (GSetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(gchar*)&nMsecs, sizeof(gint)) < 0)
	{
		return  false;
	}
	return true;
#else
	timeval tTimeValue;
	tTimeValue.tv_sec = nMsecs / 1000;
	tTimeValue.tv_usec = nMsecs % 1000 * 1000;
	if (GSetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(gchar*)&tTimeValue, sizeof(timeval)) < 0)
	{
		return false;
	}
	return true;
#endif
}

gint GSocket_Ex::GetSendTimeout() const
{
#ifdef _WIN32
	gint nArgs = 0;
	socklen_t tArgsLen = sizeof(gint);
	if (GGetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(gchar*)&nArgs, &tArgsLen) < 0)
	{
		return  -1;
	}
	return nArgs;
#else
	timeval tTimeValue;
	socklen_t tTimeValueLen = sizeof(tTimeValue);
	if (GGetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(gchar*)&tTimeValue, &tTimeValueLen) < 0)
	{
		return  -1;
	}
	return tTimeValue.tv_sec * 1000 + tTimeValue.tv_usec / 1000;
#endif
}

gbool GSocket_Ex::SetReuseAddress(gbool nResue)
{
	gint nOpt = nResue ? 1 : 0;
	socklen_t nLen = sizeof(nOpt);
	if (GSetSocketOpt(m_hSocket, SOL_SOCKET, SO_REUSEADDR,
		(char*)&nOpt, nLen) < 0)
	{
		return false;
	}
	return true;
}

gbool GSocket_Ex::GetPeerAddr(GSockAddress_Ex *pSockAddr) const
{
	if (!pSockAddr)
	{
		return false;
	}
	socklen_t nLen = sizeof(pSockAddr->m_tSocketAddr);
	if (getpeername(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), &nLen) < 0)
	{
		return false;
	}
	return true;
}

gbool GSocket_Ex::GetLocalAddr(GSockAddress_Ex *pSockAddr) const
{
	if (!pSockAddr)
	{
		return false;
	}
	socklen_t nLen = sizeof(pSockAddr->m_tSocketAddr);
	if (getsockname(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), &nLen) < 0)
	{
		return false;
	}
	return true;
}