/// 定长的内存池
/// 分配出定长的内存
/// 可以对分配出去的内存进行回收
/// 线程不安全

#ifndef _CORE_MEMORY_POOL_H_
#define _CORE_MEMORY_POOL_H_

#include "gglobal.h"

class GAPI GMemoryPool
{
	// 内存池单元
	struct GMemoryCell
	{
		//该内存块的大小，以字节为单位
		gint m_nSize;

		//该内存块还有多少可分配的单元
		gint m_nFree;

		//当前可用单元的序号，从0开始
		gint m_nFirst;

		//指向下一个内存块
		GMemoryCell *m_pNext;

		//用于标记分配单元开始的位置，分配单元从aData的位置开始
		gchar aData[1];

		GMemoryCell(gsize nUnitSize, gsize nUnitAmount);
		~GMemoryCell();

		static void *operator new(gsize, gint nUnitSize, gint nUnitAmount);
		static void operator delete (gpointer pCell, gint nUnitSize, gint nUnitAmount);
		static void operator delete (gpointer pCell);
	};

public:
	GMemoryPool(gsize nUnitSize,
		gsize nInitSzie = 512,
		gsize nGrowSize = 1024);
	~GMemoryPool();

	// 分配内存，分配失败则返回NULL
	gpointer Alloc();

	// 释放内存
	gvoid Free(gpointer pFree);

private:
	gsize m_nInitSize;		// 初始大小
	gsize m_nGrowSize;		// 增长大小
	gsize m_nUnitSize;		// 分配单元大小
	GMemoryCell *m_pList;	// 内存块链表
};

#endif // _CORE_MEMORY_POOL_H_