/////////////////////////////////////////////////////////////////////////////////
/// @brief 线程类的定义
/// 
///  该文件中包含了线程类CsThread的定义
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_THREAD_H_
#define _CORE_THREAD_H_

#include "CsGlobal.h"

/// 线程类
class CS_API CsThread
{
public:
	CsThread();
	virtual ~CsThread();

	/// 创建线程并启动
	virtual cs_int Start();

	/// 终止一个线程
	virtual cs_void Stop(cs_ulong nMsecs = 0);

	/// 让当前线程睡眠，单位：秒
	static cs_void Sleep(cs_ulong nSecs);

	/// 让当前线程睡眠，单位：毫秒
	static cs_void MSleep(cs_ulong nMsecs);

	/// 回收指定的线程
	static cs_void Join(CsThread *pThread);

	/// 线程体主函数
	virtual cs_int Run() = 0;

private:
	/// 当前线程体的句柄，在不同的操作系统下使用不同的结构
	cs_pointer m_pHandle;
};

#endif // _CORE_THREAD_H_
