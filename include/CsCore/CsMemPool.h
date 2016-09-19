/// 内存池

#ifndef _CORE_MEMORY_POOL_H_
#define _CORE_MEMORY_POOL_H_

#include "CsCoreGlobal.h"

class CsMemoryBlock;

class CS_CORE_EXPORT CsMemoryPool
{
public:
	CsMemoryPool(cs_size_t nUnitSize,
		cs_size_t nGrowSize = 1024,
		cs_size_t nInitSzie = 256);
	~CsMemoryPool();

	/// 根据内存分配单元分配一块内存
	cs_pointer Alloc();
	cs_void Free(cs_pointer pFree);

private:
	cs_size_t m_nInitSize;		// 初始大小
	cs_size_t m_nGrowSize;		// 增长大小
	cs_size_t m_nUnitSize;		// 分配单元大小
	CsMemoryBlock *m_pBlock;	// 内存块链表
};

#endif // _CORE_MEMORY_POOL_H_