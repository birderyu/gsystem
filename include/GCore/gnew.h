#ifndef _CORE_NEW_H_
#define _CORE_NEW_H_

#include "gmemory.h"
#include "gmemorypool.h"
#include "glockguard.h"
#include <new>

namespace gsystem { // gsystem

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
	static gptr operator new(gsize) GEXCEPT(false);
	static gvoid operator delete(gptr)GNOEXCEPT;
};

// 线程不安全
// 分配到内存池
// 不带有NewHandler
template<typename ClassT>
class GNewInPoolT
{
public:
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

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
	static gptr operator new(gsize);
	static gvoid operator delete(gptr);

private:
	static std::new_handler currentHandler;
	static GMemoryPool<sizeof(ClassT)> pool;
	static LockT lock;
};

} // namespace gsystem

#include "gnew.inl"

#endif // _CORE_NEW_H_
