#include "CsStringPool.h"

CsStringPool::CsStringPool(cs_size_t nInitSzie, cs_size_t nMaxSize)
:m_tStore(nInitSzie, nInitSzie)
{

}

cs_pointer CsStringPool::Alloc(cs_size_t size)
{
	std::map<cs_size_t, std::vector<cs_ptr_addr>>::const_iterator citer = m_tRecycle.find(size);
	if (citer != m_tRecycle.cend())
	{
		// 从内存回收站中获取一块内存（TODO）
	}
	return m_tStore.Alloc(size);
}

cs_void CsStringPool::Free(cs_pointer)
{

}