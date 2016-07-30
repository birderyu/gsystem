#ifndef _CSCORE_CSTHREAD_PRIVATE_H_
#define _CSCORE_CSTHREAD_PRIVATE_H_

#include "CsObject_Private.h"

class CsThread;

class CsThread_Private :public CsObject_Private
{
public:
	CsThread_Private(CsThread *pPublic);
	~CsThread_Private();

	/// 创建线程并启动
	virtual cs_int Start();
	virtual void Stop(cs_ulong nMsecs);

	/// 让当前线程睡眠，单位：秒
	static void Sleep(cs_ulong nSecs);

	/// 让当前线程睡眠，单位：毫秒
	static void MSleep(cs_ulong nMsecs);

	/// 回收指定的线程
	static void Join(CsThread_Private *pThread);

private:
	/// 当前线程体的句柄，在不同的操作系统下使用不同的结构
	void *m_pHandle;
};

#endif // _CSCORE_CSTHREAD_PRIVATE_H_