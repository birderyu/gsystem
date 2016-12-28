#include "CsStringPool.h"

CsStringPool::CsStringPool(cs_size_t nInitSzie, cs_size_t nMaxSize)
:m_tStore(nInitSzie, nInitSzie)
{

}

cs_pointer CsStringPool::Alloc(cs_size_t size)
{
	CsMap<cs_size_t, CsVector<cs_ptr_addr>>::ConstIterator citer = m_tRecycle.ConstFind(size);
	if (citer != m_tRecycle.ConstEnd())
	{
		// 从内存回收站中获取一块内存（TODO）
	}
	return m_tStore.Alloc(size);
}

cs_void CsStringPool::Free(cs_pointer)
{

}