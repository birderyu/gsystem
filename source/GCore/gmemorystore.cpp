#include "gmemorystore.h"

GMemoryStore::GMemCell::GMemCell(gsize nSize)
: m_tBlock(nSize), m_nCursor(0), m_pNext(GNULL)
{

}

GMemoryStore::GMemCell::~GMemCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

GMemoryStore::GMemoryStore(gsize nInitSzie, gsize nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(GNULL)
{

}

GMemoryStore::~GMemoryStore()
{
	if (m_pList)
	{
		delete m_pList;
	}
}

gpointer GMemoryStore::Alloc(gsize nSize)
{
	GMemCell* pBlock = GNULL;
	if (!m_pList)
	{
		// 初始化
		gsize nRealInitSize = m_nInitSize;
		while (nRealInitSize < nSize)
		{
			nRealInitSize += m_nGrowSize;
		}
		m_pList = new GMemCell(nRealInitSize);
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
			gsize nRealGrowSize = m_nGrowSize;
			while (nRealGrowSize < nSize)
			{
				nRealGrowSize += m_nGrowSize;
			}
			pBlock = new GMemCell(nRealGrowSize);

			pBlock->m_pNext = m_pList;
			m_pList = pBlock;
		}
	}

	gpointer pPtr = pBlock->m_tBlock.CursorAt(pBlock->m_nCursor);
	if (pPtr)
	{
		pBlock->m_nCursor += nSize;
	}
	return pPtr;
}