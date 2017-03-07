/// 非定长的内存池
/// 分配出非定长的内存
/// 分配出去的内存不回收
/// 线程不安全

#ifndef _CORE_MEMORY_STORE_H_
#define _CORE_MEMORY_STORE_H_

#include "gglobal.h"
#include "gblock.h"

class GAPI GMemoryStore
{
	// 内存池单元
	struct GMemCell
	{
		//内存块
		GBlock m_tBlock;

		//光标
		gsize m_nCursor;

		//指向下一个内存块
		GMemCell *m_pNext;

		GMemCell(gsize nSize);
		~GMemCell();
	};

public:
	GMemoryStore(gsize nInitSzie = 2048, gsize nGrowSize = 1024);
	~GMemoryStore();

	// 分配内存，分配失败则返回NULL
	gpointer Alloc(gsize);

private:
	gsize m_nInitSize;		// 初始大小
	gsize m_nGrowSize;		// 增长大小
	GMemCell *m_pList;		// 内存块链表
};

#endif // _CORE_MEMORY_STORE_H_