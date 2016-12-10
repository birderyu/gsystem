/// 定长的内存池
/// 分配出定长的内存
/// 可以对分配出去的内存进行回收
/// 线程不安全

#ifndef _CORE_MEMORY_POOL_H_
#define _CORE_MEMORY_POOL_H_

#include "CsGlobal.h"

class CS_API CsMemoryPool
{
	// 内存池单元
	struct CsMemoryCell
	{
		//该内存块的大小，以字节为单位
		cs_int m_nSize;

		//该内存块还有多少可分配的单元
		cs_int m_nFree;

		//当前可用单元的序号，从0开始
		cs_int m_nFirst;

		//指向下一个内存块
		CsMemoryCell *m_pNext;

		//用于标记分配单元开始的位置，分配单元从aData的位置开始
		cs_char aData[1];

		CsMemoryCell(cs_size_t nUnitSize, cs_size_t nUnitAmount);
		~CsMemoryCell();

		static void *operator new(cs_size_t, cs_int nUnitSize, cs_int nUnitAmount);
		static void operator delete (cs_pointer pCell, cs_int nUnitSize, cs_int nUnitAmount);
		static void operator delete (cs_pointer pCell);
	};

public:
	CsMemoryPool(cs_size_t nUnitSize,
		cs_size_t nInitSzie = 512,
		cs_size_t nGrowSize = 1024);
	~CsMemoryPool();

	// 分配内存，分配失败则返回NULL
	cs_pointer Alloc();

	// 释放内存
	cs_void Free(cs_pointer pFree);

private:
	cs_size_t m_nInitSize;		// 初始大小
	cs_size_t m_nGrowSize;		// 增长大小
	cs_size_t m_nUnitSize;		// 分配单元大小
	CsMemoryCell *m_pList;	// 内存块链表
};

#endif // _CORE_MEMORY_POOL_H_