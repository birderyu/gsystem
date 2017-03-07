#include "gmemory.h"
#include "dlmalloc.h"

gpointer GMalloc(gsize size)
{
	return dlmalloc(size);
}

gpointer GCalloc(gsize n, gsize size)
{
	return dlcalloc(n, size);
}

gpointer GRealloc(gpointer oldptr, gsize newsize)
{
	return dlrealloc(oldptr, newsize);
}

gvoid GFree(gpointer pfree)
{
	dlfree(pfree);
}

gpointer GMemCopy(gvoid *dst, const gvoid *src, gsize size)
{
	return memcpy(dst, src, size);
}

gpointer GMemMove(gvoid *dst, const gvoid *src, gsize size)
{
	return memmove(dst, src, size);
}

GAPI gpointer GMemSet(gvoid *dst, gbyte value, gsize size)
{
	return memset(dst, (gint)value, size);
}
