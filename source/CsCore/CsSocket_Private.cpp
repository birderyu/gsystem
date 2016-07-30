#include "CsSocket_Private.h"
#include "CsSocket.h"

#ifdef _WIN32
// Windows下使用Socket需要先初始化
#pragma comment(lib,"ws2_32")
class CsSocketInit
{
public:
	CsSocketInit()
	{
		WSADATA tWsaData;
		int nResult = WSAStartup(MAKEWORD(2, 2), &tWsaData);
		if (nResult != NO_ERROR)
		{

		}
	}
	~CsSocketInit()
	{
		WSACleanup();
	}
};
static CsSocketInit g_tSocket_Init_Win32;
#endif

CsSocket_Private::CsSocket_Private(CsSocket *pPublic)
:CsObject_Private(pPublic), m_hSocket(-1)
{

}

CsSocket_Private::~CsSocket_Private()
{

}

cs_int CsSocket_Private::SetRecvTimeout(const cs_int nMsecs)
{
#ifdef _WIN32
	if (_SetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(cs_char*)&nMsecs, sizeof(cs_int)) < 0)
	{
		return  -1;
	}
	return 0;
#else
	timeval tTimeValue;
	tTimeValue.tv_sec = nMsecs / 1000;
	tTimeValue.tv_usec = nMsecs % 1000 * 1000;
	if (_SetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(cs_char*)&tTimeValue, sizeof(timeval)) < 0)
	{
		return  -1;
	}
	return 0;
#endif
}

cs_int CsSocket_Private::GetRecvTimeout() const
{
#ifdef _WIN32
	cs_int nArgs = 0;
	socklen_t tArgsLen = sizeof(cs_int);
	if (_GetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(char*)&nArgs, &tArgsLen) < 0)
	{
		return  -1;
	}
	return nArgs;
#else
	timeval tTimeValue;
	socklen_t tTimeValueLen = sizeof(tTimeValue);
	if (_GetSocketOpt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO,
		(char*)&tTimeValue, &tTimeValueLen) < 0)
	{
		return  -1;
	}
	return tTimeValue.tv_sec * 1000 + tTimeValue.tv_usec / 1000;
#endif
}

cs_int CsSocket_Private::SetSendTimeout(const cs_int nMsecs)
{
#ifdef _WIN32
	if (_SetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(cs_char*)&nMsecs, sizeof(cs_int)) < 0)
	{
		return  -1;
	}
	return 0;
#else
	timeval tTimeValue;
	tTimeValue.tv_sec = nMsecs / 1000;
	tTimeValue.tv_usec = nMsecs % 1000 * 1000;
	if (_SetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(cs_char*)&tTimeValue, sizeof(timeval)) < 0)
	{
		return  -1;
	}
	return 0;
#endif
}

cs_int CsSocket_Private::GetSendTimeout() const
{
#ifdef _WIN32
	cs_int nArgs = 0;
	socklen_t tArgsLen = sizeof(cs_int);
	if (_GetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(char*)&nArgs, &tArgsLen) < 0)
	{
		return  -1;
	}
	return nArgs;
#else
	timeval tTimeValue;
	socklen_t tTimeValueLen = sizeof(tTimeValue);
	if (_GetSocketOpt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO,
		(char*)&tTimeValue, &tTimeValueLen) < 0)
	{
		return  -1;
	}
	return tTimeValue.tv_sec * 1000 + tTimeValue.tv_usec / 1000;
#endif
}

cs_int CsSocket_Private::SetReuseAddr(const cs_bool nResue)
{
	cs_int nOpt = nResue ? 1 : 0;
	socklen_t nLen = sizeof(nOpt);
	if (_SetSocketOpt(m_hSocket, SOL_SOCKET, SO_REUSEADDR,
		(char*)&nOpt, nLen) < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsSocket_Private::GetPeerAddr(CsSockAddress_Private *pSockAddr) const
{
	if (!pSockAddr)
	{
		return -1;
	}
	socklen_t nLen = sizeof(pSockAddr->m_tSocketAddr);
	if (getpeername(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), &nLen) < 0)
	{
		return -1;
	}
	return 0;
}

cs_int CsSocket_Private::GetLocalAddr(CsSockAddress_Private *pSockAddr) const
{
	if (!pSockAddr)
	{
		return -1;
	}
	socklen_t nLen = sizeof(pSockAddr->m_tSocketAddr);
	if (getsockname(m_hSocket, (sockaddr*)&(pSockAddr->m_tSocketAddr), &nLen) < 0)
	{
		return -1;
	}
	return 0;
}