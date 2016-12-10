#include "CsMemoryStore.h"

CsMemoryStore::CsMemCell::CsMemCell(cs_size_t nSize)
: m_tBlock(nSize), m_nCursor(0), m_pNext(NULL)
{

}

CsMemoryStore::CsMemCell::~CsMemCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

CsMemoryStore::CsMemoryStore(cs_size_t nInitSzie, cs_size_t nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(NULL)
{

}

CsMemoryStore::~CsMemoryStore()
{
	if (m_pList)
	{
		delete m_pList;
	}
}

cs_pointer CsMemoryStore::Alloc(cs_size_t nSize)
{
	CsMemCell* pBlock = NULL;
	if (!m_pList)
	{
		// 初始化
		cs_size_t nRealInitSize = m_nInitSize;
		while (nRealInitSize < nSize)
		{
			nRealInitSize += m_nGrowSize;
		}
		m_pList = new CsMemCell(nRealInitSize);
		pBlock = m_pList;
	}
	else
	{
		pBlock = m_pList;
		while (pBlock && pBlock->m_tBlock.Size() - pBlock->m_nCursor <= nSize)
		{
			pBlock = pBlock->m_pNext;
		}

		if (!pBlock)
		{
			// 增长
			cs_size_t nRealGrowSize = m_nGrowSize;
			while (nRealGrowSize < nSize)
			{
				nRealGrowSize += m_nGrowSize;
			}
			pBlock = new CsMemCell(nRealGrowSize);

			pBlock->m_pNext = m_pList;
			m_pList = pBlock;
		}
	}

	cs_pointer pPtr = pBlock->m_tBlock.Cursor(pBlock->m_nCursor);
	if (pPtr)
	{
		pBlock->m_nCursor += nSize;
	}
	return pPtr;
}