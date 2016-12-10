#include "CsFilter_Ex.h"
#include "CsString.h"
#include "CsListStack.h"

// 支持的联合类型，按照优先级排列
CsStringList CsFilter_Ex::m_tUnionSymbols;
cs_bool CsFilter_Ex::m_bInitializeUnionSymbols = false;

// 支持的比较类型，按优先级排列
CsStringList CsFilter_Ex::m_tCompareSymbols;
cs_bool CsFilter_Ex::m_bInitializeCompareSymbols = false;

//////////////////////////////////////////////////////////////////////////
// CsFilterCell
//////////////////////////////////////////////////////////////////////////
CsFilter_Ex::CsFilterCell::CsFilterCell()
:m_emCompareType(COMPARE_TYPE_ERROR)
{
	
}

CsFilter_Ex::CsFilterCell::CsFilterCell(const CsFilterCell &tCell)
: m_emCompareType(tCell.m_emCompareType)
, m_sFieldName(tCell.m_sFieldName)
, m_tFieldValue(tCell.m_tFieldValue)
{

}

CsFilter_Ex::CsFilterCell::~CsFilterCell()
{

}

cs_bool CsFilter_Ex::CsFilterCell::SetFilter(const CsString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	
	cs_size_t len = m_tCompareSymbols.Length();
	for (cs_size_t i = 0; i < len; i++)
	{
		CsStringList tFilterList = sFilter.Split(m_tCompareSymbols.GetAt(i));
		if (tFilterList.Length() != 2)
		{
			continue;
		}
		m_sFieldName = tFilterList.GetAt(0);
		if (!CsFilterParse::ParseFilter_ParseCompareType(m_tCompareSymbols.GetAt(i), m_emCompareType))
		{
			return false;
		}
		m_tFieldValue.SetValue(tFilterList.GetAt(i));
		return true;
	}
	return false;
}

cs_bool CsFilter_Ex::CsFilterCell::IsValid() const
{
	return m_emCompareType != COMPARE_TYPE_ERROR
		&& !m_sFieldName.IsEmpty()
		&& m_tFieldValue.IsValid();
}

cs_bool CsFilter_Ex::CsFilterCell::Release()
{
	m_emCompareType = COMPARE_TYPE_ERROR;
	return true;
}

CsString CsFilter_Ex::CsFilterCell::ToString() const
{
	if (!IsValid())
	{
		return "";
	}
	CsString sCompare;
	if (!CsFilterParse::GetCompareString(m_emCompareType, sCompare))
	{
		return "";
	}
	return m_sFieldName + sCompare + m_tFieldValue.ToString();
}

CsFilter_Ex::CsFilterCell &CsFilter_Ex::CsFilterCell::operator=(const CsFilterCell &tCell)
{
	m_sFieldName = tCell.m_sFieldName;
	m_tFieldValue = tCell.m_tFieldValue;
	m_emCompareType = tCell.m_emCompareType;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// CsFilterData
//////////////////////////////////////////////////////////////////////////
CsFilter_Ex::CsFilterData::CsFilterData()
: m_emUnionType(UNION_TYPE_ERROR)
{

}

CsFilter_Ex::CsFilterData::CsFilterData(const CsFilterData &tData)
: m_emUnionType(tData.m_emUnionType)
{
	if (m_emUnionType == UNION_TYPE_ERROR)
	{
		return;
	}
	else if (m_emUnionType == UNION_TYPE_SINGLE)
	{
		m_tCell = tData.m_tCell;
	}
	else
	{
		m_tChildren = tData.m_tChildren;
	}
}

cs_bool CsFilter_Ex::CsFilterData::SetFilter(const CsString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	return CsFilterParse::ParseFilter(sFilter, m_emUnionType, m_tChildren, m_tCell);
}

cs_bool CsFilter_Ex::CsFilterData::IsValid() const
{
	switch (m_emUnionType)
	{
	case UNION_TYPE_ERROR:
		return false;
		break;
	case UNION_TYPE_SINGLE:
		return m_tCell.IsValid();
		break;
	default:
	{
		cs_size_t len = m_tChildren.Size();
		if (len == 0)
		{
			return false;
		}
		for (cs_size_t i = 0; i < len; i++)
		{
			if (!m_tChildren[i].IsValid())
			{
				return false;
			}
		}
		return true;
	}
		break;
	}
	return false;
}

CsString CsFilter_Ex::CsFilterData::ToString() const
{
	if (!IsValid())
	{
		return "";
	}
	if (m_emUnionType == UNION_TYPE_SINGLE)
	{
		return m_tCell.ToString();
	}
	else
	{
		CsString sResult = "";
		cs_size_t len = m_tChildren.Size();
		cs_bool bNeedBracket = false;
		if (len > 0)
		{
			bNeedBracket = true;
		}
		for (cs_size_t i = 0; i < len; i++)
		{
			if (bNeedBracket)
			{
				sResult += "(";
			}
			sResult += m_tChildren[i].ToString();
			if (bNeedBracket)
			{
				sResult += ")";
			}
			if (i != len - 1)
			{
				CsString sUnion;
				if (CsFilterParse::GetUnionString(m_emUnionType, sUnion))
				{
					sResult += sUnion;
				}
			}
		}
		return sResult;
	}
	return "";
}

cs_bool CsFilter_Ex::CsFilterData::Release()
{
	m_emUnionType = UNION_TYPE_ERROR;
	m_tChildren.Clear();
	m_tCell.Release();
	return true;
}

CsFilter_Ex::CsFilterData &CsFilter_Ex::CsFilterData::operator = (const CsFilterData &tData)
{
	m_emUnionType = tData.m_emUnionType;
	if (m_emUnionType == UNION_TYPE_ERROR)
	{
		return *this;
	}
	else if (m_emUnionType == UNION_TYPE_SINGLE)
	{
		m_tCell = tData.m_tCell;
	}
	else
	{
		m_tChildren = tData.m_tChildren;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// CsFilterParse
//////////////////////////////////////////////////////////////////////////
cs_bool CsFilter_Ex::CsFilterParse::ParseFilter(const CsString &sFilter, CS_UNION_TYPE &emUnionType, 
	CsDynamicArray<CsFilterData> &tData, CsFilterCell &tCell)
{
	// 1.判断括号是否合法
	if (!ParseFilter_IsBracketLegal(sFilter))
	{
		return false;
	}

	CsString _sFilter(sFilter);
	// 2.预处理字符串（替换无法识别的字符+去除两边无效的括号）
	if (!ParseFilter_PreParseFilter(_sFilter)
		|| !ParseFilter_TrimBracket(_sFilter))
	{
		return false;
	}

	// 3.分解字符串
	cs_size_t nUnionCount = m_tUnionSymbols.Length();
	cs_bool bHasBracket = false;
	if (_sFilter.Find('(') != -1 && _sFilter.Find(')') != -1)
	{
		bHasBracket = true;
	}

	for (cs_size_t i = 0; i < nUnionCount; i++)
	{
		CsString sUnion = m_tUnionSymbols.GetAt(i);
		CsStringList tFilterList;
		if (bHasBracket)
		{
			// 有括号
			if (!ParseFilter_BreakUpBracketOnOneLevel(_sFilter, sUnion, tFilterList))
			{
				return false;
			}
		}
		else
		{
			// 无括号
			tFilterList = _sFilter.Split(sUnion, true);
		}

		cs_size_t nLenOfUnion = tFilterList.Length();
		if (nLenOfUnion == 1)
		{
			if (i == nUnionCount - 1)
			{
				// 说明为简单类型
				emUnionType = UNION_TYPE_SINGLE;
				return tCell.SetFilter(_sFilter);
			}
			else
			{
				// 判断下一个连接符号
				continue;
			}
		}
		else
		{
			// 已经能够得出当前类型
			if (!ParseFilter_ParseUnionType(sUnion, emUnionType)
				|| !tData.Resize(nLenOfUnion))
			{
				return false;
			}
			for (cs_size_t i = 0; i < nLenOfUnion; i++)
			{
				if (!tData[i].SetFilter(tFilterList.GetAt(i)))
				{
					return false;
				}
			}
			return true;
		}

	}
	return true;
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_PreParseFilter(CsString &sFilter)
{
	if (sFilter.IsEmpty())
	{
		return false;
	}
	sFilter = sFilter.ToUpper().Replace("'", "").Replace(";", " AND ");
	return !sFilter.IsEmpty();
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_ParseUnionType(const CsString &sUnion, CS_UNION_TYPE &emUnionType)
{
	if (sUnion == " AND ")
	{
		emUnionType = UNION_TYPE_AND;
		return true;
	}
	if (sUnion == " OR ")
	{
		emUnionType = UNION_TYPE_OR;
		return true;
	}

	emUnionType = UNION_TYPE_ERROR;
	return false;
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_IsBracketLegal(const CsString &sFilter)
{
	cs_size_t length = sFilter.Length();
	CsListStack<cs_char> stack;

	for (cs_size_t i = 0; i < length; i++)
	{
		if (sFilter[i] == '(')
		{
			stack.Push(sFilter[i]);
		}
		else if (sFilter[i] == ')')
		{
			if (!stack.Pop())
			{
				return false;
			}
		}
	}
	return stack.IsEmpty();
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_TrimBracket(CsString &sFilter)
{
	if (sFilter[0] == '(' && sFilter[sFilter.Length() - 1] == ')')
	{
		// 移除括号
		sFilter = sFilter.SubString(1, sFilter.Length() - 2);
		return ParseFilter_TrimBracket(sFilter);
	}
	else
	{
		return true;
	}
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_BreakUpBracketOnOneLevel(const CsString &sFilter, const CsString &sUnion, CsStringList &tFilterList)
{
	cs_size_t length = sFilter.Length();
	CsListStack<cs_char> stack;
	cs_size_t cursor = 0;
	for (cs_size_t i = 0; i < length; i++)
	{
		cs_int id = sFilter.Find(sUnion, i);
		if (id < 0)
		{
			tFilterList.Add(sFilter.SubString(i, length - i));
			return true;
		}
		if (stack.IsEmpty())
		{
			tFilterList.Add(sFilter.SubString(cursor, i - cursor));
			i += sUnion.Length();
			cursor = i;
		}
		else
		{
			if (sFilter[i] == '(')
			{
				stack.Push(sFilter[i]);
			}
			else if (sFilter[i] == ')')
			{
				stack.Pop();
			}
		}
	}

	return true;
}

cs_bool CsFilter_Ex::CsFilterParse::GetUnionString(CS_UNION_TYPE emUnionType, CsString &sUnion)
{
	switch (emUnionType)
	{
	case CsFilter_Ex::UNION_TYPE_ERROR:
		return false;
		break;
	case CsFilter_Ex::UNION_TYPE_SINGLE:
		return false;
		break;
	case CsFilter_Ex::UNION_TYPE_AND:
		sUnion = " AND ";
		return true;
		break;
	case CsFilter_Ex::UNION_TYPE_OR:
		sUnion = " OR ";
		return true;
		break;
	default:
		break;
	}
	return false;
}

cs_bool CsFilter_Ex::CsFilterParse::ParseFilter_ParseCompareType(const CsString &sCompare, CS_COMPARE_TYPE &emCompareType)
{
	if (sCompare == " LIKE ")
	{
		emCompareType = COMPARE_TYPE_LIKE;
		return true;
	}
	if (sCompare == " != ")
	{
		emCompareType = COMPARE_TYPE_NOTEQUAL;
		return true;
	}
	if (sCompare == " >= ")
	{
		emCompareType = COMPARE_TYPE_GREATER_EQUAL;
		return true;
	}
	if (sCompare == " <= ")
	{
		emCompareType = COMPARE_TYPE_LESS_EQUAL;
		return true;
	}
	if (sCompare == " = ")
	{
		emCompareType = COMPARE_TYPE_EQUAL;
		return true;
	}
	if (sCompare == " > ")
	{
		emCompareType = COMPARE_TYPE_GREATER;
		return true;
	}
	if (sCompare == " < ")
	{
		emCompareType = COMPARE_TYPE_LESS;
		return true;
	}
	emCompareType = COMPARE_TYPE_ERROR;
	return false;
}

cs_bool CsFilter_Ex::CsFilterParse::GetCompareString(CS_COMPARE_TYPE emCompareType, CsString &sCompare)
{
	switch (emCompareType)
	{
	case CsFilter_Ex::COMPARE_TYPE_ERROR:
		return false;
		break;
	case CsFilter_Ex::COMPARE_TYPE_EQUAL:
		sCompare = " = ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_LESS:
		sCompare = " < ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_LESS_EQUAL:
		sCompare = " <= ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_GREATER:
		sCompare = " > ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_GREATER_EQUAL:
		sCompare = " >= ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_NOTEQUAL:
		sCompare = " != ";
		return true;
		break;
	case CsFilter_Ex::COMPARE_TYPE_LIKE:
		sCompare = " LIKE ";
		return true;
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// CsFilter_Private
//////////////////////////////////////////////////////////////////////////
CsFilter_Ex::CsFilter_Ex(const CsString &sFilter)
{
	Initialize();
	if (!sFilter.IsEmpty())
	{
		SetFilter(sFilter);
	}
}

CsFilter_Ex::CsFilter_Ex(const CsFilter_Ex &tFilter)
: m_tFilterData(tFilter.m_tFilterData)
{
	Initialize();
}

CsFilter_Ex::~CsFilter_Ex()
{
	Release();
}

cs_bool CsFilter_Ex::SetFilter(const CsString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	cs_bool bRet = m_tFilterData.SetFilter(sFilter);
	if (!bRet)
	{
		Release();
	}
	return bRet;
}

CsFilter_Ex &CsFilter_Ex::operator = (const CsFilter_Ex &tFilter)
{
	m_tFilterData = tFilter.m_tFilterData;
	return *this;
}

cs_bool CsFilter_Ex::IsValid() const
{
	return m_tFilterData.IsValid();
}

CsString CsFilter_Ex::ToString() const
{
	return m_tFilterData.ToString();
}

cs_bool CsFilter_Ex::Initialize()
{
	if (!m_bInitializeUnionSymbols)
	{
		m_tUnionSymbols = CsString(" AND ; OR ").Split(";");
		m_bInitializeUnionSymbols = true;
	}
	if (!m_bInitializeCompareSymbols)
	{
		m_tCompareSymbols = CsString(" LIKE ; != ; >= ; <= ; = ; > ; < ").Split(";");
		m_bInitializeCompareSymbols = true;
	}
	return true;
}

cs_bool CsFilter_Ex::Release()
{
	return m_tFilterData.Release();
}