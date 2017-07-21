#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "GCore/gobject.h"

class GFilter;

// value是一个无符号整型值，表示行号
// value不可以重复
class GTableDataIndex
{
public:
	enum DATA_INDEX_TYPE
	{
		INDEX_TYPE_ORDER,		// 有序索引，会对key值进行排序，可以支持>、>=、<、<=等操作
		INDEX_TYPE_UNORDER,		// 无序索引，速度较快，仅支持=操作
	};

public:
	virtual ~GTableDataIndex();

	gbool Valid() const;

	// 搜索
	gbool Search(const GFilter &sFilter) const;

	gbool Add();
	gbool Remove();

	// 重构索引
	gbool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_