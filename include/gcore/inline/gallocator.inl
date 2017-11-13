#ifndef _CORE_ALLOCATOR_INLINE_
#define _CORE_ALLOCATOR_INLINE_

#include <exception>

namespace gsystem { // gsystem

template <typename ClassT> GINLINE
ClassT *GAllocate(gsize n) GEXCEPT(false)
{
	gptr ptr = GMalloc(n * sizeof(ClassT));
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return static_cast<ClassT *>(ptr);
}

template <typename ClassT> GINLINE 
gvoid GDeallocate(ClassT *ptr) GNOEXCEPT
{
	GFree(ptr);
}

template <typename ClassT> GINLINE 
ClassT *GReallocate(ClassT *oldptr, gsize n) GEXCEPT(false)
{
	gptr ptr = GRealloc(oldptr, n * sizeof(ClassT));
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return static_cast<ClassT *>(ptr);
}

template <typename ClassT> GINLINE
ClassT *GAllocator<ClassT>::Allocate(gsize n) GEXCEPT(false)
{
	return GAllocate<ClassT>(n);
}

template <typename ClassT> GINLINE
gvoid GAllocator<ClassT>::Deallocate(ClassT *ptr) GNOEXCEPT
{
	GDeallocate<ClassT>(ptr);
}

template <typename ClassT> GINLINE
ClassT *GAllocator<ClassT>::Reallocate(ClassT *oldptr, gsize n) GEXCEPT(false)
{
	return GReallocate<ClassT>(oldptr, n);
}

} // namespace gsystem

#endif // _CORE_ALLOCATOR_INLINE_

