/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2015-2020, NARI Corporation. All rights reserved.
/// @brief 线程类在Win32下的实现
/// 
///  该文件中包含了线程类CsThread_Private在Win32下的具体实现方法
///  在最底层使用函数_beginthreadex而非CreateThread去创建一个线程
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include "CsThread.h"
#include "CsNew.h"
#include <windows.h>
#include <process.h>

/// Win32进程实例句柄
struct CsThread_Handle : CsNewT<CsThread_Handle>
{
	HANDLE m_hThread;
};

cs_uint WINAPI ThreadProc4Win32(cs_pointer pParam)
{
	if (!pParam)
	{
		return 0;
	}
	CsThread* pThread = (CsThread*)pParam;
	pThread->Run();
	return 0;
}

CsThread::CsThread()
:m_pHandle(NULL)
{

}

CsThread::~CsThread()
{
	if (m_pHandle)
	{
		Stop(0);
		CsThread_Handle *pHandle = (CsThread_Handle*)m_pHandle;
		delete pHandle;
		m_pHandle = NULL;
	}
}

cs_int CsThread::Start()
{
	CsThread_Handle* pHandle = new CsThread_Handle;
	if (!pHandle)
	{
		return -1;
	}

	m_pHandle = pHandle;
	cs_uint nThreadAddr;
	pHandle->m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc4Win32, this, 0, &nThreadAddr);
	if (pHandle->m_hThread == NULL)
	{
		delete pHandle;
		pHandle = NULL;
		return -1;
	}
	return 0;
}

cs_void CsThread::Stop(cs_ulong nMsecs)
{
	CsThread_Handle *pHandle = (CsThread_Handle*)m_pHandle;
	if (!pHandle)
	{
		return;
	}
	if (WAIT_OBJECT_0 != WaitForSingleObject(pHandle->m_hThread, nMsecs))
	{
		TerminateThread(pHandle->m_hThread, 0);
	}
	CloseHandle(pHandle->m_hThread);
	pHandle->m_hThread = NULL;
}

cs_void CsThread::Sleep(cs_ulong nSecs)
{
	::Sleep(1000 * nSecs);
}

cs_void CsThread::MSleep(cs_ulong nMsecs)
{
	::Sleep(nMsecs);
}

cs_void CsThread::Join(CsThread *pThread)
{
	CsThread_Handle* pHandle = (CsThread_Handle*)pThread->m_pHandle;
	if (pHandle)
	{
		WaitForSingleObject(pHandle->m_hThread, INFINITE);
		delete pHandle;
		pThread->m_pHandle = NULL;
	}
}

#endif // _WIN32