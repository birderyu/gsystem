/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2015-2020, NARI Corporation. All rights reserved.
/// @brief 线程类在Win32下的实现
/// 
///  该文件中包含了线程类CsThread在Win32下的具体实现方法
///  在最底层使用函数_beginthreadex而非CreateThread去创建一个线程
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#include "CsThread.h"
#include "CsThread_Private.h"

CsThread::CsThread()
:CsObject(new CsThread_Private(this))
{

}

CsThread::~CsThread()
{

}

int CsThread::Start()
{
	CS_PRIVATE(CsThread);
	return pPrivate->Start();
}

void CsThread::Stop(cs_ulong nMsecs)
{
	CS_PRIVATE(CsThread);
	pPrivate->Stop(nMsecs);
}

void CsThread::Sleep(cs_ulong nSecs)
{
	CsThread_Private::Sleep(nSecs);
}

void CsThread::MSleep(cs_ulong nMsecs)
{
	CsThread_Private::MSleep(nMsecs);
}

void CsThread::Join(CsThread *pThread)
{
	CsThread_Private::Join((CsThread_Private*)pThread->GetPrivate());
}

int CsThread::Run()
{
	return 0;
}