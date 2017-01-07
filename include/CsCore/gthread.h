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

#include "gglobal.h"

/// 线程类
class GAPI GThread
{
public:
	GThread();
	virtual ~GThread();

	/// 创建线程并启动
	virtual gint Start();

	/// 终止一个线程
	virtual gvoid Stop(gulong nMsecs = 0);

	/// 让当前线程睡眠，单位：秒
	static gvoid Sleep(gulong nSecs);

	/// 让当前线程睡眠，单位：毫秒
	static gvoid MSleep(gulong nMsecs);

	/// 回收指定的线程
	static gvoid Join(GThread *pThread);

	/// 线程体主函数
	virtual gint Run() = 0;

private:
	/// 当前线程体的句柄，在不同的操作系统下使用不同的结构
	gpointer m_pHandle;
};

#endif // _CORE_THREAD_H_
