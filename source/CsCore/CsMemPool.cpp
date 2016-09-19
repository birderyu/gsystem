#include "CsMemPool.h"
#include "CsMemBlock.h"

#define  CS_MEMPOOL_ALIGNMENT 8            //对齐长度

CsMemoryPool::CsMemoryPool(cs_size_t nUnitSize, cs_size_t nGrowSize, cs_size_t nInitSzie)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pBlock(NULL)
{
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (CS_MEMPOOL_ALIGNMENT - 1)) & ~(CS_MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

CsMemoryPool::~CsMemoryPool()
{
	CsMemoryBlock* pBlock = static_cast<CsMemoryBlock*>(m_pBlock);
	while (pBlock)
	{
		pBlock = pBlock->m_pNext;
		delete(pBlock);
	}
}

cs_pointer CsMemoryPool::Alloc()
{
	if (!m_pBlock)
	{
		//首次生成MemoryBlock，new带参数，new了一个MemoryBlock类
		m_pBlock = new(m_nUnitSize, m_nInitSize) CsMemoryBlock(m_nUnitSize, m_nInitSize);
		return (void*)m_pBlock->aData;
	}

	//找到符合条件的内存块
	CsMemoryBlock* pBlock = static_cast<CsMemoryBlock*>(m_pBlock);
	while (pBlock && 0 == pBlock->m_nFree)
	{
		pBlock = pBlock->m_pNext;
	}
		
	if (pBlock)
	{
		//找到了，进行分配
		cs_pointer pFree = pBlock->aData + pBlock->m_nFirst * m_nUnitSize;
		pBlock->m_nFirst = *((cs_ushort*)pFree);
		pBlock->m_nFree--;
		return pFree;
	}
	else
	{
		//没有找到，说明原来的内存块都满了，要再次分配
		if (0 == m_nGrowSize)
			return NULL;

		pBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nGrowSize) CsMemoryBlock(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//进行一次插入操作
		pBlock->m_pNext = m_pBlock;
		m_pBlock = pBlock;

		return (void*)pBlock->aData;
	}
}

cs_void CsMemoryPool::Free(cs_pointer pFree)
{
	//找到p所在的内存块
	CsMemoryBlock* pBlock = m_pBlock;
	CsMemoryBlock* pPreBlock = NULL;
	while (pBlock != NULL && (m_pBlock->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
	{
		pPreBlock = pBlock;
		pBlock = pBlock->m_pNext;
	}

	if (NULL != pBlock)      //该内存在本内存池中pMyBlock所指向的内存块中
	{
		//Step1 修改数组链表
		*((cs_ushort*)pFree) = pBlock->m_nFirst;
		pBlock->m_nFirst = (cs_ushort)((cs_ulong)pFree - (cs_ulong)pBlock->aData) / m_nUnitSize;
		pBlock->m_nFree++;

		//Step2 判断是否需要向OS释放内存
		if (pBlock->m_nSize == pBlock->m_nFree * m_nUnitSize)
		{
			if (!pPreBlock)
			{
				// 不删除队首
				m_pBlock = pBlock;
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
			pBlock->m_pNext = m_pBlock;
			m_pBlock = pBlock;
		}
	}
}
