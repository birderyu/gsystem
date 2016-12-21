#include "CsStringStore.h"
#include "CsCStringHelper.h"
#include "CsNew.h"

cs_bool CsSmallStringStore::Initialize()
{
	m_nSize = 0;
	return true;
}

cs_bool CsSmallStringStore::Initialize(cs_char cChar)
{
	m_nSize = 1;
	m_cStr[0] = cChar;
	m_cStr[1] = '\0';
	return true;
}

cs_bool CsSmallStringStore::Initialize(const cs_char *pStr, cs_size_t len)
{
	cs_size_t real_len(len);
	if (len > CsSmallStringStore::MAX_SIZE)
	{
		real_len = CsSmallStringStore::MAX_SIZE;
	}
	if (!CsCStringHelper::Copy(pStr, real_len, m_cStr))
	{
		m_nSize = 0;
		return false;
	}
	m_cStr[real_len] = '\0';
	m_nSize = static_cast<cs_uint8>(real_len);
	return true;
}

cs_bool CsSmallStringStore::Initialize(const CsSmallStringStore &sStr)
{
	if (!CsCStringHelper::Copy(sStr.m_cStr, sStr.m_nSize + 1, m_cStr))
	{
		m_nSize = 0;
		return false;
	}
	m_nSize = sStr.m_nSize;
	return true;
}

cs_size_t CsSmallStringStore::Size() const
{
	return m_nSize;
}

cs_char CsSmallStringStore::GetAt(cs_size_t pos) const
{
	return m_cStr[pos];
}

cs_cstring CsSmallStringStore::CString() const
{
	return m_cStr;
}

cs_bool CsSmallStringStore::MakeTrim()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrim(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStringStore::MakeTrimLeft()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimLeft(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStringStore::MakeTrimRight()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimRight(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStringStore::MakeUpper()
{
	return CsCStringHelper::MakeUpper(m_cStr, m_nSize);
}

cs_bool CsSmallStringStore::MakeLower()
{
	return CsCStringHelper::MakeLower(m_cStr, m_nSize);
}

cs_bool CsSmallStringStore::SwitchToNormal(CsNormalStringStore &sStr) const
{
	return sStr.Initialize(m_cStr, m_nSize);
}

cs_bool CsNormalStringStore::Initialize(const cs_char *pStr, cs_size_t len)
{
	cs_size_t real_len(len);
	if (len > CsNormalStringStore::MAX_SIZE)
	{
		real_len = CsNormalStringStore::MAX_SIZE;
	}
	m_pStr = (cs_char*)CsMalloc((real_len + 1)* sizeof(cs_char));
	if (!m_pStr)
	{
		m_nSize = 0;
		return false;
	}
	if (!CsCStringHelper::Copy(pStr, real_len, m_pStr))
	{
		CsFree(m_pStr);
		m_nSize = 0;
		return false;
	}
	m_pStr[real_len] = '\0';
	m_nSize = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStringStore::Initialize(const CsNormalStringStore &sStr)
{
	m_pStr = (cs_char*)CsMalloc((sStr.m_nSize + 1) * sizeof(cs_char));
	if (!m_pStr)
	{
		m_nSize = 0;
		return false;
	}
	if (!CsCStringHelper::Copy(sStr.m_pStr, sStr.m_nSize + 1, m_pStr))
	{
		CsFree(m_pStr);
		m_nSize = 0;
		return false;
	}
	m_nSize = sStr.m_nSize;
	return true;
}

cs_size_t CsNormalStringStore::Size() const
{
	if (!m_pStr)
	{
		return 0;
	}
	return m_nSize;
}

cs_void CsNormalStringStore::Free()
{
	if (m_pStr)
	{
		CsFree(m_pStr);
	}
	m_pStr = NULL;
}

cs_char CsNormalStringStore::GetAt(cs_size_t pos) const
{
	if (!m_pStr)
	{
		return '\0';
	}
	return m_pStr[pos];
}

cs_cstring CsNormalStringStore::CString() const
{
	return m_pStr;
}

cs_bool CsNormalStringStore::MakeTrim()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrim(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStringStore::MakeTrimLeft()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimLeft(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStringStore::MakeTrimRight()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimRight(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStringStore::MakeUpper()
{
	if (!m_pStr)
	{
		return false;
	}
	return CsCStringHelper::MakeUpper(m_pStr, m_nSize);
}

cs_bool CsNormalStringStore::MakeLower()
{
	if (!m_pStr)
	{
		return false;
	}
	return CsCStringHelper::MakeLower(m_pStr, m_nSize);
}

cs_bool CsNormalStringStore::CanSwithToSmall() const
{
	return m_nSize <= CsSmallStringStore::MAX_SIZE;
}

cs_bool CsNormalStringStore::SwitchToSmall(CsSmallStringStore &sStr) const
{
	return sStr.Initialize(m_pStr, m_nSize);
}

cs_void CsStringStore::Free(CsStringStore &tStrMem)
{
	switch (tStrMem.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		tStrMem.m_sNormalStr.Free();
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case CsStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	tStrMem.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	tStrMem.m_sSmallStr.Initialize();
}