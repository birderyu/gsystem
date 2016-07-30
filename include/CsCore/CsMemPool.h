#ifndef _CSCORE_CSMEMORYPOOL_H_
#define _CSCORE_CSMEMORYPOOL_H_

#include "CsCoreGlobal.h"

class CsMemoryPool;
class CsCore_Export CsMemoryBlock
{
	friend class CsMemoryPool;
public:
	CsMemoryBlock(cs_int nUnitSize, cs_int nUnitAmount);
	~CsMemoryBlock();
	static void *operator new(cs_size_t, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (void *pBlock, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (void *pBlock);

private:
	cs_int m_nSize;              //该内存块的大小，以字节为单位
	cs_int m_nFree;              //该内存块还有多少可分配的单元
	cs_int m_nFirst;             //当前可用单元的序号，从0开始
	CsMemoryBlock *m_pNext;              //指向下一个内存块
	cs_char aData[1];           //用于标记分配单元开始的位置，分配单元从aData的位置开始
};

class CsCore_Export CsMemoryPool
{
public:
	CsMemoryPool(cs_int nUnitSize,
		cs_int nGrowSize = 1024,
		cs_int nInitSzie = 256);
	~CsMemoryPool();
	void *Alloc();
	void Free(void *pFree);

private:
	cs_int m_nInitSize;          //初始大小
	cs_int m_nGrowSize;          //增长大小
	cs_int m_nUnitSize;          //分配单元大小
	CsMemoryBlock *m_pBlock;     //内存块链表
};

#endif // _CSCORE_CSMEMORYPOOL_H_
