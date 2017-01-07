#ifndef _CORE_NEW_INLINE_
#define _CORE_NEW_INLINE_

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
inline gpointer GNewT<ClassT>::operator new(gsize size)
throw(std::bad_alloc)
{
	return GMalloc(size);
}

template<typename ClassT>
inline gvoid GNewT<ClassT>::operator delete(gpointer free)
{
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
GMemoryPool GNewInPoolT<ClassT>::pool = GMemoryPool(sizeof(ClassT));

template<typename ClassT>
inline gpointer GNewInPoolT<ClassT>::operator new(gsize)
throw(std::bad_alloc)
{
	gpointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT>
inline gvoid GNewInPoolT<ClassT>::operator delete(gpointer free)
{
	if (free == NULL)
	{
		return;
	}
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler GNewWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
inline std::new_handler GNewWithHandlerT<ClassT>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT>
inline gpointer GNewWithHandlerT<ClassT>::operator new(gsize size) throw(std::bad_alloc)
{
	GNewHander h(std::set_new_handler(currentHandler));
	return GMalloc(size);
}

template<typename ClassT>
inline gvoid GNewWithHandlerT<ClassT>::operator delete(gpointer free)
{
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler GNewInPoolWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
GMemoryPool GNewInPoolWithHandlerT<ClassT>::pool = GMemoryPool(sizeof(ClassT));

template<typename ClassT>
inline gpointer GNewInPoolWithHandlerT<ClassT>::operator new(gsize size) throw(std::bad_alloc)
{
	GNewHander h(std::set_new_handler(currentHandler));
	gpointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT>
inline gvoid GNewInPoolWithHandlerT<ClassT>::operator delete(gpointer free)
{
	if (free == NULL)
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
inline gpointer GSafeNewT<ClassT, LockT>::operator new(gsize size)
throw(std::bad_alloc)
{
	GLockGuard<LockT> autolock(lock);
	return GMalloc(size);
}

template<typename ClassT, typename LockT>
inline gvoid GSafeNewT<ClassT, LockT>::operator delete(gpointer free)
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
inline std::new_handler GSafeNewWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
inline gpointer GSafeNewWithHandlerT<ClassT, LockT>::operator new(gsize size)
throw(std::bad_alloc)
{
	GNewHander h(std::set_new_handler(currentHandler));

	GLockGuard<LockT> autolock(lock);
	return GMalloc(size);
}

template<typename ClassT, typename LockT>
inline gvoid GSafeNewWithHandlerT<ClassT, LockT>::operator delete(gpointer free)
{
	GLockGuard<LockT> autolock(lock);
	GFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
LockT GSafeNewInPoolT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
GMemoryPool GSafeNewInPoolT<ClassT, LockT>::pool = GMemoryPool(sizeof(ClassT));

template<typename ClassT, typename LockT>
inline gpointer GSafeNewInPoolT<ClassT, LockT>::operator new(gsize)
throw(std::bad_alloc)
{
	GLockGuard<LockT> autolock(lock);
	gpointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT, typename LockT>
inline gvoid GSafeNewInPoolT<ClassT, LockT>::operator delete(gpointer free)
{
	if (free == NULL)
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
GMemoryPool GSafeNewInPoolWithHandlerT<ClassT, LockT>::pool = GMemoryPool(sizeof(ClassT));

template<typename ClassT, typename LockT>
inline std::new_handler GSafeNewInPoolWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
inline gpointer GSafeNewInPoolWithHandlerT<ClassT, LockT>::operator new(gsize)
throw(std::bad_alloc)
{
	GNewHander h(std::set_new_handler(currentHandler));

	GLockGuard<LockT> autolock(lock);
	gpointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT, typename LockT>
inline gvoid GSafeNewInPoolWithHandlerT<ClassT, LockT>::operator delete(gpointer free)
{
	if (free == NULL)
	{
		return;
	}
	GLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

#endif // _CORE_NEW_INLINE_