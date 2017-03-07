#pragma once

#include "grunnable.h"
#include "gthread.h"
#include "gstring.h"

/// 一个派生自GRunnable的类
class GSelfThread : public GRunnable
{
public:
	GSelfThread(const GString &name)
		: name_(name)
	{

	}

protected:
	gint Run()
	{
		std::cout << name_.CString() << std::endl;
		return 0;
	}

private:
	GString name_;
};

/// 使用派生类的方式实现一个线程类
gvoid SelfThread_Test()
{
	GSelfThread task("use self thread.");
	task.Start();
	GThread::Sleep(5);
	task.Stop();
}

/// 使用绑定的方式实现一个线程类
gvoid BindThread_Test()
{
	GThread task;
	task.Start();
	GThread::Sleep(5);
	task.Stop();
}