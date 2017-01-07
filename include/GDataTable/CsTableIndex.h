#ifndef _CORE_INDEX_H_
#define _CORE_INDEX_H_

#include "gobject.h"

class CsFilter;

template<typename TableT>
class GAPI CsTableIndex
	: public GObject
{
public:
	enum TYPE
	{
		INDEX_TYPE_NULL = -1,
		INDEX_TYPE_DATA,		// 属性数据索引
		INDEX_TYPE_SPATIAL,		// 空间数据索引
	};

	// 结果集
	class CsCursor
	{
		friend class CsTableIndex;
	public:
		CsCursor();
		gsize Size() const;

	public:
		CsCursor &Next();

	private:
		TableT *m_tTable;
		gsize m_nCursor;
		// 行号的集合
	};

public:
	virtual gbool Valid() const = 0;
	virtual gvoid Rebulid() = 0;
	virtual gsmall IndexType() = 0;
	virtual gbool Search(const CsFilter &, CsCursor &) = 0;
	virtual gbool Sync();

private:
	TableT &m_tTable;
};

#endif // _CORE_INDEX_H_