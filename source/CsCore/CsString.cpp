#include "CsString.h"
#include "CsStringList.h"
#include "CsCStringHelper.h"

CsString::CsString()
{
	m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	m_tStringStore.m_sSmallStr.Initialize();
}

CsString::CsString(cs_char cChar)
{
	m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	m_tStringStore.m_sSmallStr.Initialize(cChar);
}

CsString::CsString(const cs_char *pStr)
{
	cs_size_t size = CsCStringHelper::Size(pStr);
	if (size <= 0)
	{
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
	}
	else if (size <= CsSmallStringStore::MAX_SIZE)
	{
		// 小字符串
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize(pStr, size);
	}
	else if (size <= CsNormalStringStore::MAX_SIZE)
	{
		// 普通字符串
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
		m_tStringStore.m_sNormalStr.Initialize(pStr, size);
	}
	else
	{
		// 大字符串
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_BIG;
		// TODO
	}
}

CsString::CsString(const CsString &sStr)
{
	m_tStringStore.m_nType = sStr.m_tStringStore.m_nType;
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		m_tStringStore.m_sSmallStr.Initialize(sStr.m_tStringStore.m_sSmallStr);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		m_tStringStore.m_sNormalStr.Initialize(sStr.m_tStringStore.m_sNormalStr);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case CsStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
		break;
	}
}

CsString::~CsString()
{
	Free();
}

CsString CsString::FromStdString(const std::string &sStr)
{
	return CsString(sStr.c_str());
}

cs_bool CsString::IsEmpty() const
{
	return Size() == 0;
}

CsString CsString::Trim() const
{
	CsString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrim();
		return sStr;
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrim();
		return sStr;
	}
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
	return sStr;
}

CsString CsString::TrimLeft() const
{
	CsString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrimLeft();
		return sStr;
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrimLeft();
		return sStr;
	}
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
	return sStr;
}

CsString CsString::TrimRight() const
{
	CsString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrimRight();
		return sStr;
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrimRight();
		return sStr;
	}
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

	return sStr;
}

CsString CsString::ToUpper() const
{
	CsString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeUpper();
		return sStr;
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeUpper();
		return sStr;
	}
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

	return sStr;
}

CsString CsString::ToLower() const
{
	CsString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeLower();
		return sStr;
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeLower();
		return sStr;
	}
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

	return sStr;
}

cs_cstring CsString::CString() const
{
	if (IsEmpty())
	{
		return "";
	}
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.CString();
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.CString();
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
	return "";
}

cs_size_t CsString::Size() const
{
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Size();
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Size();
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
	return 0;
}

cs_bool CsString::Resize(cs_size_t size)
{
	if (size == 0)
	{
		Free();
	}

	// 转换为值类型
	ToValue();

	// size相等则不做任何操作
	if (size == Size())
	{
		return true;
	}

	// 判断Resize之后的类型
	CsStringStore::TYPE emType = GetTypeBySize(size);
	if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_SMALL)
	{
		// Resize之后应该为小字符串
		if (!Switch(emType))
		{
			return false;
		}
		m_tStringStore.m_sSmallStr.m_nSize = size;
		m_tStringStore.m_sSmallStr.m_cStr[size] = '\0';
		return true;
	}
	else if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
	{
		// Resize之后应该为普通字符串
		if (m_tStringStore.m_nType == CsStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// 原本是小字符串
			CsString str_copy(*this);
			m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
			if (!m_tStringStore.m_sNormalStr.Initialize(size))
			{
				// 开辟内存
				return false;
			}
			if (!m_tStringStore.m_sNormalStr.CopyString(str_copy.CString(), str_copy.Size()))
			{
				// 拷贝原有字符串
				return false;
			}
			// 改变Size
			m_tStringStore.m_sNormalStr.m_pStr[size] = '\0';
			m_tStringStore.m_sNormalStr.m_nSize = static_cast<cs_uint16>(size);
			return true;
		}
		else if (m_tStringStore.m_nType == CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			// 原本是普通字符串
			return m_tStringStore.m_sNormalStr.Resize(size);
		}
		else
		{
			// 原本是大字符串
			// TODO
		}
	}
	else
	{
		// CsStringStore::STRING_STORE_TYPE_VALUE_BIG
		// Resize之后应该为大字符串
		// TODO
	}
	return false;
}

cs_char CsString::GetAt(cs_size_t pos) const
{
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.GetAt(pos);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.GetAt(pos);
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
}

cs_char &CsString::GetAt(cs_size_t pos)
{
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.GetAt(pos);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.GetAt(pos);
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
}

const cs_char *CsString::Cursor(cs_size_t pos) const
{
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Cursor(pos);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Cursor(pos);
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
	return NULL;
}

cs_char *CsString::Cursor(cs_size_t pos)
{
	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Cursor(pos);
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Cursor(pos);
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
	return NULL;
}

CsString &CsString::Replace(const CsString &from, const CsString &to, cs_bool bIsSensitive)
{
	cs_size_t size = Size();
	cs_size_t from_size = from.Size();
	if (size <= 0 || from_size <= 0)
	{
		return *this;
	}

	cs_cstring cfrom = from.CString();
	cs_cstring cto = to.CString();
	cs_size_t to_size = to.Size();

	if (!cfrom ||
		(!cto && to_size >= 0))
	{
		return *this;
	}

	// 转换为值类型
	ToValue();

	// 预算一下替换过后的长度，长度按尽量可能大去计算
	cs_size_t estimate_size = size;
	if (from_size < to_size)
	{
		// 有可能会被扩容
		estimate_size = size * to_size / from_size + 1;
	}
	CsStringStore::TYPE nEstimateType = GetTypeBySize(estimate_size);

	if (nEstimateType == CsStringStore::STRING_STORE_TYPE_VALUE_SMALL)
	{
		// 替换之后为小字符串
		cs_char cStr[CS_SMALL_STRING_MAX_SIZE];
		cs_size_t out_len = 0;
		if (!CsCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			cStr, out_len))
		{
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sSmallStr.Initialize(cStr, out_len);
		return *this;
	}
	else if (nEstimateType == CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
	{
		// 替换之后为普通字符串
		cs_char *pStr = (cs_char*)CsMalloc((estimate_size + 1) * sizeof(cs_char));
		cs_size_t out_len = 0;
		if (!CsCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			pStr, out_len))
		{
			CsFree(pStr);
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sNormalStr.m_pStr = pStr;
		m_tStringStore.m_sNormalStr.m_nSize = out_len;
		return *this;
	}
	else
	{
		// CsStringStore::STRING_STORE_TYPE_VALUE_BIG
		// 替换之后为大字符串
		// TODO
	}
	return *this;
}

CsStringList CsString::Split(const CsString &sSep, cs_bool bIgnoreEmpty, cs_bool bIsSensitive) const
{
	// TODO
	CsStringList t;
	return t;
}

cs_size_t CsString::Find(cs_char c, cs_size_t start, cs_bool bIsSensitive) const
{
	// TODO
	return NULL_POS;
}

cs_size_t CsString::Find(const CsString &str, cs_size_t start, cs_bool bIsSensitive) const
{
	// TODO
	return NULL_POS;
}

CsString CsString::SubString(cs_size_t start, cs_size_t length) const
{
	return CsString();
}

cs_bool CsString::Equals(const CsString &str, cs_bool bIsSensitive) const
{
	if (bIsSensitive)
	{
		return *this == str;
	}
	return false;
}

cs_bool CsString::Switch(CsStringStore::TYPE emType)
{
	if (m_tStringStore.m_nType == emType)
	{
		return true;
	}

	switch (m_tStringStore.m_nType)
	{
	case CsStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			CsString str_copy(*this);
			Free();
			m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
			str_copy.m_tStringStore.m_sSmallStr.SwitchToNormal(m_tStringStore.m_sNormalStr);
			return true;
		}
		else if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_BIG)
		{
			// TODO
		}
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// TODO
			if (m_tStringStore.m_sNormalStr.CanSwithToSmall())
			{
				CsString str_copy(*this);
				Free();
				m_tStringStore.m_nType = CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
				str_copy.m_tStringStore.m_sNormalStr.SwitchToSmall(m_tStringStore.m_sSmallStr);
				return true;
			}			
		}
		else if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_BIG)
		{
			// TODO
		}
	}
		break;
	case CsStringStore::STRING_STORE_TYPE_VALUE_BIG:
	{
		if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// TODO
		}
		else if (emType == CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			// TODO
		}
	}
		break;
	default:
		break;
	}

	return false;
}

cs_bool CsString::StartWith(cs_char c) const
{
	return GetAt(0) == c;
}

cs_bool CsString::EndWith(cs_char c) const
{
	return GetAt(Size() - 1) == c;
}
