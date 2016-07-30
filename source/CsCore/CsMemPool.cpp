#include "CsMemPool.h"
#define  MEMPOOL_ALIGNMENT 8            //对齐长度

CsMemoryBlock::CsMemoryBlock(cs_int nUnitSize, cs_int nUnitAmount)
	:m_nSize(nUnitAmount * nUnitSize),
	m_nFree(nUnitAmount - 1),  //构造的时候，就已将第一个单元分配出去了，所以减一
	m_nFirst(1),                //同上
	m_pNext(NULL)
{
	//初始化数组链表，将每个分配单元的下一个分配单元的序号写在当前单元的前两个字节中
	char* pData = aData;
	//最后一个位置不用写入
	for (int i = 1; i < m_nSize - 1; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryBlock::~CsMemoryBlock()
{

}

void* CsMemoryBlock::operator new(size_t, int nUnitSize, int nUnitAmount)
{
	return ::operator new(sizeof(CsMemoryBlock)+nUnitSize * nUnitAmount);
}

void CsMemoryBlock::operator delete(void *pBlock, cs_int nUnitSize, cs_int nUnitAmount)
{
	::operator delete(pBlock);
}

void CsMemoryBlock::operator delete(void* pBlock)
{
	::operator delete(pBlock);
}

CsMemoryPool::CsMemoryPool(int nUnitSize, int nGrowSize, int nInitSzie)
{
	m_nInitSize = nInitSzie;
	m_nGrowSize = nGrowSize;
	m_pBlock = NULL;
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

CsMemoryPool::~CsMemoryPool()
{
	CsMemoryBlock* pMyBlock = m_pBlock;
	while (pMyBlock != NULL)
	{
		pMyBlock = pMyBlock->m_pNext;
		delete(pMyBlock);
	}
}

void *CsMemoryPool::Alloc()
{
	if (NULL == m_pBlock)
	{
		//首次生成MemoryBlock,new带参数，new了一个MemoryBlock类
		m_pBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nInitSize) CsMemoryBlock(m_nUnitSize, m_nUnitSize);
		return (void*)m_pBlock->aData;
	}

	//找到符合条件的内存块
	CsMemoryBlock* pMyBlock = m_pBlock;
	while (pMyBlock != NULL && 0 == pMyBlock->m_nFree)
		pMyBlock = pMyBlock->m_pNext;

	if (pMyBlock != NULL)
	{
		//找到了，进行分配
		char* pFree = pMyBlock->aData + pMyBlock->m_nFirst * m_nUnitSize;
		pMyBlock->m_nFirst = *((cs_ushort*)pFree);
		pMyBlock->m_nFree--;

		return (void*)pFree;
	}
	else
	{
		//没有找到，说明原来的内存块都满了，要再次分配

		if (0 == m_nGrowSize)
			return NULL;

		pMyBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nGrowSize) CsMemoryBlock(m_nUnitSize, m_nGrowSize);

		if (NULL == pMyBlock)
			return NULL;

		//进行一次插入操作
		pMyBlock->m_pNext = m_pBlock;
		m_pBlock = pMyBlock;

		return (void*)pMyBlock->aData;
	}
}

void CsMemoryPool::Free(void* pFree)
{
	//找到p所在的内存块
	CsMemoryBlock* pMyBlock = m_pBlock;
	CsMemoryBlock* pPreBlock = NULL;
	while (pMyBlock != NULL && (m_pBlock->aData > pFree || pMyBlock->aData + pMyBlock->m_nSize))
	{
		pPreBlock = pMyBlock;
		pMyBlock = pMyBlock->m_pNext;
	}

	if (NULL != pMyBlock)      //该内存在本内存池中pMyBlock所指向的内存块中
	{
		//Step1 修改数组链表
		*((cs_ushort*)pFree) = pMyBlock->m_nFirst;
		pMyBlock->m_nFirst = (cs_ushort)((cs_ulong)pFree - (cs_ulong)pMyBlock->aData) / m_nUnitSize;
		pMyBlock->m_nFree++;

		//Step2 判断是否需要向OS释放内存
		if (pMyBlock->m_nSize == pMyBlock->m_nFree * m_nUnitSize)
		{
			//在链表中删除该block

			delete(pMyBlock);
		}
		else
		{
			//将该block插入到队首
			pPreBlock = pMyBlock->m_pNext;
			pMyBlock->m_pNext = m_pBlock;
			m_pBlock = pMyBlock;
		}
	}
}
