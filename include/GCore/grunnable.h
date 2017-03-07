/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	grunnable.h
** @brief	线程类的基类
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-02-05
** @version	1.0
** @see		GRunnable
**
** 若用户希望定义并启动一个线程类，只需要派生GRunnable，并重写Run方法即可。通过调用
** Start方法启动一个线程，在该线程体中会执行用户重写的Run方法；通过调用Stop方法关闭
** 已经启动的线程。若没有使用Stop方法关闭线程，就再次调用了Start方法，则旧的线程资源
** 将无法释放。
**
****************************************************************************/

#ifndef _CORE_RUNNABLE_H_
#define _CORE_RUNNABLE_H_

#include "gglobal.h"

class GThread;

/// 线程类
class GAPI GRunnable
{
	friend class GThread;

public:
	GRunnable();

	/****************************************************************************
	**
	** GRunnable
	**
	** @name	~GRunnable
	** @brief	析构函数（destructor）
	**
	** 析构函数中会自动关闭当前线程
	**
	****************************************************************************/
	virtual ~GRunnable();

	/// 创建线程并启动
	virtual gbool Start();

	/// 终止一个线程
	virtual gvoid Stop(gulong msecs = 0);

	/// 线程体主函数
	virtual gint Run() = 0;

private:
	/// 当前线程体的句柄，在不同的操作系统下使用不同的结构
	gpointer m_pHandle;
};

#endif // _CORE_RUNNABLE_H_
