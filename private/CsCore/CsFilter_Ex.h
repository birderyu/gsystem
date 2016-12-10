#ifndef _CORE_FILTER_EX_H_
#define _CORE_FILTER_EX_H_

#include "CsDynamicArray.h"
#include "CsVariant.h"

class CsFilter_Ex
{
protected:
	// 联合类型
	enum CS_UNION_TYPE
	{
		UNION_TYPE_ERROR = -1,
		UNION_TYPE_SINGLE = 0,	// 无联合关系（只有一个条件）
		UNION_TYPE_AND,			// 逻辑与
		UNION_TYPE_OR,			// 逻辑或
	};

	/// 比较类型
	enum CS_COMPARE_TYPE
	{
		COMPARE_TYPE_ERROR = -1,		// 非法的比较类型
		COMPARE_TYPE_EQUAL,			// 等于
		COMPARE_TYPE_LESS,			// 小于
		COMPARE_TYPE_LESS_EQUAL,	// 小于等于
		COMPARE_TYPE_GREATER,		// 大于
		COMPARE_TYPE_GREATER_EQUAL,	// 大于等于
		COMPARE_TYPE_NOTEQUAL,		// 不等于
		COMPARE_TYPE_LIKE,			// 模糊比较
	};

private:
	class CsFilterCell
	{
	public:
		CsFilterCell();
		CsFilterCell(const CsFilterCell &tCell);
		virtual ~CsFilterCell();
		cs_bool SetFilter(const CsString &sFilter);
		cs_bool IsValid() const;
		cs_bool Release();
		CsString ToString() const;
		CsFilterCell &operator=(const CsFilterCell &tCell);

	private:		
		CsString m_sFieldName;
		CsVariant m_tFieldValue;
		CS_COMPARE_TYPE m_emCompareType;
	};

	struct CsFilterData
	{
		CsFilterData();
		CsFilterData(const CsFilterData &tData);
		cs_bool SetFilter(const CsString &sFilter);
		cs_bool IsValid() const;
		CsString ToString() const;
		cs_bool Release();
		CsFilterData &operator=(const CsFilterData &tData);

	private:
		CsDynamicArray<CsFilterData> m_tChildren;
		CsFilterCell m_tCell;
		CS_UNION_TYPE m_emUnionType;
	};

	struct CsFilterParse
	{
		// 解析过滤器字符串
		static cs_bool ParseFilter(const CsString &sFilter, CS_UNION_TYPE &emUnionType, 
			CsDynamicArray<CsFilterData> &tData, CsFilterCell &tCell);

		// 解析过滤器字符串：预处理字符串，如"OID = 1; NAME = 'ABC'"，改为"OID = 1 AND NAME = ABC"
		static cs_bool ParseFilter_PreParseFilter(CsString &sFilter);
		// 解析过滤器字符串：根据联合的符号，获取联合的枚举值
		static cs_bool ParseFilter_ParseUnionType(const CsString &sUnion, CS_UNION_TYPE &emUnionType);
		// 解析过滤器字符串：判断括号是否合法
		static cs_bool ParseFilter_IsBracketLegal(const CsString &sFilter);
		// 解析过滤器字符串：移除起始无效的括号，如"(OID = 1 AND TYPE = 2)"，变为"OID = 1 AND TYPE = 2"
		static cs_bool ParseFilter_TrimBracket(CsString &sFilter);
		// 解析过滤器字符串：指定联合符号去分解括号
		// 只分解第一级括号
		// 如"(OID = 1 OR TYPE = 2) AND (NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		// 变为"(OID = 1 OR TYPE = 2)" 和 "(NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		static cs_bool ParseFilter_BreakUpBracketOnOneLevel(const CsString &sFilter, const CsString &sUnion, CsStringList &tFilterList);
		// 
		static cs_bool ParseFilter_ParseCompareType(const CsString &sCompare, CS_COMPARE_TYPE &emCompareType);
		static cs_bool GetCompareString(CS_COMPARE_TYPE emCompareType, CsString &sCompare);
		static cs_bool GetUnionString(CS_UNION_TYPE emUnionType, CsString &sUnion);
	};

public:
	CsFilter_Ex(const CsString &sFilter);
	CsFilter_Ex(const CsFilter_Ex &tFilter);
	virtual ~CsFilter_Ex();
	virtual cs_bool SetFilter(const CsString &sFilter);
	virtual CsFilter_Ex &operator=(const CsFilter_Ex &tFilter);

	cs_bool IsValid() const;
	CsString ToString() const;

private:
	cs_bool Initialize();
	cs_bool Release();
	CsFilterData m_tFilterData;

private:
	static CsStringList m_tUnionSymbols;
	static cs_bool m_bInitializeUnionSymbols;

	static CsStringList m_tCompareSymbols;
	static cs_bool m_bInitializeCompareSymbols;
};

#endif // _CORE_FILTER_EX_H_