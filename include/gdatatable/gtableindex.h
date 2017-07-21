#ifndef _CORE_INDEX_H_
#define _CORE_INDEX_H_

#include "GCore/gobject.h"

class GFilter;

template<typename TableT>
class GAPI GTableIndex
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
	class GCursor
	{
		friend class GTableIndex;
	public:
		GCursor();
		gsize Size() const;

	public:
		GCursor &Next();

	private:
		TableT *m_tTable;
		gsize m_nCursor;
		// 行号的集合
	};

public:
	virtual gbool Valid() const = 0;
	virtual gvoid Rebulid() = 0;
	virtual gsmall IndexType() = 0;
	virtual gbool Search(const GFilter &, GCursor &) = 0;
	virtual gbool Sync();

private:
	TableT &m_tTable;
};

#endif // _CORE_INDEX_H_