#include "CsBytes_Ex.h"
#include "CsBytes.h"

#define CS_DEFAULT_ADD_SIZE 256

CsBytes_Ex::CsBytes_Ex(cs_size_t nCapacity)
: m_tBlock(0), m_nHeadCursor(-1), m_nTailCursor(-1)
{
	if (nCapacity > 0)
	{
		Reserve(nCapacity);
	}
}

CsBytes_Ex::CsBytes_Ex(const CsBytes_Ex &tBytes)
: m_tBlock(0), m_nHeadCursor(-1), m_nTailCursor(-1)
{
	cs_size_t len = tBytes.Length();
	if (len <= 0)
	{
		return;
	}
	m_tBlock.CreateFrom(tBytes.m_tBlock, tBytes.m_nHeadCursor, len);
	m_nTailCursor = len;
}

CsBytes_Ex::~CsBytes_Ex()
{
	Clear();
}

cs_bool CsBytes_Ex::IsEmpty() const
{
	return !m_tBlock.Valid() || Length() == 0;
}

cs_byte *CsBytes_Ex::GetHead() const
{
	if (!Valid())
	{
		return NULL;
	}
	return (cs_byte *)m_tBlock.Cursor(m_nHeadCursor);
}

cs_size_t CsBytes_Ex::Length() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTailCursor - m_nHeadCursor;
}

cs_size_t CsBytes_Ex::Capacity() const
{
	cs_size_t nMemSize = m_tBlock.Size();
	if (m_nHeadCursor < 0 || nMemSize <= m_nHeadCursor)
	{
		return 0;
	}
	return nMemSize - m_nHeadCursor;
}

cs_bool CsBytes_Ex::ReadFrom(const cs_byte *pBuf, cs_size_t len)
{
	if (len <= 0)
	{
		return false;
	}

	cs_size_t nNewLen = Length() + len;
	if (nNewLen > Capacity())
	{
		if (!Reserve(nNewLen))
		{
			return false;
		}
	}
	memcpy(GetTail(), pBuf, len);
	m_nTailCursor += len;
	return true;
}

cs_bool CsBytes_Ex::ReadFrom(cs_cstring str)
{
	cs_size_t len = strlen(str);
	if (len <= 0)
	{
		return false;
	}
	else
	{
		len++;
	}
	cs_size_t nNewLen = Length() + len;
	if (nNewLen > Capacity())
	{
		if (!Reserve(nNewLen))
		{
			return false;
		}
	}
	memcpy(GetTail(), str, len);
	m_nTailCursor += len;
	return true;
}

cs_bool CsBytes_Ex::WriteTo(cs_size_t len, cs_byte *&pBuf)
{
	if (len <= 0)
	{
		return false;
	}
	cs_int nNewLen = Length() - len;
	if (nNewLen < 0)
	{
		return false;
	}
	memcpy(pBuf, GetHead(), len);
	m_nHeadCursor += len;
	return true;
}

cs_bool CsBytes_Ex::WriteToStr(cs_char *str, cs_size_t maxsize)
{
	cs_size_t len_old = Length();
	cs_size_t len = 0;
	for (cs_size_t i = 0; i < len_old; i++)
	{
		cs_byte *b = GetHead() + i;
		if (b[0] == '\0')
		{
			len = i + 1;
			break;
		}
	}

	if (len <= 0 || len > maxsize)
	{
		return false;
	}
	cs_int len_new = len_old - len;
	if (len_new < 0)
	{
		return false;
	}
	memcpy(str, GetHead(), len);
	m_nHeadCursor += len;
	return true;
}

cs_bool CsBytes_Ex::Valid() const
{
	return m_tBlock.Valid() 
		&& m_nHeadCursor >= 0 
		&& m_nTailCursor > m_nHeadCursor 
		&& m_nTailCursor <= m_tBlock.Size();
}

cs_byte *CsBytes_Ex::GetTail() const
{
	if (!m_tBlock.Valid() || m_nHeadCursor < 0 || m_tBlock.Size() <= m_nHeadCursor)
	{
		return NULL;
	}
	return (cs_byte *)m_tBlock.Cursor(m_nTailCursor);
}

cs_bool CsBytes_Ex::Reserve(cs_size_t size)
{
	cs_size_t capacity = Capacity();
	if (size <= capacity)
	{
		// 无需扩容
		return true;
	}
	if (size - capacity< CS_DEFAULT_ADD_SIZE)
	{
		// 按照扩容步长进行扩容
		size = capacity + CS_DEFAULT_ADD_SIZE;
	}
	cs_size_t n_size = Length();
	if (!m_tBlock.Resize(size, m_nHeadCursor, n_size))
	{
		return false;
	}
	m_nHeadCursor = 0;
	m_nTailCursor = n_size;
	return true;
}

cs_void CsBytes_Ex::Clear()
{
	if (!m_tBlock.Resize(0))
	{
		return;
	}
	m_nHeadCursor = m_nTailCursor = -1;
}
