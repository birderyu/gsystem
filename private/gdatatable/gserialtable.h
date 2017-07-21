// 连续内存表
// 使用一整块连续的内存存储表结构

#ifndef _CORE_SERIAL_TABLE_H_
#define _CORE_SERIAL_TABLE_H_

#include "gvirtualtable.h"
#include "GCore/gvector.h"

class GSerialTable 
	: public GVirtualTable
{
public:
	GSerialTable();

private:
	GVector<gbyte> m_tBlock;
	GString m_sTableName;
};

#endif // _CORE_SERIAL_TABLE_H_