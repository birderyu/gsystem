/////////////////////////////////////////////////////////////////////////////////
/// @brief 线程类的定义
/// 
///  该文件中包含了线程类CsThread的定义
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CSCORE_CSTHREAD_H_
#define _CSCORE_CSTHREAD_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

/// 线程类
class CS_CORE_EXPORT CsThread :public CsObject
{
public:
	CsThread();
	virtual ~CsThread();

	/// 创建线程并启动
	virtual cs_int Start();

	/// 终止一个线程
	virtual void Stop(cs_ulong nMsecs = 0);

	/// 让当前线程睡眠，单位：秒
	static void Sleep(cs_ulong nSecs);

	/// 让当前线程睡眠，单位：毫秒
	static void MSleep(cs_ulong nMsecs);

	/// 回收指定的线程
	static void Join(CsThread *pThread);

	/// 线程体主函数
	virtual int Run() = 0;

public:
	enum { CLASSCODE = CORE_CLASSCODE_THREAD, };
};

#endif // _CSCORE_CSTHREAD_H_
