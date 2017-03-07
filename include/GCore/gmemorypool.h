/// 定长的内存池
/// 分配出定长的内存
/// 可以对分配出去的内存进行回收
/// 线程不安全

#ifndef _CORE_MEMORY_POOL_H_
#define _CORE_MEMORY_POOL_H_

#include "gglobal.h"
#include "gmemory.h"

#define G_MEMORYPOOL_ALIGNMENT 8            // 对齐长度

template<gsize UNIT_SIZE,
	guint16 INIT_SIZE = 512,
	guint16 GROW_SIZE = 1024>
class GAPI GMemoryPool
{
	static_assert(INIT_SIZE > 0, "memory pool initial size must greater than zero.");
	static_assert(GROW_SIZE > 0, "memory pool grow size must greater than zero.");

	// 内存池单元
	struct GMemoryCell
	{
		// 该内存块的大小，以字节为单位
		gsize m_nSize;

		// 该内存块还有多少可分配的单元
		guint16 m_nFree;

		// 当前可用单元的序号，从0开始
		guint16 m_nFirst;

		// 指向下一个内存块
		GMemoryCell *m_pNext;

		//用于标记分配单元开始的位置，分配单元从m_bData的位置开始
		gbyte m_bData[1];

		GMemoryCell(gsize unit_size, guint16 unit_amount)
			: m_nSize(unit_amount * unit_size)
			, m_nFree(unit_amount - 1)   // 构造的时候，就已将第一个单元分配出去了，所以减一
			, m_nFirst(1)                // 同上
			, m_pNext(GNULL)
		{
			// 初始化数组链表，将每个分配单元的下一个分配单元的序号写在当前单元的前两个字节中
			gbyte *ptr = m_bData;
			//最后一个位置不用写入
			for (gsize i = 1; i < unit_amount; i++)
			{
				(*(guint16*)ptr) = i;
				ptr += unit_size;
			}
		}

		~GMemoryCell()
		{
			if (m_pNext)
			{
				delete m_pNext;
			}
		}

		static gpointer operator new(gsize size, gsize unit_size, guint16 unit_amount)
		{
			return GMalloc(size + unit_size * unit_amount);
		}

		static gvoid operator delete (gpointer cell, gsize unit_size, guint16 unit_amount)
		{
			GFree(cell);
		}
		
		static gvoid operator delete (gpointer cell)
		{
			GFree(cell);
		}
	};

public:
	GMemoryPool()
		: m_pList(GNULL)
	{

	}
	~GMemoryPool()
	{
		if (m_pList)
		{
			delete m_pList;
		}
	}

	// 分配内存，分配失败则返回GNULL
	gpointer Alloc()
	{
		if (!m_pList)
		{
			m_pList = new(m_nUnitSize, INIT_SIZE) GMemoryCell(m_nUnitSize, INIT_SIZE);
			return (gpointer)m_pList->m_bData;
		}

		// 找到符合条件的内存块
		GMemoryCell* block = m_pList;
		while (block && 0 == block->m_nFree)
		{
			block = block->m_pNext;
		}

		if (block)
		{
			// 找到了，进行分配
			gpointer ptr = block->m_bData + block->m_nFirst * m_nUnitSize;
			block->m_nFirst = *((gushort*)ptr);
			block->m_nFree--;
			return ptr;
		}
		else
		{
			// 没有找到，说明原来的内存块都满了，要再次分配
			block = new(m_nUnitSize, GROW_SIZE) GMemoryCell(m_nUnitSize, GROW_SIZE);

			// 进行一次插入操作
			block->m_pNext = m_pList;
			m_pList = block;

			return (gpointer)block->m_bData;
		}
	}

	// 释放内存
	gvoid Free(gpointer free)
	{
		if (GNULL == free)
		{
			return;
		}
		//找到p所在的内存块
		GMemoryCell* block = m_pList;
		GMemoryCell* pre_block = GNULL;
		while (block != GNULL && (m_pList->m_bData > free || block->m_bData + block->m_nSize < free))
		{
			pre_block = block;
			block = block->m_pNext;
		}

		if (GNULL != block)      //该内存在本内存池中pMyBlock所指向的内存块中
		{
			//Step1 修改数组链表
			*((guint16*)free) = block->m_nFirst;
			block->m_nFirst = (guint16)((gaddress)free - (gaddress)block->m_bData) / m_nUnitSize;
			block->m_nFree++;

			//Step2 判断是否需要向OS释放内存
			if (block->m_nSize == block->m_nFree * m_nUnitSize)
			{
				if (!pre_block)
				{
					// 不删除队首
					m_pList = block;
				}
				else
				{
					//在链表中删除该block
					pre_block->m_pNext = block->m_pNext;
					delete block;
					block = GNULL;
				}
			}
			else
			{
				//将该block插入到队首
				pre_block = block->m_pNext;
				block->m_pNext = m_pList;
				m_pList = block;
			}
		}
	}

private:
	const static gsize m_nUnitSize;
	GMemoryCell *m_pList;	// 内存块链表
};

#include "gmemorypool.inl"

#endif // _CORE_MEMORY_POOL_H_