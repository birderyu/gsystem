#include "gblock.h"
#include "gallocator.h"

#define G_BLOCK_AUTO_RELEASE m_tConfig[0]
#define G_BLOCK_LOCAL_MEMORY m_tConfig[1]

GBlock::GBlock(gsize nSize)
	: m_nSize(nSize)
{
	Initialize();
}

GBlock::GBlock(gbyte *pBuf, gsize nSize, gbool bAutoRelease)
	: m_nSize(nSize)
{
	G_BLOCK_AUTO_RELEASE = bAutoRelease;
	G_BLOCK_LOCAL_MEMORY = false;
	m_pBlock = pBuf;
	if (GNULL == m_pBlock)
	{
		m_nSize = 0;
	}
	else if (m_nSize == 0)
	{
		if (bAutoRelease)
		{
			Free();
		}
	}
}

GBlock::GBlock(const GBlock &block)
	: m_nSize(block.m_nSize)
{
	G_BLOCK_AUTO_RELEASE = true;
	G_BLOCK_LOCAL_MEMORY = block.G_BLOCK_LOCAL_MEMORY;

	if (true == G_BLOCK_LOCAL_MEMORY)
	{
		GMemCopy(m_tBlock, block.m_tBlock, m_nSize * sizeof(gbyte));
	}
	else
	{
		if (m_nSize == 0)
		{
			m_pBlock = GNULL;
		}
		else
		{
			GMemCopy(m_pBlock, block.m_pBlock, m_nSize * sizeof(gbyte));
		}
	}
}

GBlock::GBlock(GBlock &&block)
	: m_nSize(block.m_nSize)
{
	GMemCopy(m_tConfig, block.m_tConfig, 2);
	GMemCopy(m_pBlock, block.m_pBlock, G_POINTER_ADDRESS_SIZE);

	// 收尾工作
	if (!block.G_BLOCK_LOCAL_MEMORY)
	{
		block.m_pBlock = GNULL;
	}
	block.m_nSize = 0;
}

GBlock::~GBlock()
{
	if (G_BLOCK_AUTO_RELEASE)
	{
		Free();
	}
}

gsize GBlock::Size() const
{
	return m_nSize;
}

gbyte *GBlock::CursorAt(gsize nCursor)
{
	if (!Valid())
	{
		return GNULL;
	}
	GASSERT(nCursor < m_nSize);
	if (true == G_BLOCK_LOCAL_MEMORY)
	{
		return m_tBlock + nCursor;
	}
	return m_pBlock + nCursor;
}

const gbyte *GBlock::CursorAt(gsize nCursor) const
{
	if (!Valid())
	{
		return GNULL;
	}
	GASSERT(nCursor < m_nSize);
	if (true == G_BLOCK_LOCAL_MEMORY)
	{
		return m_tBlock + nCursor;
	}
	return m_pBlock + nCursor;
}

gvoid GBlock::Resize(gsize nSize)
{
	if (m_nSize == nSize)
	{
		// 无需重新分配尺寸
		return;
	}

	if (nSize <= 0)
	{
		Free();
		return;
	}

	if (!Valid())
	{
		m_nSize = nSize;
		Initialize();
		return;
	}
	
	if (nSize <= G_POINTER_ADDRESS_SIZE)
	{
		if (false == G_BLOCK_LOCAL_MEMORY)
		{
			// TODO：需要验证安全性
			GMemMove(m_tBlock, m_pBlock, nSize);
		}
	}
	else
	{
		if (true == G_BLOCK_LOCAL_MEMORY)
		{
			// TODO：需要验证安全性
			GMemMove(m_pBlock, m_tBlock, m_nSize);
		}
		else
		{
			m_pBlock = GReallocate<gbyte>(m_pBlock, nSize);
		}
	}

	m_nSize = nSize;
}

gbyte &GBlock::GetAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	if (true == G_BLOCK_LOCAL_MEMORY)
	{
		return m_tBlock[pos];
	}
	GASSERT(m_pBlock);
	return m_pBlock[pos];
}

const gbyte &GBlock::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	if (true == G_BLOCK_LOCAL_MEMORY)
	{
		return m_tBlock[pos];
	}
	GASSERT(m_pBlock);
	return m_pBlock[pos];
}

gbyte &GBlock::operator[](gsize pos)
{
	return GetAt(pos);
}

const gbyte &GBlock::operator[](gsize pos) const
{
	return GetAt(pos);
}

gbool GBlock::Valid() const
{
	if (m_nSize <= 0)
	{
		return false;
	}
	if (false == G_BLOCK_LOCAL_MEMORY)
	{
		return m_pBlock != GNULL;
	}
	return true;
}

gvoid GBlock::Initialize()
{
	G_BLOCK_AUTO_RELEASE = true;
	if (m_nSize <= G_POINTER_ADDRESS_SIZE)
	{
		G_BLOCK_LOCAL_MEMORY = true;
	}
	else
	{
		// 需要分配内存，使用内存分配器去分配
		m_pBlock = GAllocate<gbyte>(m_nSize);
	}
}

gvoid GBlock::Free()
{
	if (false == G_BLOCK_LOCAL_MEMORY)
	{
		GDeallocate<gbyte>(m_pBlock);
		G_BLOCK_LOCAL_MEMORY = true;
	}
	m_nSize = 0;
}

#undef G_BLOCK_LOCAL_MEMORY
#undef G_BLOCK_AUTO_RELEASE