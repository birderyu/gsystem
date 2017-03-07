#ifndef _CORE_NEW_H_
#define _CORE_NEW_H_

#include <new>
#include "gmemory.h"
#include "gmemorypool.h"
#include "glockguard.h"

G_BEGIN_NAMESPACE

// NewHandler
class GNewHander
{
public:
	explicit GNewHander(std::new_handler nh)
		: handler(nh) {}
	~GNewHander()
	{
		std::set_new_handler(handler);
	}

private:
	std::new_handler handler;
	GNewHander(const GNewHander&);
	GNewHander &operator=(const GNewHander&);
};

// 线程不安全
// 不分配到内存池
// 不带有NewHandler
template<typename ClassT>
class GNewT
{
public:
	static gpointer operator new(gsize) noexcept(false);
	static gvoid operator delete(gpointer) noexcept;
};

// 线程不安全
// 分配到内存池
// 不带有NewHandler
template<typename ClassT>
class GNewInPoolT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool<sizeof(ClassT)> pool;
};

// 线程不安全
// 不分配到内存池
// 带有NewHandler
template<typename ClassT>
class GNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
};

// 线程不安全
// 分配到内存池
// 带有NewHandler
template<typename ClassT>
class GNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool<sizeof(ClassT)> pool;
};

// 线程安全
// 不分配到内存池
// 不带有NewHandler
template<typename ClassT, typename LockT>
class GSafeNewT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static LockT lock;
};

// 线程安全
// 不分配到内存池
// 带有NewHandler
template<typename ClassT, typename LockT>
class GSafeNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static LockT lock;
};

// 线程安全
// 分配到内存池
// 不带有NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolT
{
public:
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool<sizeof(ClassT)> pool;
	static LockT lock;
};

// 线程安全
// 分配到内存池
// 带有NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p);
	static gpointer operator new(gsize);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool<sizeof(ClassT)> pool;
	static LockT lock;
};

#include "gnew.inl"

G_END_NAMESPACE

#endif // _CORE_NEW_H_
