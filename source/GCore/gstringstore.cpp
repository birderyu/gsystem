#include "gstringstore.h"
#include "gcstringhelper.h"
#include "gnew.h"

//////////////////////////////////////////////////////////////////////////

gbool GSmallStringStore::Initialize()
{
	m_nSize = 0;
	return true;
}

gbool GSmallStringStore::Initialize(gchar cChar)
{
	m_nSize = 1;
	m_cStr[0] = cChar;
	m_cStr[1] = '\0';
	return true;
}

gbool GSmallStringStore::Initialize(const gchar *pStr, gsize size)
{
	gsize real_len(size);
	if (size > GSmallStringStore::MAX_SIZE)
	{
		real_len = GSmallStringStore::MAX_SIZE;
	}
	if (!GCStringHelper::Copy(pStr, real_len, m_cStr))
	{
		m_nSize = 0;
		return false;
	}
	m_cStr[real_len] = '\0';
	m_nSize = static_cast<guint8>(real_len);
	return true;
}

gbool GSmallStringStore::Initialize(const GSmallStringStore &sStr)
{
	if (!GCStringHelper::Copy(sStr.m_cStr, sStr.m_nSize + 1, m_cStr))
	{
		m_nSize = 0;
		return false;
	}
	m_nSize = sStr.m_nSize;
	return true;
}

gsize GSmallStringStore::Size() const
{
	return m_nSize;
}

gchar GSmallStringStore::GetAt(gsize pos) const
{
	GASSERT(pos < MAX_SIZE);
	return m_cStr[pos];
}

gchar &GSmallStringStore::GetAt(gsize pos)
{
	GASSERT(pos < MAX_SIZE);
	return m_cStr[pos];
}

const gchar *GSmallStringStore::Cursor(gsize pos) const
{
	return m_cStr + pos;
}

gchar *GSmallStringStore::Cursor(gsize pos)
{
	return m_cStr + pos;
}

gcstring GSmallStringStore::CString() const
{
	return m_cStr;
}

gbool GSmallStringStore::MakeTrim()
{
	gsize len;
	if (!GCStringHelper::MakeTrim(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint8>(len);
	return true;
}

gbool GSmallStringStore::MakeTrimLeft()
{
	gsize len;
	if (!GCStringHelper::MakeTrimLeft(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint8>(len);
	return true;
}

gbool GSmallStringStore::MakeTrimRight()
{
	gsize len;
	if (!GCStringHelper::MakeTrimRight(m_cStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint8>(len);
	return true;
}

gbool GSmallStringStore::MakeUpper()
{
	return GCStringHelper::MakeUpper(m_cStr, m_nSize);
}

gbool GSmallStringStore::MakeLower()
{
	return GCStringHelper::MakeLower(m_cStr, m_nSize);
}

gbool GSmallStringStore::SwitchToNormal(GNormalStringStore &sStr) const
{
	return sStr.Initialize(m_cStr, m_nSize);
}

//////////////////////////////////////////////////////////////////////////

gbool GNormalStringStore::Initialize(gsize capacity)
{
	m_nSize = 0;
	if (capacity == 0)
	{
		m_pStr = NULL;
		return true;
	}

	gsize real_len(capacity);
	if (capacity > GNormalStringStore::MAX_SIZE)
	{
		real_len = GNormalStringStore::MAX_SIZE;
	}
	
	m_pStr = (gchar*)GMalloc((real_len + 1)* sizeof(gchar));
	if (!m_pStr)
	{
		return false;
	}
	return true;
}

gbool GNormalStringStore::Initialize(const gchar *pStr, gsize size)
{
	gsize real_len(size);
	if (size > GNormalStringStore::MAX_SIZE)
	{
		real_len = GNormalStringStore::MAX_SIZE;
	}
	m_pStr = (gchar*)GMalloc((real_len + 1)* sizeof(gchar));
	if (!m_pStr)
	{
		m_nSize = 0;
		return false;
	}
	if (!GCStringHelper::Copy(pStr, real_len, m_pStr))
	{
		GFree(m_pStr);
		m_nSize = 0;
		return false;
	}
	m_pStr[real_len] = '\0';
	m_nSize = static_cast<guint16>(real_len);
	return true;
}

gbool GNormalStringStore::Initialize(const GNormalStringStore &sStr)
{
	m_pStr = (gchar*)GMalloc((sStr.m_nSize + 1) * sizeof(gchar));
	if (!m_pStr)
	{
		m_nSize = 0;
		return false;
	}
	if (!GCStringHelper::Copy(sStr.m_pStr, sStr.m_nSize + 1, m_pStr))
	{
		GFree(m_pStr);
		m_nSize = 0;
		return false;
	}
	m_nSize = sStr.m_nSize;
	return true;
}

gbool GNormalStringStore::CopyString(const gchar *pStr, gsize size)
{
	if (!m_pStr)
	{
		return false;
	}
	if (!GCStringHelper::Copy(pStr, size, m_pStr))
	{
		return false;
	}
	m_pStr[size] = '\0';
	m_nSize = static_cast<guint16>(size);
	return true;
}

gbool GNormalStringStore::Resize(gsize size)
{
	if (!m_pStr)
	{
		return Initialize(size);
	}
	
	gsize real_len(size);
	if (size > GNormalStringStore::MAX_SIZE)
	{
		real_len = GNormalStringStore::MAX_SIZE;
	}
	if (real_len > Size())
	{
		m_pStr = (gchar*)GRealloc(m_pStr, (real_len + 1)* sizeof(gchar));
		if (!m_pStr)
		{
			m_nSize = 0;
			return false;
		}
	}
	m_pStr[real_len] = '\0';
	m_nSize = static_cast<guint16>(real_len);
	return true;
}

gsize GNormalStringStore::Size() const
{
	return m_nSize;
}

gvoid GNormalStringStore::Free()
{
	if (m_pStr)
	{
		GFree(m_pStr);
	}
	m_pStr = NULL;
}

gchar GNormalStringStore::GetAt(gsize pos) const
{
	GASSERT(m_pStr);
	return m_pStr[pos];
}

gchar &GNormalStringStore::GetAt(gsize pos)
{
	GASSERT(m_pStr);
	return m_pStr[pos];
}

const gchar *GNormalStringStore::Cursor(gsize pos) const
{
	GASSERT(m_pStr);
	return m_pStr + pos;
}

gchar *GNormalStringStore::Cursor(gsize pos)
{
	GASSERT(m_pStr);
	return m_pStr + pos;
}

gcstring GNormalStringStore::CString() const
{
	if (!m_pStr)
	{
		return "";
	}
	return m_pStr;
}

gbool GNormalStringStore::MakeTrim()
{
	if (!m_pStr)
	{
		return false;
	}
	gsize len;
	if (!GCStringHelper::MakeTrim(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint16>(len);
	return true;
}

gbool GNormalStringStore::MakeTrimLeft()
{
	if (!m_pStr)
	{
		return false;
	}
	gsize len;
	if (!GCStringHelper::MakeTrimLeft(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint16>(len);
	return true;
}

gbool GNormalStringStore::MakeTrimRight()
{
	if (!m_pStr)
	{
		return false;
	}
	gsize len;
	if (!GCStringHelper::MakeTrimRight(m_pStr, m_nSize, len))
	{
		return false;
	}
	m_nSize = static_cast<guint16>(len);
	return true;
}

gbool GNormalStringStore::MakeUpper()
{
	if (!m_pStr)
	{
		return false;
	}
	return GCStringHelper::MakeUpper(m_pStr, m_nSize);
}

gbool GNormalStringStore::MakeLower()
{
	if (!m_pStr)
	{
		return false;
	}
	return GCStringHelper::MakeLower(m_pStr, m_nSize);
}

gbool GNormalStringStore::CanSwithToSmall() const
{
	return m_nSize <= GSmallStringStore::MAX_SIZE;
}

gbool GNormalStringStore::SwitchToSmall(GSmallStringStore &sStr) const
{
	return sStr.Initialize(m_pStr, m_nSize);
}

//////////////////////////////////////////////////////////////////////////

gvoid GStringStore::Free(GStringStore &tStrMem)
{
	switch (tStrMem.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		tStrMem.m_sNormalStr.Free();
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	tStrMem.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	tStrMem.m_sSmallStr.Initialize();
}