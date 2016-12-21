#include "CsNew.h"
#include "dlmalloc.h"

cs_pointer CsMalloc(cs_size_t size)
{
	return dlmalloc(size);
}

cs_pointer CsCalloc(cs_size_t n, cs_size_t size)
{
	return dlcalloc(n, size);
}

cs_pointer CsRealloc(cs_pointer oldptr, cs_size_t newsize)
{
	return dlrealloc(oldptr, newsize);
}

cs_void CsFree(cs_pointer pfree)
{
	dlfree(pfree);
}

cs_pointer CsMemoryCopy(cs_void *dst, const cs_void *src, cs_size_t size)
{
	return memcpy(dst, src, size);
}
