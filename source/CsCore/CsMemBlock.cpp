#include "CsMemBlock.h"

CsMemoryBlock::CsMemoryBlock(cs_size_t nUnitSize, cs_size_t nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //构造的时候，就已将第一个单元分配出去了，所以减一
, m_nFirst(1)                //同上
, m_pNext(NULL)
{
	//初始化数组链表，将每个分配单元的下一个分配单元的序号写在当前单元的前两个字节中
	char* pData = aData;
	//最后一个位置不用写入
	for (int i = 1; i < nUnitAmount; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryBlock::~CsMemoryBlock()
{

}

cs_bool CsMemoryBlock::CanAlloc() const
{
	return m_nFree != 0;
}

void* CsMemoryBlock::operator new(size_t nSize, int nUnitSize, int nUnitAmount)
{
	return ::operator new(nSize + nUnitSize * nUnitAmount);
}

void CsMemoryBlock::operator delete(void *pBlock, cs_int nUnitSize, cs_int nUnitAmount)
{
	::operator delete(pBlock);
}

void CsMemoryBlock::operator delete(void* pBlock)
{
	::operator delete(pBlock);
}