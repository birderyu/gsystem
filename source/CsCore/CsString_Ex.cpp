#include "CsString_Ex.h"
#include "CsBlock.h"
#include "CsEndian.h"
#include "CsCStringHelper.h"

#define STRING_EX_HASHCODE_BASE 31

cs_size_t CsSmallStr_Ex::MaxSize()
{
	return CS_MIN_STRING_SIZE - 1;
}

cs_bool CsSmallStr_Ex::Initialize()
{
	m_nLength = 0;
	return true;
}

cs_bool CsSmallStr_Ex::Initialize(cs_char cChar)
{
	m_nLength = 1;
	m_cStr[0] = cChar;
	m_cStr[1] = '\0';
	return true;
}

cs_bool CsSmallStr_Ex::Initialize(const cs_char *pStr, cs_size_t len)
{
	cs_size_t real_len(len);
	if (len > CsSmallStr_Ex::MaxSize())
	{
		real_len = CsSmallStr_Ex::MaxSize();
	}
	if (!CsCStringHelper::Copy(pStr, real_len, m_cStr))
	{
		m_nLength = 0;
		return false;
	}
	m_cStr[real_len] = '\0';
	m_nLength = static_cast<cs_uint8>(real_len);
	return true;
}

cs_bool CsSmallStr_Ex::Initialize(const CsSmallStr_Ex &sStr)
{
	if (!CsCStringHelper::Copy(sStr.m_cStr, sStr.m_nLength + 1, m_cStr))
	{
		m_nLength = 0;
		return false;
	}
	m_nLength = sStr.m_nLength;
	return true;
}

cs_size_t CsSmallStr_Ex::Length() const
{
	return m_nLength;
}

cs_char CsSmallStr_Ex::GetAt(cs_size_t id) const
{
	return m_cStr[id];
}

cs_cstring CsSmallStr_Ex::CString() const
{
	return m_cStr;
}

cs_bool CsSmallStr_Ex::MakeTrim()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrim(m_cStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStr_Ex::MakeTrimLeft()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimLeft(m_cStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStr_Ex::MakeTrimRight()
{
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimRight(m_cStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint8>(len);
	return true;
}

cs_bool CsSmallStr_Ex::MakeUpper()
{
	return CsCStringHelper::MakeUpper(m_cStr, m_nLength);
}

cs_bool CsSmallStr_Ex::MakeLower()
{
	return CsCStringHelper::MakeLower(m_cStr, m_nLength);
}

cs_bool CsSmallStr_Ex::SwitchToNormal(CsNormalStr_Ex &sStr) const
{
	return sStr.Initialize(m_cStr, m_nLength);
}

cs_size_t CsNormalStr_Ex::MaxSize()
{
	return CS_MAX_STRING_SIZE;
}

cs_bool CsNormalStr_Ex::Initialize(const cs_char *pStr, cs_size_t len)
{
	cs_size_t real_len(len);
	if (len > CsNormalStr_Ex::MaxSize())
	{
		real_len = CsNormalStr_Ex::MaxSize();
	}
	m_pStr = (cs_char*)CsCalloc(real_len + 1, sizeof(cs_char));
	if (!m_pStr)
	{
		m_nLength = 0;
		return false;
	}
	if (!CsCStringHelper::Copy(pStr, real_len, m_pStr))
	{
		CsFree(m_pStr);
		m_nLength = 0;
		return false;
	}
	m_pStr[real_len] = '\0';
	m_nLength = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStr_Ex::Initialize(const CsNormalStr_Ex &sStr)
{
	m_pStr = (cs_char*)CsCalloc(sStr.m_nLength + 1, sizeof(cs_char));
	if (!m_pStr)
	{
		m_nLength = 0;
		return false;
	}
	if (!CsCStringHelper::Copy(sStr.m_pStr, sStr.m_nLength + 1, m_pStr))
	{
		CsFree(m_pStr);
		m_nLength = 0;
		return false;
	}
	m_nLength = sStr.m_nLength;
	return true;
}

cs_bool CsNormalStr_Ex::Initialize_Quick(cs_char *pStr, cs_size_t len)
{
	m_pStr = pStr;
	m_nLength = len;
	return true;
}

cs_size_t CsNormalStr_Ex::Length() const
{
	if (!m_pStr)
	{
		return 0;
	}
	return m_nLength;
}

cs_void CsNormalStr_Ex::Free()
{
	if (m_pStr)
	{
		CsFree(m_pStr);
	}
	m_pStr = NULL;
}

cs_char CsNormalStr_Ex::GetAt(cs_size_t id) const
{
	if (!m_pStr)
	{
		return '\0';
	}
	return m_pStr[id];
}

cs_cstring CsNormalStr_Ex::CString() const
{
	return m_pStr;
}

cs_bool CsNormalStr_Ex::MakeTrim()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrim(m_pStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStr_Ex::MakeTrimLeft()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimLeft(m_pStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStr_Ex::MakeTrimRight()
{
	if (!m_pStr)
	{
		return false;
	}
	cs_size_t len;
	if (!CsCStringHelper::MakeTrimRight(m_pStr, m_nLength, len))
	{
		return false;
	}
	m_nLength = static_cast<cs_uint16>(len);
	return true;
}

cs_bool CsNormalStr_Ex::MakeUpper()
{
	if (!m_pStr)
	{
		return false;
	}
	return CsCStringHelper::MakeUpper(m_pStr, m_nLength);
}

cs_bool CsNormalStr_Ex::MakeLower()
{
	if (!m_pStr)
	{
		return false;
	}
	return CsCStringHelper::MakeLower(m_pStr, m_nLength);
}

cs_bool CsNormalStr_Ex::CanSwithToSmall() const
{
	return m_nLength <= CsSmallStr_Ex::MaxSize();
}

cs_bool CsNormalStr_Ex::SwitchToSmall(CsSmallStr_Ex &sStr) const
{
	return sStr.Initialize(m_pStr, m_nLength);
}

cs_void CsStringStore::Free(CsStringStore &tStrMem)
{
	switch (tStrMem.m_nType)
	{
	case VALUE_STRING_NORMAL:
		tStrMem.m_sNormalStr.Free();
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
	tStrMem.m_nType = VALUE_STRING_SMALL;
	tStrMem.m_sSmallStr.Initialize();
}

CsString_Ex::CsString_Ex()
{
	m_tStrMem.m_nType = VALUE_STRING_SMALL;
	m_tStrMem.m_sSmallStr.Initialize();
}

CsString_Ex::CsString_Ex(cs_char cChar)
{
	m_tStrMem.m_nType = VALUE_STRING_SMALL;
	m_tStrMem.m_sSmallStr.Initialize(cChar);
}

CsString_Ex::CsString_Ex(const cs_char *pStr)
{
	cs_size_t len = CsCStringHelper::Length(pStr);
	if (len <= 0)
	{
		m_tStrMem.m_nType = VALUE_STRING_SMALL;
		m_tStrMem.m_sSmallStr.Initialize();
	}
	else if (len <= CsSmallStr_Ex::MaxSize())
	{
		// 小字符串
		m_tStrMem.m_nType = VALUE_STRING_SMALL;
		m_tStrMem.m_sSmallStr.Initialize(pStr, len);
	}
	else if (len <= CsNormalStr_Ex::MaxSize())
	{
		// 普通字符串
		m_tStrMem.m_nType = VALUE_STRING_NORMAL;
		m_tStrMem.m_sNormalStr.Initialize(pStr, len);
	}
	else
	{
		// 大字符串
		m_tStrMem.m_nType = VALUE_STRING_BIG;
		// TODO
	}
}

CsString_Ex::CsString_Ex(const CsString_Ex &sStr)
{
	m_tStrMem.m_nType = sStr.m_tStrMem.m_nType;
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		m_tStrMem.m_sSmallStr.Initialize(sStr.m_tStrMem.m_sSmallStr);
		break;
	case VALUE_STRING_NORMAL:
		m_tStrMem.m_sNormalStr.Initialize(sStr.m_tStrMem.m_sNormalStr);
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		m_tStrMem.m_nType = VALUE_STRING_SMALL;
		m_tStrMem.m_sSmallStr.Initialize();
		break;
	}
}

CsString_Ex::~CsString_Ex()
{
	Free();
}

cs_bool CsString_Ex::Initialize()
{
	Free();
	return true;
}

cs_bool CsString_Ex::Initialize(cs_char cChar)
{
	Free();
	m_tStrMem.m_nType = VALUE_STRING_SMALL;
	return m_tStrMem.m_sSmallStr.Initialize(cChar);
}

cs_bool CsString_Ex::Initialize(const cs_char *pStr)
{
	Free();
	cs_size_t len = CsCStringHelper::Length(pStr);
	if (len <= 0)
	{
		m_tStrMem.m_nType = VALUE_STRING_SMALL;
		return m_tStrMem.m_sSmallStr.Initialize();
	}

	if (len <= CsSmallStr_Ex::MaxSize())
	{
		// 小字符串
		m_tStrMem.m_nType = VALUE_STRING_SMALL;
		return m_tStrMem.m_sSmallStr.Initialize(pStr, len);
	}

	if (len <= CsNormalStr_Ex::MaxSize())
	{
		// 普通字符串
		m_tStrMem.m_nType = VALUE_STRING_NORMAL;
		return m_tStrMem.m_sNormalStr.Initialize(pStr, len);
	}

	// 大字符串
	m_tStrMem.m_nType = VALUE_STRING_BIG;
	// TODO
	return false;
}

cs_bool CsString_Ex::Initialize(const CsString_Ex &sStr)
{
	Free();
	m_tStrMem.m_nType = sStr.m_tStrMem.m_nType;
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		return m_tStrMem.m_sSmallStr.Initialize(sStr.m_tStrMem.m_sSmallStr);
		break;
	case VALUE_STRING_NORMAL:
		return m_tStrMem.m_sNormalStr.Initialize(sStr.m_tStrMem.m_sNormalStr);
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
	return true;
}

cs_bool CsString_Ex::IsReference() const
{
	return m_tStrMem.m_nType == REFERENCE_STRING;
}

cs_bool CsString_Ex::IsSmall() const
{
	if (m_tStrMem.m_nType == VALUE_STRING_SMALL)
	{
		return true;
	}
	else if (m_tStrMem.m_nType == REFERENCE_STRING)
	{
		// 引用类型，根据引用的类型去判断是否是小字符串
		// TODO
	}
	return false;
}

cs_bool CsString_Ex::IsLarge() const
{
	if (m_tStrMem.m_nType == VALUE_STRING_BIG)
	{
		return true;
	}
	else if (m_tStrMem.m_nType == REFERENCE_STRING)
	{
		// 引用类型，根据引用的类型去判断是否是大字符串
		// TODO
	}
	return false;
}

cs_bool CsString_Ex::IsSerial() const
{
	// TODO
	return false;
}

CsString_Ex &CsString_Ex::ToValue()
{
	if (IsReference())
	{
		// 引用类型，将其转换成值
		// TODO
	}
	return *this;
}

cs_char CsString_Ex::GetAt(cs_size_t id) const
{
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		return m_tStrMem.m_sSmallStr.GetAt(id);
		break;
	case VALUE_STRING_NORMAL:
		return m_tStrMem.m_sNormalStr.GetAt(id);
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
}

cs_cstring CsString_Ex::CString() const
{
	if (IsEmpty())
	{
		return "";
	}
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		return m_tStrMem.m_sSmallStr.CString();
		break;
	case VALUE_STRING_NORMAL:
		return m_tStrMem.m_sNormalStr.CString();
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
	return "";
}

cs_size_t CsString_Ex::Length() const
{
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		return m_tStrMem.m_sSmallStr.Length();
		break;
	case VALUE_STRING_NORMAL:
		return m_tStrMem.m_sNormalStr.Length();
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
	return 0;
}

cs_bool CsString_Ex::IsEmpty() const
{
	return Length() == 0;
}

CsString_Ex &CsString_Ex::MakeTrim()
{
	if (Length() <= 0)
	{
		return *this;
	}

	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		m_tStrMem.m_sSmallStr.MakeTrim();
		return *this;
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		m_tStrMem.m_sNormalStr.MakeTrim();
		return *this;
	}
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}
	return *this;
}

CsString_Ex &CsString_Ex::MakeTrimLeft()
{
	if (Length() <= 0)
	{
		return *this;
	}

	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		m_tStrMem.m_sSmallStr.MakeTrimLeft();
		return *this;
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		m_tStrMem.m_sNormalStr.MakeTrimLeft();
		return *this;
	}
		// TODO
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	return *this;
}

CsString_Ex &CsString_Ex::MakeTrimRight()
{
	if (Length() <= 0)
	{
		return *this;
	}

	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		m_tStrMem.m_sSmallStr.MakeTrimRight();
		return *this;
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		m_tStrMem.m_sNormalStr.MakeTrimRight();
		return *this;
	}
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	return *this;
}

CsString_Ex &CsString_Ex::MakeUpper()
{
	if (Length() <= 0)
	{
		return *this;
	}
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		m_tStrMem.m_sSmallStr.MakeUpper();
		return *this;
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		m_tStrMem.m_sNormalStr.MakeUpper();
		return *this;
	}
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	return *this;
}

CsString_Ex &CsString_Ex::MakeLower()
{
	if (Length() <= 0)
	{
		return *this;
	}
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		m_tStrMem.m_sSmallStr.MakeLower();
		return *this;
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		m_tStrMem.m_sNormalStr.MakeLower();
		return *this;
	}
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	return *this;
}

CsString_Ex &CsString_Ex::Replace(const cs_char *from, cs_size_t from_len, const cs_char *to, cs_size_t to_len, cs_bool bIsSensitive)
{
	if (Length() <= 0 || !from || from_len <= 0 ||
		(!to && to_len > 0))
	{
		// 无需替换
		return *this;
	}

	// 转换为值类型
	ToValue();

	// 预算一下替换过后的长度，长度按尽量可能大去计算
	cs_size_t length = Length();
	cs_size_t estimate_len = length;
	if (from_len < to_len)
	{
		// 有可能会被扩容
		estimate_len = length * to_len / from_len + 1;
	}
	CS_STRING_EX_TYPE nEstimateType = GetTypeByLength(estimate_len);

	if (nEstimateType == VALUE_STRING_SMALL)
	{
		// 替换之后为小字符串
		cs_char cStr[CS_MIN_STRING_SIZE];
		cs_size_t out_len = 0;
		if (!CsCStringHelper::Replace(CString(), length, from, from_len, to, to_len, bIsSensitive,
			cStr, out_len))
		{
			return *this;
		}
		Free();
		m_tStrMem.m_nType = nEstimateType;
		m_tStrMem.m_sSmallStr.Initialize(cStr, out_len);
		return *this;
	}
	if (nEstimateType != VALUE_STRING_BIG)
	{
		// 替换之后为普通字符串
		cs_char *pStr = (cs_char*)CsCalloc(estimate_len + 1, sizeof(cs_char));
		cs_size_t out_len = 0;
		if (!CsCStringHelper::Replace(CString(), length, from, from_len, to, to_len, bIsSensitive,
			pStr, out_len))
		{
			CsFree(pStr);
			return *this;
		}
		Free();
		m_tStrMem.m_nType = nEstimateType;
		m_tStrMem.m_sNormalStr.Initialize_Quick(pStr, out_len);
		return *this;
	}
	else
	{
		// 替换之后为大字符串
		// TODO
	}
	return *this;
}

CsString_Ex &CsString_Ex::Replace(cs_size_t start, cs_size_t length, const cs_char *to, cs_size_t to_len, cs_bool bIsSensitive)
{
	// 转换为值类型
	ToValue();

	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
		// TODO
		break;
	case VALUE_STRING_NORMAL:
		// TODO
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	return *this;
}

CsString_Ex &CsString_Ex::Switch(CS_STRING_EX_TYPE emType, cs_bool *pIsOk)
{
	if (m_tStrMem.m_nType == emType)
	{
		if (pIsOk)
		{
			*pIsOk = true;
		}
		return *this;
	}

	cs_bool bIsOK = false;
	switch (m_tStrMem.m_nType)
	{
	case VALUE_STRING_SMALL:
	{
		switch (emType)
		{
		case VALUE_STRING_NORMAL:
		{
			// 拷贝副本
			CsString_Ex _sStr(*this);
			// 转换
			bIsOK = _sStr.m_tStrMem.m_sSmallStr.SwitchToNormal(m_tStrMem.m_sNormalStr);
		}
			break;
		case VALUE_STRING_BIG:
			// TODO
			break;
		default:
			break;
		}
	}
		break;
	case VALUE_STRING_NORMAL:
	{
		switch (emType)
		{
		case VALUE_STRING_SMALL:
		{
			// 拷贝副本
			CsString_Ex _sStr(*this);
			// 释放内存
			m_tStrMem.m_sNormalStr.Free();
			// 转换
			bIsOK = _sStr.m_tStrMem.m_sNormalStr.SwitchToSmall(m_tStrMem.m_sSmallStr);
		}
			break;
		case VALUE_STRING_BIG:
			// TODO
			break;
		default:
			break;
		}
	}
		break;
	case VALUE_STRING_BIG:
		// TODO
		break;
	case REFERENCE_STRING:
		// TODO
		break;
	default:
		break;
	}

	if (bIsOK)
	{
		// 转换成功
		m_tStrMem.m_nType = emType;
	}
	if (pIsOk)
	{
		*pIsOk = bIsOK;
	}
	return *this;
}

CS_STRING_EX_TYPE CsString_Ex::GetTypeByLength(cs_size_t len) const
{
	if (len <= CsSmallStr_Ex::MaxSize())
	{
		// 小字符串
		return VALUE_STRING_SMALL;
	}

	if (len <= CsNormalStr_Ex::MaxSize())
	{
		// 普通字符串
		return VALUE_STRING_NORMAL;
	}
	
	// 大字符串
	return VALUE_STRING_BIG;
}

CsString_Ex &CsString_Ex::Collect(cs_bool *pIsOk /*= NULL*/)
{
	cs_size_t length = Length();
	if (length <= CsSmallStr_Ex::MaxSize())
	{

	}
	return *this;
}

cs_void CsString_Ex::Free()
{
	CsStringStore::Free(m_tStrMem);
}
