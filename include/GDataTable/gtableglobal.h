#ifndef _CORE_TABLE_GLOBAL_H_
#define _CORE_TABLE_GLOBAL_H_

#include "GCore/gobject.h"
#include "GCore/gvariety.h"
#include "GCore/gdynamicarray.h"
#include "gtableaction.h"

class GDataTable;
class GDataView;
template<typename TableT> class GTableCell;
template<typename TableT> class GTableField;
template<typename TableT> class GTableFields;
template<typename TableT> class GTableRow;
template<typename TableT> class GTableRows;
template<typename TableT> class GTableColumn;
template<typename TableT> class GTableColumns;

// 表类型
enum G_TABLE_TYPE
{
	TABLE_TYPE_SERIAL,		// 连续内存表（默认）
	TABLE_TYPE_SIMPLE,		// 简单内存表
	TABLE_TYPE_VARIANT,		// 变体类型表
	TABLE_TYPE_OBJECT,		// 对象表
};

// 表字段类型
enum G_TABLE_FIELD_TYPE
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
	TABLE_FIELD_TYPE_LONGDOUBLE,
	TABLE_FIELD_TYPE_DATETIME,	// 日期类
	TABLE_FIELD_TYPE_BYTES,		// 字节数组
	TABLE_FIELD_TYPE_STRING,	// 字符串
	TABLE_FIELD_TYPE_WSTRING,	// 宽字符串
	TABLE_FIELD_TYPE_GEOMETRY,	// 几何字段
	TABLE_FIELD_TYPE_OBJECT,	// Object对象
};

// 表索引类型
enum G_TABLE_INDEX_TYPE
{
	TABLE_INDEX_TYPE_NULL,		// 无索引
	TABLE_INDEX_TYPE_UNORDER,	// 无序索引
	TABLE_INDEX_TYPE_ORDER,		// 有序索引
	TABLE_INDEX_TYPE_SPATIAL,	// 空间索引
};

#endif // _CORE_TABLE_GLOBAL_H_