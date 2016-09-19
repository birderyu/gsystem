/// 内存块

#ifndef _CORE_MEMORY_BLOCK_H_
#define _CORE_MEMORY_BLOCK_H_

#include "CsCoreGlobal.h"

class CsMemoryPool;

class CS_CORE_EXPORT CsMemoryBlock
{
	friend class CsMemoryPool;

public:
	CsMemoryBlock(cs_size_t nUnitSize, cs_size_t nUnitAmount);
	~CsMemoryBlock();

	/// 是否可以分配内存
	cs_bool CanAlloc() const;

	static void *operator new(cs_size_t, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (cs_pointer pBlock, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (cs_pointer pBlock);

private:
	cs_int m_nSize;              //该内存块的大小，以字节为单位
	cs_int m_nFree;              //该内存块还有多少可分配的单元
	cs_int m_nFirst;             //当前可用单元的序号，从0开始
	CsMemoryBlock *m_pNext;              //指向下一个内存块
	cs_char aData[1];           //用于标记分配单元开始的位置，分配单元从aData的位置开始
};

#endif // _CORE_MEMORY_BLOCK_H_