#ifndef _CORE_TABLE_GLOBAL_H_
#define _CORE_TABLE_GLOBAL_H_

#include "CsObject.h"
#include "CsVariant.h"

class CsIntArray;

class CsDataTable;
class CsDataView;
template<typename TableT> class CsTableCell;
template<typename TableT> class CsTableField;
template<typename TableT> class CsTableFields;
template<typename TableT> class CsTableRow;
template<typename TableT> class CsTableRows;
template<typename TableT> class CsTableColumn;
template<typename TableT> class CsTableColumns;

// 表类型
enum CS_TABLE_TYPE
{
	TABLE_TYPE_SERIAL,		// 连续内存表（默认）
	TABLE_TYPE_SIMPLE,		// 简单内存表
	TABLE_TYPE_VARIANT,		// 变体类型表
	TABLE_TYPE_OBJECT,		// 对象表
};

// 表字段类型
enum CS_TABLE_FIELD_TYPE
{
	TABLE_FIELD_TYPE_ILLEGAL = -1,
	TABLE_FIELD_TYPE_BOOL,
	TABLE_FIELD_TYPE_CHAR,
	TABLE_FIELD_TYPE_SCHAR,
	TABLE_FIELD_TYPE_UCHAR,
	TABLE_FIELD_TYPE_WCHAR,
	TABLE_FIELD_TYPE_SHORT,
	TABLE_FIELD_TYPE_USHORT,
	TABLE_FIELD_TYPE_INT,
	TABLE_FIELD_TYPE_UINT,
	TABLE_FIELD_TYPE_LONG,
	TABLE_FIELD_TYPE_ULONG,
	TABLE_FIELD_TYPE_LONGLONG,
	TABLE_FIELD_TYPE_ULONGLONG,
	TABLE_FIELD_TYPE_FLOAT,
	TABLE_FIELD_TYPE_DOUBLE,
	TABLE_FIELD_TYPE_DECIMAL,
	TABLE_FIELD_TYPE_STRING,	// 字符串
	TABLE_FIELD_TYPE_GEOMETRY,	// 几何字段
};

// 表索引类型
enum CS_TABLE_INDEX_TYPE
{
	TABLE_INDEX_TYPE_NULL,		// 无索引
	TABLE_INDEX_TYPE_UNORDER,	// 无序索引
	TABLE_INDEX_TYPE_ORDER,		// 有序索引
	TABLE_INDEX_TYPE_SPATIAL,	// 空间索引
};

#endif // _CORE_TABLE_GLOBAL_H_