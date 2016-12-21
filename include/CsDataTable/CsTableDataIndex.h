#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "CsObject.h"

class CsFilter;

// value是一个无符号整型值，表示行号
// value不可以重复
class CsTableDataIndex
{
public:
	enum DATA_INDEX_TYPE
	{
		INDEX_TYPE_ORDER,		// 有序索引，会对key值进行排序，可以支持>、>=、<、<=等操作
		INDEX_TYPE_UNORDER,		// 无序索引，速度较快，仅支持=操作
	};

public:
	virtual ~CsTableDataIndex();

	cs_bool Valid() const;

	// 搜索
	cs_bool Search(const CsFilter &sFilter) const;

	cs_bool Add();
	cs_bool Remove();

	// 重构索引
	cs_bool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_