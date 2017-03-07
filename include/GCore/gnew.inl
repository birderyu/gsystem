#ifndef _CORE_NEW_INLINE_
#define _CORE_NEW_INLINE_

template<typename ClassT>
GINLINE gpointer GNewT<ClassT>::operator new(gsize size) noexcept(false)
{
	gpointer ptr = GMalloc(size);
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT>
GINLINE gvoid GNewT<ClassT>::operator delete(gpointer ptr) noexcept
{
	GFree(ptr);
}

template<typename ClassT>
GMemoryPool<sizeof(ClassT)> GNewInPoolT<ClassT>::pool;

template<typename ClassT>
GINLINE gpointer GNewInPoolT<ClassT>::operator new(gsize)
{
	gpointer ptr = pool.Alloc();
	if (!ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT>
GINLINE gvoid GNewInPoolT<ClassT>::operator delete(gpointer free)
{
	if (free == GNULL)
	{
		return;
	}
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler GNewWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
GINLINE std::new_handler GNewWithHandlerT<ClassT>::set_new_handler(std::new_handler p)
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT>
GINLINE gpointer GNewWithHandlerT<ClassT>::operator new(gsize size)
{
	GNewHander h(std::set_new_handler(currentHandler));
	gpointer ptr = GMalloc(size);
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT>
GINLINE gvoid GNewWithHandlerT<ClassT>::operator delete(gpointer free)
{
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler GNewInPoolWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
GMemoryPool<sizeof(ClassT)> GNewInPoolWithHandlerT<ClassT>::pool;

template<typename ClassT>
GINLINE gpointer GNewInPoolWithHandlerT<ClassT>::operator new(gsize size)
{
	GNewHander h(std::set_new_handler(currentHandler));
	gpointer ptr = pool.Alloc();
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT>
GINLINE gvoid GNewInPoolWithHandlerT<ClassT>::operator delete(gpointer free)
{
	if (free == GNULL)
	{
		return;
	}
	GLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
LockT GSafeNewT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
GINLINE gpointer GSafeNewT<ClassT, LockT>::operator new(gsize size)
{
	GLockGuard<LockT> autolock(lock);
	gpointer ptr = GMalloc(size);
	if (nullptr == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT, typename LockT>
GINLINE gvoid GSafeNewT<ClassT, LockT>::operator delete(gpointer free)
{
	GLockGuard<LockT> autolock(lock);
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
std::new_handler GSafeNewWithHandlerT<ClassT, LockT>::currentHandler;

template<typename ClassT, typename LockT>
LockT GSafeNewWithHandlerT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
GINLINE std::new_handler GSafeNewWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
GINLINE gpointer GSafeNewWithHandlerT<ClassT, LockT>::operator new(gsize size)
{
	GNewHander h(std::set_new_handler(currentHandler));

	GLockGuard<LockT> autolock(lock);
	gpointer ptr = GMalloc(size);
	if (nullptr == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT, typename LockT>
GINLINE gvoid GSafeNewWithHandlerT<ClassT, LockT>::operator delete(gpointer free)
{
	GLockGuard<LockT> autolock(lock);
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
LockT GSafeNewInPoolT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
GMemoryPool<sizeof(ClassT)> GSafeNewInPoolT<ClassT, LockT>::pool;

template<typename ClassT, typename LockT>
GINLINE gpointer GSafeNewInPoolT<ClassT, LockT>::operator new(gsize)
{
	GLockGuard<LockT> autolock(lock);
	gpointer ptr = pool.Alloc();
	if (!ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT, typename LockT>
GINLINE gvoid GSafeNewInPoolT<ClassT, LockT>::operator delete(gpointer free)
{
	if (free == GNULL)
	{
		return;
	}
	GLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
std::new_handler GSafeNewInPoolWithHandlerT<ClassT, LockT>::currentHandler;

template<typename ClassT, typename LockT>
LockT GSafeNewInPoolWithHandlerT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
GMemoryPool<sizeof(ClassT)> GSafeNewInPoolWithHandlerT<ClassT, LockT>::pool;

template<typename ClassT, typename LockT>
GINLINE std::new_handler GSafeNewInPoolWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
GINLINE gpointer GSafeNewInPoolWithHandlerT<ClassT, LockT>::operator new(gsize)
{
	GNewHander h(std::set_new_handler(currentHandler));

	GLockGuard<LockT> autolock(lock);
	gpointer ptr = pool.Alloc();
	if (!ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template<typename ClassT, typename LockT>
GINLINE gvoid GSafeNewInPoolWithHandlerT<ClassT, LockT>::operator delete(gpointer free)
{
	if (free == GNULL)
	{
		return;
	}
	GLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

#endif // _CORE_NEW_INLINE_