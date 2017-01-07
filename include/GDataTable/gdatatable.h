/// 数据表

#ifndef _DATA_TABLE_TABLE_H_
#define _DATA_TABLE_TABLE_H_

#include "gtableglobal.h"

class GVirtualTable;

class GAPI GDataTable
{
public:
	GDataTable();
	GDataTable(GVirtualTable *);
	GDataTable(const GDataTable &);
	~GDataTable();

public:
	// 面向对象操作
	GTableFields<GDataTable> Fields() const;
	GTableRows<GDataTable> Rows() const;
	GTableColumns<GDataTable> Columns() const;

	GTableField<GDataTable> FieldAt(gsize) const;
	GTableRow<GDataTable> RowAt(gsize) const;
	GTableColumn<GDataTable> ColumnAt(gsize) const;

	GTableRow<GDataTable> operator[](gsize) const;

public:
	// 快速操作
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
	GVariant GetValue(gsize row, gsize col) const;

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
	gbool SetValue(gsize row, gsize col, const GVariant &);

public:
	enum { CLASS_CODE = CLASS_CODE_TABLE, };

private:
	GVirtualTable *m_pVirtualTable;
};

#endif // _CSCORE_CSDATATABLE_H_
