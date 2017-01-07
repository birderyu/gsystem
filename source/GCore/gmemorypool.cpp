#include "gmemorypool.h"
#include "gnew.h"

#define  G_MEMPOOL_ALIGNMENT 8            //对齐长度

GMemoryPool::GMemoryCell::GMemoryCell(gsize nUnitSize, gsize nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //构造的时候，就已将第一个单元分配出去了，所以减一
, m_nFirst(1)                //同上
, m_pNext(NULL)
{
	//初始化数组链表，将每个分配单元的下一个分配单元的序号写在当前单元的前两个字节中
	gchar* pData = aData;
	//最后一个位置不用写入
	for (gsize i = 1; i < nUnitAmount; i++)
	{
		(*(gushort*)pData) = i;
		pData += nUnitSize;
	}
}

GMemoryPool::GMemoryCell::~GMemoryCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

void* GMemoryPool::GMemoryCell::operator new(gsize nSize, int nUnitSize, int nUnitAmount)
{
	//return ::operator new(nSize + nUnitSize * nUnitAmount);
	return GMalloc(nSize + nUnitSize * nUnitAmount);
}

void GMemoryPool::GMemoryCell::operator delete(void *pCell, gint nUnitSize, gint nUnitAmount)
{
	//::operator delete(pCell);
	GFree(pCell);
}

void GMemoryPool::GMemoryCell::operator delete(void* pCell)
{
	//::operator delete(pCell);
	GFree(pCell);
}

GMemoryPool::GMemoryPool(gsize nUnitSize, gsize nInitSzie, gsize nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(NULL)
{
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (G_MEMPOOL_ALIGNMENT - 1)) & ~(G_MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

GMemoryPool::~GMemoryPool()
{
	if (m_pList)
	{
		delete m_pList;
	}
}

gpointer GMemoryPool::Alloc()
{
	if (!m_pList)
	{
		//首次生成MemoryBlock，new带参数，new了一个MemoryBlock类
		m_pList = new(m_nUnitSize, m_nInitSize) GMemoryCell(m_nUnitSize, m_nInitSize);
		return (gpointer)m_pList->aData;
	}

	//找到符合条件的内存块
	GMemoryCell* pBlock = m_pList;
	while (pBlock && 0 == pBlock->m_nFree)
	{
		pBlock = pBlock->m_pNext;
	}
		
	if (pBlock)
	{
		//找到了，进行分配
		gpointer pFree = pBlock->aData + pBlock->m_nFirst * m_nUnitSize;
		pBlock->m_nFirst = *((gushort*)pFree);
		pBlock->m_nFree--;
		return pFree;
	}
	else
	{
		//没有找到，说明原来的内存块都满了，要再次分配
		if (0 == m_nGrowSize)
			return NULL;

		pBlock = (GMemoryCell*)new(m_nUnitSize, m_nGrowSize) GMemoryCell(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//进行一次插入操作
		pBlock->m_pNext = m_pList;
		m_pList = pBlock;

		return (void*)pBlock->aData;
	}
}

gvoid GMemoryPool::Free(gpointer pFree)
{
	//找到p所在的内存块
	GMemoryCell* pBlock = m_pList;
	GMemoryCell* pPreBlock = NULL;
	while (pBlock != NULL && (m_pList->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
	{
		pPreBlock = pBlock;
		pBlock = pBlock->m_pNext;
	}

	if (NULL != pBlock)      //该内存在本内存池中pMyBlock所指向的内存块中
	{
		//Step1 修改数组链表
		*((gushort*)pFree) = pBlock->m_nFirst;
		pBlock->m_nFirst = (gushort)((gulong)pFree - (gulong)pBlock->aData) / m_nUnitSize;
		pBlock->m_nFree++;

		//Step2 判断是否需要向OS释放内存
		if (pBlock->m_nSize == pBlock->m_nFree * m_nUnitSize)
		{
			if (!pPreBlock)
			{
				// 不删除队首
				m_pList = pBlock;
			}
			else
			{
				//在链表中删除该block
				pPreBlock->m_pNext = pBlock->m_pNext;
				delete pBlock;
				pBlock = NULL;
			}
		}
		else
		{
			//将该block插入到队首
			pPreBlock = pBlock->m_pNext;
			pBlock->m_pNext = m_pList;
			m_pList = pBlock;
		}
	}
}
