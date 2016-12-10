#include "CsMemoryPool.h"
#include "CsNew.h"

#define  CS_MEMPOOL_ALIGNMENT 8            //对齐长度

CsMemoryPool::CsMemoryCell::CsMemoryCell(cs_size_t nUnitSize, cs_size_t nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //构造的时候，就已将第一个单元分配出去了，所以减一
, m_nFirst(1)                //同上
, m_pNext(NULL)
{
	//初始化数组链表，将每个分配单元的下一个分配单元的序号写在当前单元的前两个字节中
	cs_char* pData = aData;
	//最后一个位置不用写入
	for (cs_size_t i = 1; i < nUnitAmount; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryPool::CsMemoryCell::~CsMemoryCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

void* CsMemoryPool::CsMemoryCell::operator new(cs_size_t nSize, int nUnitSize, int nUnitAmount)
{
	//return ::operator new(nSize + nUnitSize * nUnitAmount);
	return CsMalloc(nSize + nUnitSize * nUnitAmount);
}

void CsMemoryPool::CsMemoryCell::operator delete(void *pCell, cs_int nUnitSize, cs_int nUnitAmount)
{
	//::operator delete(pCell);
	CsFree(pCell);
}

void CsMemoryPool::CsMemoryCell::operator delete(void* pCell)
{
	//::operator delete(pCell);
	CsFree(pCell);
}

CsMemoryPool::CsMemoryPool(cs_size_t nUnitSize, cs_size_t nInitSzie, cs_size_t nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(NULL)
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
	if (m_pList)
	{
		delete m_pList;
	}
}

cs_pointer CsMemoryPool::Alloc()
{
	if (!m_pList)
	{
		//首次生成MemoryBlock，new带参数，new了一个MemoryBlock类
		m_pList = new(m_nUnitSize, m_nInitSize) CsMemoryCell(m_nUnitSize, m_nInitSize);
		return (cs_pointer)m_pList->aData;
	}

	//找到符合条件的内存块
	CsMemoryCell* pBlock = m_pList;
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

		pBlock = (CsMemoryCell*)new(m_nUnitSize, m_nGrowSize) CsMemoryCell(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//进行一次插入操作
		pBlock->m_pNext = m_pList;
		m_pList = pBlock;

		return (void*)pBlock->aData;
	}
}

cs_void CsMemoryPool::Free(cs_pointer pFree)
{
	//找到p所在的内存块
	CsMemoryCell* pBlock = m_pList;
	CsMemoryCell* pPreBlock = NULL;
	while (pBlock != NULL && (m_pList->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
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
