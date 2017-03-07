#ifndef _CORE_FILTER_EX_H_
#define _CORE_FILTER_EX_H_

#include "GCore/gdynamicarray.h"
#include "GCore/gvariety.h"
#include "GCore/gstring.h"

class GFilter_Ex
{
public:
	struct GFilterData;

protected:
	// 联合类型
	enum G_UNION_TYPE
	{
		UNION_TYPE_ERROR = -1,
		UNION_TYPE_SINGLE = 0,	// 无联合关系（只有一个条件）
		UNION_TYPE_AND,			// 逻辑与
		UNION_TYPE_OR,			// 逻辑或
	};

	/// 比较类型
	enum G_COMPARE_TYPE
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
	class GFilterCell
	{
	public:
		GFilterCell();
		GFilterCell(const GFilterCell &tCell);
		virtual ~GFilterCell();
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		gbool Release();
		GString ToString() const;
		GFilterCell &operator=(const GFilterCell &tCell);

	private:		
		GString m_sFieldName;
		GVariety m_tFieldValue;
		G_COMPARE_TYPE m_emCompareType;
	};

	struct GFilterData
	{
		GFilterData();
		GFilterData(const GFilterData &tData);
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		GString ToString() const;
		gbool Release();
		GFilterData &operator=(const GFilterData &tData);

	private:
		GDynamicArray<GFilterData> m_tChildren;
		GFilterCell m_tCell;
		G_UNION_TYPE m_emUnionType;
	};

	struct GFilterParse
	{
		// 解析过滤器字符串
		static gbool ParseFilter(const GString &sFilter, G_UNION_TYPE &emUnionType, 
			GDynamicArray<GFilterData> &tData, GFilterCell &tCell);

		// 解析过滤器字符串：预处理字符串，如"OID = 1; NAME = 'ABC'"，改为"OID = 1 AND NAME = ABC"
		static gbool ParseFilter_PreParseFilter(GString &sFilter);
		// 解析过滤器字符串：根据联合的符号，获取联合的枚举值
		static gbool ParseFilter_ParseUnionType(const GString &sUnion, G_UNION_TYPE &emUnionType);
		// 解析过滤器字符串：判断括号是否合法
		static gbool ParseFilter_IsBracketLegal(const GString &sFilter);
		// 解析过滤器字符串：移除起始无效的括号，如"(OID = 1 AND TYPE = 2)"，变为"OID = 1 AND TYPE = 2"
		static gbool ParseFilter_TrimBracket(GString &sFilter);
		// 解析过滤器字符串：指定联合符号去分解括号
		// 只分解第一级括号
		// 如"(OID = 1 OR TYPE = 2) AND (NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		// 变为"(OID = 1 OR TYPE = 2)" 和 "(NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		static gbool ParseFilter_BreakUpBracketOnOneLevel(const GString &sFilter, const GString &sUnion, GStringList &tFilterList);
		// 
		static gbool ParseFilter_ParseCompareType(const GString &sCompare, G_COMPARE_TYPE &emCompareType);
		static gbool GetCompareString(G_COMPARE_TYPE emCompareType, GString &sCompare);
		static gbool GetUnionString(G_UNION_TYPE emUnionType, GString &sUnion);
	};

public:
	GFilter_Ex(const GString &sFilter);
	GFilter_Ex(const GFilter_Ex &tFilter);
	virtual ~GFilter_Ex();
	virtual gbool SetFilter(const GString &sFilter);
	virtual GFilter_Ex &operator=(const GFilter_Ex &tFilter);

	gbool IsValid() const;
	GString ToString() const;

private:
	gbool Initialize();
	gbool Release();
	GFilterData m_tFilterData;

private:
	static GStringList m_tUnionSymbols;
	static gbool m_bInitializeUnionSymbols;

	static GStringList m_tCompareSymbols;
	static gbool m_bInitializeCompareSymbols;
};

#endif // _CORE_FILTER_EX_H_