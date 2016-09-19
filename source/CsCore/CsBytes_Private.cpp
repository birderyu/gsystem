#include "CsBytes_Private.h"
#include "CsBytes.h"
#include <string>

CsMemoryPool CsBytes_Private::m_tMemoryPool(sizeof(CsBytes_Private));

CsBytes_Private::CsBytes_Private(CsBytes *pPublic, const cs_size_t nCapacity)
: CsObject_Private(pPublic), m_pBuffer(NULL), m_nCapacity(nCapacity), m_nLength(0)
{
	if (m_nCapacity > 0)
	{
		m_pBuffer = (cs_byte*)malloc(sizeof(cs_byte)* m_nCapacity);
		memset(m_pBuffer, 0, sizeof(cs_byte)* m_nCapacity);
	}
}

CsBytes_Private::CsBytes_Private(CsBytes *pPublic, const CsBytes_Private &tBytes)
: CsObject_Private(pPublic), m_pBuffer(NULL), m_nCapacity(0), m_nLength(0)
{
	if (tBytes.m_nCapacity > 0 && tBytes.m_pBuffer)
	{
		m_pBuffer = (cs_byte*)malloc(sizeof(cs_byte) * tBytes.m_nCapacity);
		memcpy(m_pBuffer, tBytes.m_pBuffer, sizeof(cs_byte) * tBytes.m_nCapacity);
		m_nCapacity = tBytes.m_nCapacity;
	}
}

CsBytes_Private::~CsBytes_Private()
{
	Free();
}

cs_bool CsBytes_Private::IsEmpty() const
{
	return false;
}

cs_byte *CsBytes_Private::GetBuffer() const
{
	return m_pBuffer;
}

cs_bool CsBytes_Private::Alloc()
{
	return false;
}

cs_void CsBytes_Private::Free()
{
	if (m_pBuffer)
	{
		free(m_pBuffer);
		m_pBuffer = NULL;
	}
	m_nCapacity = 0;
}
