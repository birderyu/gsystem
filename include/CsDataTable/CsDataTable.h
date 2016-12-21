/// 数据表

#ifndef _DATA_TABLE_TABLE_H_
#define _DATA_TABLE_TABLE_H_

#include "CsTableGlobal.h"

class CsVirtualTable;

class CS_API CsDataTable
{
public:
	CsDataTable();
	CsDataTable(CsVirtualTable *);
	CsDataTable(const CsDataTable &);
	~CsDataTable();

public:
	// 面向对象操作
	CsTableFields<CsDataTable> Fields() const;
	CsTableRows<CsDataTable> Rows() const;
	CsTableColumns<CsDataTable> Columns() const;

	CsTableField<CsDataTable> FieldAt(cs_size_t) const;
	CsTableRow<CsDataTable> RowAt(cs_size_t) const;
	CsTableColumn<CsDataTable> ColumnAt(cs_size_t) const;

	CsTableRow<CsDataTable> operator[](cs_size_t) const;

public:
	// 快速操作
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_bool &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_char &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_schar &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_uchar &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_wchar &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_short &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ushort &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_int &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_uint &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_long &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ulong &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_longlong &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ulonglong &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_float &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_double &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, cs_decimal &) const;
	cs_bool GetValue(cs_size_t row, cs_size_t col, CsString &) const;
	CsVariant GetValue(cs_size_t row, cs_size_t col) const;

	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_bool);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_char);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_schar);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_uchar);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_wchar);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_short);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ushort);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_int);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_uint);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_long);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ulong);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_longlong);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ulonglong);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_float);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_double);
	cs_bool SetValue(cs_size_t row, cs_size_t col, cs_decimal);
	cs_bool SetValue(cs_size_t row, cs_size_t col, const CsString &);
	cs_bool SetValue(cs_size_t row, cs_size_t col, const CsVariant &);

public:
	enum { CLASS_CODE = CLASS_CODE_TABLE, };

private:
	CsVirtualTable *m_pVirtualTable;
};

#endif // _CSCORE_CSDATATABLE_H_
