#include "CsMemPool.h"
#include "CsString_Private.h"

cs_void TestMemPool()
{
	CsMemoryPool pool(sizeof(CsString_Private), 1024, 50);
	cs_pointer p = pool.Alloc();

	int stop = 1;
	stop++;
}