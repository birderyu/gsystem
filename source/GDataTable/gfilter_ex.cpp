#include "gfilter_ex.h"
#include "GCore/gstring.h"
#include "GCore/gstringlist.h"
#include "GCore/gliststack.h"

// 支持的联合类型，按照优先级排列
GStringList GFilter_Ex::m_tUnionSymbols;
gbool GFilter_Ex::m_bInitializeUnionSymbols = false;

// 支持的比较类型，按优先级排列
GStringList GFilter_Ex::m_tCompareSymbols;
gbool GFilter_Ex::m_bInitializeCompareSymbols = false;

//////////////////////////////////////////////////////////////////////////
// GFilterCell
//////////////////////////////////////////////////////////////////////////
GFilter_Ex::GFilterCell::GFilterCell()
:m_emCompareType(COMPARE_TYPE_ERROR)
{
	
}

GFilter_Ex::GFilterCell::GFilterCell(const GFilterCell &tCell)
: m_emCompareType(tCell.m_emCompareType)
, m_sFieldName(tCell.m_sFieldName)
, m_tFieldValue(tCell.m_tFieldValue)
{

}

GFilter_Ex::GFilterCell::~GFilterCell()
{

}

gbool GFilter_Ex::GFilterCell::SetFilter(const GString &sFilter)
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
		if (!GFilterParse::ParseFilter_ParseCompareType(m_tCompareSymbols.GetAt(i), m_emCompareType))
		{
			return false;
		}
		m_tFieldValue.SetValue(tFilterList.GetAt(i));
		return true;
	}
	return false;
}

gbool GFilter_Ex::GFilterCell::IsValid() const
{
	return m_emCompareType != COMPARE_TYPE_ERROR
		&& !m_sFieldName.IsEmpty()
		&& m_tFieldValue.Valid();
}

gbool GFilter_Ex::GFilterCell::Release()
{
	m_emCompareType = COMPARE_TYPE_ERROR;
	return true;
}

GString GFilter_Ex::GFilterCell::ToString() const
{
	if (!IsValid())
	{
		return "";
	}
	GString sCompare;
	if (!GFilterParse::GetCompareString(m_emCompareType, sCompare))
	{
		return "";
	}
	return m_sFieldName + sCompare + m_tFieldValue.ToString();
}

GFilter_Ex::GFilterCell &GFilter_Ex::GFilterCell::operator=(const GFilterCell &tCell)
{
	m_sFieldName = tCell.m_sFieldName;
	m_tFieldValue = tCell.m_tFieldValue;
	m_emCompareType = tCell.m_emCompareType;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// GFilterData
//////////////////////////////////////////////////////////////////////////
GFilter_Ex::GFilterData::GFilterData()
: m_emUnionType(UNION_TYPE_ERROR)
{

}

GFilter_Ex::GFilterData::GFilterData(const GFilterData &tData)
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

gbool GFilter_Ex::GFilterData::SetFilter(const GString &sFilter)
{
	if (IsValid())
	{
		Release();
	}
	return GFilterParse::ParseFilter(sFilter, m_emUnionType, m_tChildren, m_tCell);
}

gbool GFilter_Ex::GFilterData::IsValid() const
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

GString GFilter_Ex::GFilterData::ToString() const
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
				if (GFilterParse::GetUnionString(m_emUnionType, sUnion))
				{
					sResult += sUnion;
				}
			}
		}
		return sResult;
	}
	return "";
}

gbool GFilter_Ex::GFilterData::Release()
{
	m_emUnionType = UNION_TYPE_ERROR;
	m_tChildren.Dispose();
	m_tCell.Release();
	return true;
}

GFilter_Ex::GFilterData &GFilter_Ex::GFilterData::operator = (const GFilterData &tData)
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
// GFilterParse
//////////////////////////////////////////////////////////////////////////
gbool GFilter_Ex::GFilterParse::ParseFilter(const GString &sFilter, G_UNION_TYPE &emUnionType, 
	GDynamicArray<GFilterData> &tData, GFilterCell &tCell)
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

gbool GFilter_Ex::GFilterParse::ParseFilter_PreParseFilter(GString &sFilter)
{
	if (sFilter.IsEmpty())
	{
		return false;
	}
	sFilter = sFilter.ToUpper().Replace("'", "").Replace(";", " AND ");
	return !sFilter.IsEmpty();
}

gbool GFilter_Ex::GFilterParse::ParseFilter_ParseUnionType(const GString &sUnion, G_UNION_TYPE &emUnionType)
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

gbool GFilter_Ex::GFilterParse::ParseFilter_IsBracketLegal(const GString &sFilter)
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

gbool GFilter_Ex::GFilterParse::ParseFilter_TrimBracket(GString &sFilter)
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

gbool GFilter_Ex::GFilterParse::ParseFilter_BreakUpBracketOnOneLevel(const GString &sFilter, const GString &sUnion, GStringList &tFilterList)
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

gbool GFilter_Ex::GFilterParse::GetUnionString(G_UNION_TYPE emUnionType, GString &sUnion)
{
	switch (emUnionType)
	{
	case GFilter_Ex::UNION_TYPE_ERROR:
		return false;
		break;
	case GFilter_Ex::UNION_TYPE_SINGLE:
		return false;
		break;
	case GFilter_Ex::UNION_TYPE_AND:
		sUnion = " AND ";
		return true;
		break;
	case GFilter_Ex::UNION_TYPE_OR:
		sUnion = " OR ";
		return true;
		break;
	default:
		break;
	}
	return false;
}

gbool GFilter_Ex::GFilterParse::ParseFilter_ParseCompareType(const GString &sCompare, G_COMPARE_TYPE &emCompareType)
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

gbool GFilter_Ex::GFilterParse::GetCompareString(G_COMPARE_TYPE emCompareType, GString &sCompare)
{
	switch (emCompareType)
	{
	case GFilter_Ex::COMPARE_TYPE_ERROR:
		return false;
		break;
	case GFilter_Ex::COMPARE_TYPE_EQUAL:
		sCompare = " = ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_LESS:
		sCompare = " < ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_LESS_EQUAL:
		sCompare = " <= ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_GREATER:
		sCompare = " > ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_GREATER_EQUAL:
		sCompare = " >= ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_NOTEQUAL:
		sCompare = " != ";
		return true;
		break;
	case GFilter_Ex::COMPARE_TYPE_LIKE:
		sCompare = " LIKE ";
		return true;
		break;
	default:
		break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// GFilter_Ex
//////////////////////////////////////////////////////////////////////////
GFilter_Ex::GFilter_Ex(const GString &sFilter)
{
	Initialize();
	if (!sFilter.IsEmpty())
	{
		SetFilter(sFilter);
	}
}

GFilter_Ex::GFilter_Ex(const GFilter_Ex &tFilter)
: m_tFilterData(tFilter.m_tFilterData)
{
	Initialize();
}

GFilter_Ex::~GFilter_Ex()
{
	Release();
}

gbool GFilter_Ex::SetFilter(const GString &sFilter)
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

GFilter_Ex &GFilter_Ex::operator = (const GFilter_Ex &tFilter)
{
	m_tFilterData = tFilter.m_tFilterData;
	return *this;
}

gbool GFilter_Ex::IsValid() const
{
	return m_tFilterData.IsValid();
}

GString GFilter_Ex::ToString() const
{
	return m_tFilterData.ToString();
}

gbool GFilter_Ex::Initialize()
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

gbool GFilter_Ex::Release()
{
	return m_tFilterData.Release();
}