// 表视图
// 表视图并非一张实际存在的表，而是依附于某一张表的部分数据

#ifndef _CORE_TABLE_VIEW_H_
#define _CORE_TABLE_VIEW_H_

#include "CsDataTable.h"

class CS_API CsTableView :public CsDataTable
{
public:
	CsTableView(CsDataTable &, CsIntArray *rows, CsIntArray *columns);

private:
	CsVirtualTable *m_pVirtualTable;
	CsIntArray *m_pRows;
	CsIntArray *m_pColumns;
};

#endif // _CORE_TABLE_VIEW_H_