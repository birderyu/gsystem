/// 非定长的内存池
/// 分配出非定长的内存
/// 分配出去的内存不回收
/// 线程不安全

#ifndef _CORE_MEMORY_STORE_H_
#define _CORE_MEMORY_STORE_H_

#include "CsGlobal.h"
#include "CsBlock.h"

class CS_API CsMemoryStore
{
	// 内存池单元
	struct CsMemCell
	{
		//内存块
		CsBlock<cs_byte> m_tBlock;

		//光标
		cs_size_t m_nCursor;

		//指向下一个内存块
		CsMemCell *m_pNext;

		CsMemCell(cs_size_t nSize);
		~CsMemCell();
	};

public:
	CsMemoryStore(cs_size_t nInitSzie = 2048, cs_size_t nGrowSize = 1024);
	~CsMemoryStore();

	// 分配内存，分配失败则返回NULL
	cs_pointer Alloc(cs_size_t);

private:
	cs_size_t m_nInitSize;		// 初始大小
	cs_size_t m_nGrowSize;		// 增长大小
	CsMemCell *m_pList;		// 内存块链表
};

#endif // _CORE_MEMORY_STORE_H_