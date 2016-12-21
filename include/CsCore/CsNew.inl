#ifndef _CORE_NEW_INLINE_
#define _CORE_NEW_INLINE_

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
inline cs_pointer CsNewT<ClassT>::operator new(cs_size_t size)
throw(std::bad_alloc)
{
	return CsMalloc(size);
}

template<typename ClassT>
inline cs_void CsNewT<ClassT>::operator delete(cs_pointer free)
{
	CsFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
CsMemoryPool CsNewInPoolT<ClassT>::pool = CsMemoryPool(sizeof(ClassT));

template<typename ClassT>
inline cs_pointer CsNewInPoolT<ClassT>::operator new(cs_size_t)
throw(std::bad_alloc)
{
	cs_pointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT>
inline cs_void CsNewInPoolT<ClassT>::operator delete(cs_pointer free)
{
	if (free == NULL)
	{
		return;
	}
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler CsNewWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
inline std::new_handler CsNewWithHandlerT<ClassT>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT>
inline cs_pointer CsNewWithHandlerT<ClassT>::operator new(cs_size_t size) throw(std::bad_alloc)
{
	CsNewHander h(std::set_new_handler(currentHandler));
	return CsMalloc(size);
}

template<typename ClassT>
inline cs_void CsNewWithHandlerT<ClassT>::operator delete(cs_pointer free)
{
	CsFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT>
std::new_handler CsNewInPoolWithHandlerT<ClassT>::currentHandler;

template<typename ClassT>
CsMemoryPool CsNewInPoolWithHandlerT<ClassT>::pool = CsMemoryPool(sizeof(ClassT));

template<typename ClassT>
inline cs_pointer CsNewInPoolWithHandlerT<ClassT>::operator new(cs_size_t size) throw(std::bad_alloc)
{
	CsNewHander h(std::set_new_handler(currentHandler));
	cs_pointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT>
inline cs_void CsNewInPoolWithHandlerT<ClassT>::operator delete(cs_pointer free)
{
	if (free == NULL)
	{
		return;
	}
	CsLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
LockT CsSafeNewT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
inline cs_pointer CsSafeNewT<ClassT, LockT>::operator new(cs_size_t size)
throw(std::bad_alloc)
{
	CsLockGuard<LockT> autolock(lock);
	return CsMalloc(size);
}

template<typename ClassT, typename LockT>
inline cs_void CsSafeNewT<ClassT, LockT>::operator delete(cs_pointer free)
{
	CsLockGuard<LockT> autolock(lock);
	CsFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
std::new_handler CsSafeNewWithHandlerT<ClassT, LockT>::currentHandler;

template<typename ClassT, typename LockT>
LockT CsSafeNewWithHandlerT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
inline std::new_handler CsSafeNewWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
inline cs_pointer CsSafeNewWithHandlerT<ClassT, LockT>::operator new(cs_size_t size)
throw(std::bad_alloc)
{
	CsNewHander h(std::set_new_handler(currentHandler));

	CsLockGuard<LockT> autolock(lock);
	return CsMalloc(size);
}

template<typename ClassT, typename LockT>
inline cs_void CsSafeNewWithHandlerT<ClassT, LockT>::operator delete(cs_pointer free)
{
	CsLockGuard<LockT> autolock(lock);
	CsFree(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
LockT CsSafeNewInPoolT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
CsMemoryPool CsSafeNewInPoolT<ClassT, LockT>::pool = CsMemoryPool(sizeof(ClassT));

template<typename ClassT, typename LockT>
inline cs_pointer CsSafeNewInPoolT<ClassT, LockT>::operator new(cs_size_t)
throw(std::bad_alloc)
{
	CsLockGuard<LockT> autolock(lock);
	cs_pointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT, typename LockT>
inline cs_void CsSafeNewInPoolT<ClassT, LockT>::operator delete(cs_pointer free)
{
	if (free == NULL)
	{
		return;
	}
	CsLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

//////////////////////////////////////////////////////////////////////////
template<typename ClassT, typename LockT>
std::new_handler CsSafeNewInPoolWithHandlerT<ClassT, LockT>::currentHandler;

template<typename ClassT, typename LockT>
LockT CsSafeNewInPoolWithHandlerT<ClassT, LockT>::lock;

template<typename ClassT, typename LockT>
CsMemoryPool CsSafeNewInPoolWithHandlerT<ClassT, LockT>::pool = CsMemoryPool(sizeof(ClassT));

template<typename ClassT, typename LockT>
inline std::new_handler CsSafeNewInPoolWithHandlerT<ClassT, LockT>::set_new_handler(std::new_handler p)
throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename ClassT, typename LockT>
inline cs_pointer CsSafeNewInPoolWithHandlerT<ClassT, LockT>::operator new(cs_size_t)
throw(std::bad_alloc)
{
	CsNewHander h(std::set_new_handler(currentHandler));

	CsLockGuard<LockT> autolock(lock);
	cs_pointer pBuf = pool.Alloc();
	if (!pBuf)
	{
		throw std::bad_alloc();
	}
	return pBuf;
}

template<typename ClassT, typename LockT>
inline cs_void CsSafeNewInPoolWithHandlerT<ClassT, LockT>::operator delete(cs_pointer free)
{
	if (free == NULL)
	{
		return;
	}
	CsLockGuard<LockT> autolock(lock);
	pool.Free(free);
}

#endif // _CORE_NEW_INLINE_