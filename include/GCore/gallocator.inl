#ifndef _CORE_ALLOCATOR_INLINE_
#define _CORE_ALLOCATOR_INLINE_

#include <new>

namespace gsystem { // gsystem

template <typename ClassT>
GINLINE ClassT *GAllocate(gsize n) noexcept(false)
{
	ClassT *ptr = (ClassT *)GMalloc(n * sizeof(ClassT));
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

template <typename ClassT>
GINLINE gvoid GDeallocate(ClassT *ptr) noexcept
{
	GFree(ptr);
}

template <typename ClassT>
GINLINE ClassT *GReallocate(ClassT *oldptr, gsize n) noexcept(false)
{
	ClassT *ptr = (ClassT *)GRealloc(oldptr, n * sizeof(ClassT));
	if (GNULL == ptr)
	{
		throw std::bad_alloc();
	}
	return ptr;
}

} // namespace gsystem

#endif // _CORE_ALLOCATOR_INLINE_

