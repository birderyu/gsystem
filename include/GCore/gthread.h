#ifndef _CORE_THREAD_H_
#define _CORE_THREAD_H_

#include "gglobal.h"
#include "grunnable.h"
#include "gnocopyable.h"

class GRunnable;

class GAPI GThread final
	: public GRunnable
	, private GNocopyable
{
public:
	/// 让当前线程睡眠，单位：秒
	static gvoid Sleep(gulong secs);

	/// 让当前线程睡眠，单位：毫秒
	static gvoid MSleep(gulong msecs);

	/// 回收指定的线程
	static gvoid Join(GRunnable &thread);

public:
	GThread();

	template<typename _Fn,
		typename... _Args,
		class = typename GEnableIf<
		!GIsSame<typename GDecay<_Fn>::Type, GThread>::value>::Type>
	GThread(_Fn&& _Fx, _Args&&... _Ax);
	GThread(GThread &&thread);
	~GThread();

	GThread &operator==(GThread &&thread);

	/// 执行体绑定
	gvoid Bind();

public:
	gbool Start();
	gvoid Stop(gulong msecs = 0);

private:
	gint Run();
};

#endif // _CORE_THREAD_H_
