#pragma once

#include "gmemorypool.h"

gvoid MemoryPool_Test()
{
	const gsize unit_size = 8;
	const gsize init_szie = 2;
	const gsize grow_size = 1;
	GMemoryPool<unit_size, init_szie, grow_size> pool;
	gpointer ptr = pool.Alloc();
	gpointer ptr2 = pool.Alloc();
	pool.Free(ptr);
	pool.Free(ptr2);
}