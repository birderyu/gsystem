#ifndef _CORE_BLOCK_INLINE_
#define _CORE_BLOCK_INLINE_

template<typename DataT>
inline CsBlock<DataT>::CsBlock(cs_size_t nSize)
: m_nSize(nSize), m_pMemory(NULL), m_bAutoRelease(true)
{
	Initialize();
}

template<typename DataT>
inline CsBlock<DataT>::CsBlock(DataT *pBuf, cs_size_t nSize, cs_bool bAutoRelease)
: m_nSize(nSize), m_pMemory(pBuf), m_bAutoRelease(bAutoRelease)
{
	if (!m_pMemory)
	{
		m_nSize = 0;
	}
	else if (m_nSize == 0)
	{
		if (m_bAutoRelease)
		{
			Free();
		}
	}
}

template<typename DataT>
inline CsBlock<DataT>::CsBlock(const CsBlock<DataT> &tBlock)
: m_nSize(tBlock.m_nSize), m_pMemory(NULL), m_bAutoRelease(true)
{
	if (!tBlock.m_pMemory)
	{
		return;
	}
	if (!Initialize())
	{
		return;
	}
	CsMemCopy(m_pMemory, tBlock.m_pMemory, m_nSize * sizeof(DataT));
}

template<typename DataT>
inline CsBlock<DataT>::~CsBlock()
{
	if (m_bAutoRelease)
	{
		Free();
	}
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::Valid() const
{
	return m_nSize > 0 && m_pMemory;
}

template<typename DataT>
inline cs_size_t CsBlock<DataT>::Size() const
{
	return m_nSize;
}

template<typename DataT>
inline DataT *CsBlock<DataT>::Cursor(cs_size_t nCursor) const
{
	if (!Valid())
	{
		return NULL;
	}
	CS_ASSERT(nCursor < m_nSize);
	return m_pMemory + nCursor;
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::Resize(cs_size_t nSize)
{
	if (m_nSize == nSize)
	{
		// 无需重新分配尺寸
		return true;
	}

	if (nSize <= 0)
	{
		Free();
		return true;
	}

	m_nSize = nSize;
	if (!Valid())
	{
		return Initialize();
	}
	else
	{
		m_pMemory = (DataT *)CsRealloc(m_pMemory, m_nSize * sizeof(DataT));
	}
	return m_pMemory != NULL;
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::Resize(cs_size_t nSize, cs_size_t nStart, cs_size_t nLength)
{
	if (m_nSize == nSize && nStart == 0 && nLength == m_nSize)
	{
		// 无需重新分配尺寸
		return true;
	}

	if (nSize <= 0)
	{
		Free();
		return true;
	}

	DataT *pMemory = (DataT *)CsMalloc(nSize * sizeof(DataT));
	if (!pMemory)
	{
		return false;
	}
	if (m_pMemory && nStart < m_nSize && nLength > 0)
	{
		// 拷贝旧内存到新的地址
		cs_size_t nRealLength(nLength);
		if (nStart + nRealLength > m_nSize)
		{
			nRealLength = m_nSize - nStart;
		}
		CsMemCopy(pMemory, m_pMemory + nStart, nRealLength * sizeof(DataT));
	}
	if (m_pMemory)
	{
		// 释放旧的内存
		Free();
	}
	m_pMemory = pMemory;
	m_nSize = nSize;
	return true;
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::CreateFrom(const CsBlock<DataT> &tFrom)
{
	return CreateFrom(tFrom, 0, tFrom.m_nSize);
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::CreateFrom(const CsBlock<DataT> &tFrom, cs_size_t nFromStart, cs_size_t nFromLength)
{
	if (tFrom.m_nSize == 0)
	{
		Free();
		return true;
	}

	if (m_nSize == nFromLength)
	{
		// 直接拷贝
		if (!m_pMemory)
		{
			m_pMemory = (DataT *)CsMalloc(nFromLength * sizeof(DataT));
		}
	}
	else
	{
		if (m_pMemory)
		{
			Free();
		}
		m_pMemory = (DataT *)CsMalloc(nFromLength * sizeof(DataT));
	}
	if (!m_pMemory)
	{
		return false;
	}
	CsMemCopy(m_pMemory, tFrom.Cursor(nFromStart), nFromLength * sizeof(DataT));
	return true;
}

template<typename DataT>
inline DataT &CsBlock<DataT>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline const DataT &CsBlock<DataT>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline DataT &CsBlock<DataT>::operator[](cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline const DataT &CsBlock<DataT>::operator[](cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline cs_bool CsBlock<DataT>::Initialize()
{
	if (m_nSize <= 0)
	{
		return true;
	}
	m_pMemory = (DataT*)CsMalloc(m_nSize * sizeof(DataT));
	return m_pMemory != NULL;
}

template<typename DataT>
inline cs_void CsBlock<DataT>::Free()
{
	if (m_pMemory)
	{
		CsFree(m_pMemory);
	}
	m_pMemory = NULL;
	m_nSize = 0;
}

#endif // _CORE_BLOCK_INLINE_