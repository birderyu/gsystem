#include "CsFilter_Ex.h"
#include "gstring.h"
#include "gstringlist.h"
#include "gliststack.h"

// 支持的联合类型，按照优先级排列
GStringList CsFilter_Ex::m_tUnionSymbols;
gbool CsFilter_Ex::m_bInitializeUnionSymbols = false;

// 支持的比较类型，按优先级排列
GStringList CsFilter_Ex::m_tCompareSymbols;
gbool CsFilter_Ex::m_bInitializeCompareSymbols = false;

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

gbool CsFilter_Ex::CsFilterCell::SetFilter(const GString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	
	gsize size = m_tCompareSymbols.Size();
	for (gsize i = 0; i < size; i++)
	{
		GStringList tFilterList = sFilter.Split(m_tCompareSymbols.GetAt(i));
		if (tFilterList.Size() != 2)
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

gbool CsFilter_Ex::CsFilterCell::IsValid() const
{
	return m_emCompareType != COMPARE_TYPE_ERROR
		&& !m_sFieldName.IsEmpty()
		&& m_tFieldValue.IsValid();
}

gbool CsFilter_Ex::CsFilterCell::Release()
{
	m_emCompareType = COMPARE_TYPE_ERROR;
	return true;
}

GString CsFilter_Ex::CsFilterCell::ToString() const
{
	if (!IsValid())
	{
		return "";
	}
	GString sCompare;
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

gbool CsFilter_Ex::CsFilterData::SetFilter(const GString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	return CsFilterParse::ParseFilter(sFilter, m_emUnionType, m_tChildren, m_tCell);
}

gbool CsFilter_Ex::CsFilterData::IsValid() const
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
		gsize len = m_tChildren.Size();
		if (len == 0)
		{
			return false;
		}
		for (gsize i = 0; i < len; i++)
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

GString CsFilter_Ex::CsFilterData::ToString() const
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
		GString sResult = "";
		gsize len = m_tChildren.Size();
		gbool bNeedBracket = false;
		if (len > 0)
		{
			bNeedBracket = true;
		}
		for (gsize i = 0; i < len; i++)
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
				GString sUnion;
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

gbool CsFilter_Ex::CsFilterData::Release()
{
	m_emUnionType = UNION_TYPE_ERROR;
	m_tChildren.Dispose();
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
gbool CsFilter_Ex::CsFilterParse::ParseFilter(const GString &sFilter, CS_UNION_TYPE &emUnionType, 
	GDynamicArray<CsFilterData> &tData, CsFilterCell &tCell)
{
	// 1.判断括号是否合法
	if (!ParseFilter_IsBracketLegal(sFilter))
	{
		return false;
	}

	GString _sFilter(sFilter);
	// 2.预处理字符串（替换无法识别的字符+去除两边无效的括号）
	if (!ParseFilter_PreParseFilter(_sFilter)
		|| !ParseFilter_TrimBracket(_sFilter))
	{
		return false;
	}

	// 3.分解字符串
	gsize nUnionCount = m_tUnionSymbols.Size();
	gbool bHasBracket = false;
	if (_sFilter.Find('(') != -1 && _sFilter.Find(')') != -1)
	{
		bHasBracket = true;
	}

	for (gsize i = 0; i < nUnionCount; i++)
	{
		GString sUnion = m_tUnionSymbols.GetAt(i);
		GStringList tFilterList;
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

		gsize nLenOfUnion = tFilterList.Size();
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
			for (gsize i = 0; i < nLenOfUnion; i++)
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

gbool CsFilter_Ex::CsFilterParse::ParseFilter_PreParseFilter(GString &sFilter)
{
	if (sFilter.IsEmpty())
	{
		return false;
	}
	sFilter = sFilter.ToUpper().Replace("'", "").Replace(";", " AND ");
	return !sFilter.IsEmpty();
}

gbool CsFilter_Ex::CsFilterParse::ParseFilter_ParseUnionType(const GString &sUnion, CS_UNION_TYPE &emUnionType)
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

gbool CsFilter_Ex::CsFilterParse::ParseFilter_IsBracketLegal(const GString &sFilter)
{
	gsize length = sFilter.Size();
	GListStack<gchar> stack;

	for (gsize i = 0; i < length; i++)
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

gbool CsFilter_Ex::CsFilterParse::ParseFilter_TrimBracket(GString &sFilter)
{
	if (sFilter[0] == '(' && sFilter[sFilter.Size() - 1] == ')')
	{
		// 移除括号
		sFilter = sFilter.SubString(1, sFilter.Size() - 2);
		return ParseFilter_TrimBracket(sFilter);
	}
	else
	{
		return true;
	}
}

gbool CsFilter_Ex::CsFilterParse::ParseFilter_BreakUpBracketOnOneLevel(const GString &sFilter, const GString &sUnion, GStringList &tFilterList)
{
	gsize length = sFilter.Size();
	GListStack<gchar> stack;
	gsize cursor = 0;
	for (gsize i = 0; i < length; i++)
	{
		gint id = sFilter.Find(sUnion, i);
		if (id < 0)
		{
			tFilterList.Add(sFilter.SubString(i, length - i));
			return true;
		}
		if (stack.IsEmpty())
		{
			tFilterList.Add(sFilter.SubString(cursor, i - cursor));
			i += sUnion.Size();
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

gbool CsFilter_Ex::CsFilterParse::GetUnionString(CS_UNION_TYPE emUnionType, GString &sUnion)
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

gbool CsFilter_Ex::CsFilterParse::ParseFilter_ParseCompareType(const GString &sCompare, CS_COMPARE_TYPE &emCompareType)
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

gbool CsFilter_Ex::CsFilterParse::GetCompareString(CS_COMPARE_TYPE emCompareType, GString &sCompare)
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
	return false;
}

//////////////////////////////////////////////////////////////////////////
// CsFilter_Private
//////////////////////////////////////////////////////////////////////////
CsFilter_Ex::CsFilter_Ex(const GString &sFilter)
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

gbool CsFilter_Ex::SetFilter(const GString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	gbool bRet = m_tFilterData.SetFilter(sFilter);
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

gbool CsFilter_Ex::IsValid() const
{
	return m_tFilterData.IsValid();
}

GString CsFilter_Ex::ToString() const
{
	return m_tFilterData.ToString();
}

gbool CsFilter_Ex::Initialize()
{
	if (!m_bInitializeUnionSymbols)
	{
		m_tUnionSymbols = GString(" AND ; OR ").Split(";");
		m_bInitializeUnionSymbols = true;
	}
	if (!m_bInitializeCompareSymbols)
	{
		m_tCompareSymbols = GString(" LIKE ; != ; >= ; <= ; = ; > ; < ").Split(";");
		m_bInitializeCompareSymbols = true;
	}
	return true;
}

gbool CsFilter_Ex::Release()
{
	return m_tFilterData.Release();
}