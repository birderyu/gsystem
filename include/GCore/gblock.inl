#ifndef _CORE_BLOCK_INLINE_
#define _CORE_BLOCK_INLINE_

template<typename DataT>
inline GBlock<DataT>::GBlock(gsize nSize)
: m_nSize(nSize), m_pMemory(NULL), m_bAutoRelease(true)
{
	Initialize();
}

template<typename DataT>
inline GBlock<DataT>::GBlock(DataT *pBuf, gsize nSize, gbool bAutoRelease)
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
inline GBlock<DataT>::GBlock(const GBlock<DataT> &tBlock)
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
	GMemCopy(m_pMemory, tBlock.m_pMemory, m_nSize * sizeof(DataT));
}

template<typename DataT>
inline GBlock<DataT>::~GBlock()
{
	if (m_bAutoRelease)
	{
		Free();
	}
}

template<typename DataT>
inline gbool GBlock<DataT>::Valid() const
{
	return m_nSize > 0 && m_pMemory;
}

template<typename DataT>
inline gsize GBlock<DataT>::Size() const
{
	return m_nSize;
}

template<typename DataT>
inline DataT *GBlock<DataT>::Cursor(gsize nCursor) const
{
	if (!Valid())
	{
		return NULL;
	}
	GASSERT(nCursor < m_nSize);
	return m_pMemory + nCursor;
}

template<typename DataT>
inline gbool GBlock<DataT>::Resize(gsize nSize)
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
		m_pMemory = (DataT *)GRealloc(m_pMemory, m_nSize * sizeof(DataT));
	}
	return m_pMemory != NULL;
}

template<typename DataT>
inline gbool GBlock<DataT>::Resize(gsize nSize, gsize nStart, gsize nLength)
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

	DataT *pMemory = (DataT *)GMalloc(nSize * sizeof(DataT));
	if (!pMemory)
	{
		return false;
	}
	if (m_pMemory && nStart < m_nSize && nLength > 0)
	{
		// 拷贝旧内存到新的地址
		gsize nRealLength(nLength);
		if (nStart + nRealLength > m_nSize)
		{
			nRealLength = m_nSize - nStart;
		}
		GMemCopy(pMemory, m_pMemory + nStart, nRealLength * sizeof(DataT));
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
inline gbool GBlock<DataT>::CreateFrom(const GBlock<DataT> &tFrom)
{
	return CreateFrom(tFrom, 0, tFrom.m_nSize);
}

template<typename DataT>
inline gbool GBlock<DataT>::CreateFrom(const GBlock<DataT> &tFrom, gsize nFromStart, gsize nFromLength)
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
			m_pMemory = (DataT *)GMalloc(nFromLength * sizeof(DataT));
		}
	}
	else
	{
		if (m_pMemory)
		{
			Free();
		}
		m_pMemory = (DataT *)GMalloc(nFromLength * sizeof(DataT));
	}
	if (!m_pMemory)
	{
		return false;
	}
	GMemCopy(m_pMemory, tFrom.Cursor(nFromStart), nFromLength * sizeof(DataT));
	return true;
}

template<typename DataT>
inline DataT &GBlock<DataT>::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline const DataT &GBlock<DataT>::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline DataT &GBlock<DataT>::operator[](gsize pos)
{
	GASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline const DataT &GBlock<DataT>::operator[](gsize pos) const
{
	GASSERT(pos < m_nSize);
	return *(m_pMemory + pos);
}

template<typename DataT>
inline gbool GBlock<DataT>::Initialize()
{
	if (m_nSize <= 0)
	{
		return true;
	}
	m_pMemory = (DataT*)GMalloc(m_nSize * sizeof(DataT));
	return m_pMemory != NULL;
}

template<typename DataT>
inline gvoid GBlock<DataT>::Free()
{
	if (m_pMemory)
	{
		GFree(m_pMemory);
	}
	m_pMemory = NULL;
	m_nSize = 0;
}

#endif // _CORE_BLOCK_INLINE_