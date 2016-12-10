#include "CsBlock.h"
#include "CsNew.h"
#include <string>

CsBlock::CsBlock(cs_size_t nSize)
: m_nMemSize(nSize), m_pMemory(NULL), m_bAutoRelease(true)
{
	Initialize();
}

CsBlock::CsBlock(cs_pointer pBuf, cs_size_t nSize, cs_bool bAutoRelease)
: m_nMemSize(nSize), m_pMemory(pBuf), m_bAutoRelease(bAutoRelease)
{
	if (!m_pMemory)
	{
		m_nMemSize = 0;
	}
	else if (m_nMemSize == 0)
	{
		if (m_bAutoRelease)
		{
			Free();
		}
	}
}

CsBlock::CsBlock(const CsBlock &tBlock)
: m_nMemSize(tBlock.m_nMemSize), m_pMemory(NULL), m_bAutoRelease(true)
{
	if (!tBlock.m_pMemory)
	{
		return;
	}
	if (!Initialize())
	{
		return;
	}
	memcpy(m_pMemory, tBlock.m_pMemory, m_nMemSize);
}

CsBlock::~CsBlock()
{
	if (m_bAutoRelease)
	{
		Free();
	}
}

cs_bool CsBlock::Valid() const
{
	return m_nMemSize > 0 && m_pMemory;
}

cs_size_t CsBlock::Size() const
{
	return m_nMemSize;
}

cs_pointer CsBlock::Cursor(cs_size_t nCursor) const
{
	if (!Valid() || nCursor >= m_nMemSize)
	{
		return NULL;
	}
	return (cs_byte*)m_pMemory + nCursor;
}

cs_bool CsBlock::Resize(cs_size_t nSize)
{
	if (m_nMemSize == nSize)
	{
		// 无需重新分配尺寸
		return true;
	}

	if (nSize <= 0)
	{
		Free();
		return true;
	}

	m_nMemSize = nSize;
	if (!Valid())
	{
		return Initialize();
	}
	else
	{
		m_pMemory = CsRealloc(m_pMemory, m_nMemSize);
	}
	return m_pMemory != NULL;
}

cs_bool CsBlock::Resize(cs_size_t nSize, cs_size_t nStart, cs_size_t nLength)
{
	if (m_nMemSize == nSize && nStart == 0 && nLength == m_nMemSize)
	{
		// 无需重新分配尺寸
		return true;
	}

	if (nSize <= 0)
	{
		Free();
		return true;
	}

	cs_pointer pMemory = CsMalloc(nSize);
	if (!pMemory)
	{
		return false;
	}
	if (m_pMemory && nStart < m_nMemSize && nLength > 0)
	{
		// 拷贝旧内存到新的地址
		cs_size_t nRealLength(nLength);
		if (nStart + nRealLength > m_nMemSize)
		{
			nRealLength = m_nMemSize - nStart;
		}
		memcpy(pMemory, (cs_byte*)m_pMemory + nStart, nRealLength);
	}
	if (m_pMemory)
	{
		// 释放旧的内存
		Free();
	}
	m_pMemory = pMemory;
	m_nMemSize = nSize;
	return true;
}

cs_bool CsBlock::CreateFrom(const CsBlock &tFrom)
{
	return CreateFrom(tFrom, 0, tFrom.m_nMemSize);
}

cs_bool CsBlock::CreateFrom(const CsBlock &tFrom, cs_size_t nFromStart, cs_size_t nFromLength)
{
	if (tFrom.m_nMemSize == 0)
	{
		Free();
		return true;
	}

	if (m_nMemSize == nFromLength)
	{
		// 直接拷贝
		if (!m_pMemory)
		{
			m_pMemory = CsMalloc(nFromLength);
		}
	}
	else
	{
		if (m_pMemory)
		{
			Free();
		}
		m_pMemory = CsMalloc(nFromLength);
	}
	if (!m_pMemory)
	{
		return false;
	}
	memcpy(m_pMemory, tFrom.Cursor(nFromStart), nFromLength);
	return true;
}

cs_bool CsBlock::Initialize()
{
	if (m_nMemSize <= 0)
	{
		return true;
	}
	m_pMemory = CsMalloc(m_nMemSize);
	return m_pMemory != NULL;
}

cs_void CsBlock::Free()
{
	if (m_pMemory)
	{
		CsFree(m_pMemory);
	}
	m_pMemory = NULL;
	m_nMemSize = 0;
}

