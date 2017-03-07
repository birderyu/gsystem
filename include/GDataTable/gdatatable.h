/// 数据表

#ifndef _DATA_TABLE_TABLE_H_
#define _DATA_TABLE_TABLE_H_

#include "gtableglobal.h"

class GVirtualTable;
class GVirtualTableCursor;

class GAPI GDataTable
{
public:
	class Cursor;
	class ConstCursor;
	class Filter;

public:
	/// 构造一张名称为tablename的空表
	GDataTable(const GString &tablename);

	/// 拷贝构造一张表
	GDataTable(const GDataTable &table);

	/// 移动构造一张表
	GDataTable(GDataTable &&table);

	/// 析构一张表
	~GDataTable();

	/// 拷贝赋值一张表
	GDataTable &operator=(const GDataTable &table);

	/// 移动赋值一张表
	GDataTable &operator=(GDataTable &&table);

	/// 拷贝一张表
	GDataTable Clone() cosnt;

public:
	//******************************************************//
	//************************只读操作************************//
	//******************************************************//

	/// 获取字段的集合
	GTableFields<GDataTable> Fields() const;

	/// 获取列的集合
	GTableColumns<GDataTable> Columns() const;

	/// 获取行的集合
	GTableRows<GDataTable> Rows() const;

	/// 根据字段ID获取某一字段
	GTableField<GDataTable> FieldAt(gsize field) const;

	/// 根据列ID获取某一列
	GTableColumn<GDataTable> ColumnAt(gsize column) const;

	/// 根据行ID获取某一行
	GTableRow<GDataTable> RowAt(gsize row) const;

	/// 根据行ID获取某一行
	GTableRow<GDataTable> operator[](gsize row) const;

public:
	// 构建索引
	gbool IndexOn(const GString &fieldname, G_TABLE_INDEX_TYPE type);

public:
	// 获取一个只读光标
	ConstCursor GetIterator() const;
	ConstCursor GetConstIterator() const;

	template<typename T> T GetValue(gsize row, gsize col);
	template<typename T> gvoid SetValue(gsize row, gsize col, const T &val);
	template<typename T> gvoid SetValue(gsize row, gsize col, T &&val);

public:
	// 数据检索
	Cursor Search(const Filter &filter);
	ConstCursor Search(const Filter &filter) const;
	ConstCursor ConstSearch(const Filter &filter) const;

private:
	gbool GetValue(gsize row, gsize col, gbool &) const;
	gbool GetValue(gsize row, gsize col, gchar &) const;
	gbool GetValue(gsize row, gsize col, gschar &) const;
	gbool GetValue(gsize row, gsize col, guchar &) const;
	gbool GetValue(gsize row, gsize col, gwchar &) const;
	gbool GetValue(gsize row, gsize col, gshort &) const;
	gbool GetValue(gsize row, gsize col, gushort &) const;
	gbool GetValue(gsize row, gsize col, gint &) const;
	gbool GetValue(gsize row, gsize col, guint &) const;
	gbool GetValue(gsize row, gsize col, glong &) const;
	gbool GetValue(gsize row, gsize col, gulong &) const;
	gbool GetValue(gsize row, gsize col, glonglong &) const;
	gbool GetValue(gsize row, gsize col, gulonglong &) const;
	gbool GetValue(gsize row, gsize col, gfloat &) const;
	gbool GetValue(gsize row, gsize col, gdouble &) const;
	gbool GetValue(gsize row, gsize col, gdecimal &) const;
	gbool GetValue(gsize row, gsize col, GString &) const;
	GVariety GetValue(gsize row, gsize col) const;

	gbool SetValue(gsize row, gsize col, gbool);
	gbool SetValue(gsize row, gsize col, gchar);
	gbool SetValue(gsize row, gsize col, gschar);
	gbool SetValue(gsize row, gsize col, guchar);
	gbool SetValue(gsize row, gsize col, gwchar);
	gbool SetValue(gsize row, gsize col, gshort);
	gbool SetValue(gsize row, gsize col, gushort);
	gbool SetValue(gsize row, gsize col, gint);
	gbool SetValue(gsize row, gsize col, guint);
	gbool SetValue(gsize row, gsize col, glong);
	gbool SetValue(gsize row, gsize col, gulong);
	gbool SetValue(gsize row, gsize col, glonglong);
	gbool SetValue(gsize row, gsize col, gulonglong);
	gbool SetValue(gsize row, gsize col, gfloat);
	gbool SetValue(gsize row, gsize col, gdouble);
	gbool SetValue(gsize row, gsize col, gdecimal);
	gbool SetValue(gsize row, gsize col, const GString &);
	gbool SetValue(gsize row, gsize col, GString &&);
	gbool SetValue(gsize row, gsize col, const GVariety &);
	gbool SetValue(gsize row, gsize col, GVariety &&);

public:
	enum { CLASS_CODE = CLASS_CODE_TABLE, };

private:
	GDataTable(GVirtualTable *);
	GVirtualTable *m_pVirtualTable;
};

#endif // _CSCORE_CSDATATABLE_H_
