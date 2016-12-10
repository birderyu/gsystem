#ifndef _CORE_TABLE_CELL_H_
#define _CORE_TABLE_CELL_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableCell
{
public:
	CsTableCell(TableT &, cs_size_t row, cs_size_t column);
	CsTableCell(const CsTableCell<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	CsTableField<TableT> Field() const;
	CsTableRow<TableT> Row() const;
	CsTableColumn<TableT> Column() const;

	cs_size_t FieldID() const;
	cs_size_t RowID() const;
	cs_size_t ColumnID() const;

	cs_bool GetValue(cs_bool &) const;
	cs_bool GetValue(cs_char &) const;
	cs_bool GetValue(cs_schar &) const;
	cs_bool GetValue(cs_uchar &) const;
	cs_bool GetValue(cs_wchar &) const;
	cs_bool GetValue(cs_short &) const;
	cs_bool GetValue(cs_ushort &) const;
	cs_bool GetValue(cs_int &) const;
	cs_bool GetValue(cs_uint &) const;
	cs_bool GetValue(cs_long &) const;
	cs_bool GetValue(cs_ulong &) const;
	cs_bool GetValue(cs_longlong &) const;
	cs_bool GetValue(cs_ulonglong &) const;
	cs_bool GetValue(cs_float &) const;
	cs_bool GetValue(cs_double &) const;
	cs_bool GetValue(cs_decimal &) const;
	cs_bool GetValue(CsString &) const;
	CsVariant GetValue() const;

	cs_bool SetValue(cs_bool);
	cs_bool SetValue(cs_char);
	cs_bool SetValue(cs_schar);
	cs_bool SetValue(cs_uchar);
	cs_bool SetValue(cs_wchar);
	cs_bool SetValue(cs_short);
	cs_bool SetValue(cs_ushort);
	cs_bool SetValue(cs_int);
	cs_bool SetValue(cs_uint);
	cs_bool SetValue(cs_long);
	cs_bool SetValue(cs_ulong);
	cs_bool SetValue(cs_longlong);
	cs_bool SetValue(cs_ulonglong);
	cs_bool SetValue(cs_float);
	cs_bool SetValue(cs_double);
	cs_bool SetValue(cs_decimal);
	cs_bool SetValue(const CsString &);
	cs_bool SetValue(const CsVariant &);

	cs_bool operator=(cs_bool);
	cs_bool operator=(cs_char);
	cs_bool operator=(cs_schar);
	cs_bool operator=(cs_uchar);
	cs_bool operator=(cs_wchar);
	cs_bool operator=(cs_short);
	cs_bool operator=(cs_ushort);
	cs_bool operator=(cs_int);
	cs_bool operator=(cs_uint);
	cs_bool operator=(cs_long);
	cs_bool operator=(cs_ulong);
	cs_bool operator=(cs_longlong);
	cs_bool operator=(cs_ulonglong);
	cs_bool operator=(cs_float);
	cs_bool operator=(cs_double);
	cs_bool operator=(cs_decimal);
	cs_bool operator=(const CsString &);
	cs_bool operator=(const CsVariant &);

private:
	TableT &m_tTable;
	cs_size_t m_nRowID;
	cs_size_t m_nColumnID;
};

template<typename TableT>
CsTableCell<TableT>::CsTableCell(TableT &table, cs_size_t row, cs_size_t column)
: m_tTable(table), m_nRowID(row), m_nColumnID(column)
{

}

template<typename TableT>
CsTableCell<TableT>::CsTableCell(const CsTableCell<TableT> &cell)
: m_tTable(cell.m_tTable), m_nRowID(cell.m_nRowID), m_nColumnID(cell.m_nColumnID)
{

}

template<typename TableT>
TableT &CsTableCell<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &CsTableCell<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
CsTableField<TableT> CsTableCell<TableT>::Field() const
{
	return CsTableField<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
CsTableRow<TableT> CsTableCell<TableT>::Row() const
{
	return CsTableRow<TableT>(m_tTable, m_nRowID);
}

template<typename TableT>
CsTableColumn<TableT> CsTableCell<TableT>::Column() const
{
	return CsTableColumn<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
cs_size_t CsTableCell<TableT>::FieldID() const
{
	return m_nColumnID;
}


template<typename TableT>
cs_size_t CsTableCell<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
cs_size_t CsTableCell<TableT>::ColumnID() const
{
	return m_nColumnID;
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_bool &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_char &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_schar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_uchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_wchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_short &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_ushort &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_int &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_uint &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_long &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_ulong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_longlong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_ulonglong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_float &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_double &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(cs_decimal &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::GetValue(CsString &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
CsVariant CsTableCell<TableT>::GetValue() const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_bool val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_char val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_schar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_uchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_wchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_short val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_ushort val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_int val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_uint val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_long val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_ulong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_longlong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_ulonglong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_float val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_double val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(cs_decimal val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(const CsString &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::SetValue(const CsVariant &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_bool val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_char val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_schar val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_uchar val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_wchar val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_short val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_ushort val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_int val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_uint val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_long val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_ulong val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_longlong val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_ulonglong val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_float val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_double val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(cs_decimal val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(const CsString &val)
{
	return SetValue(val);
}

template<typename TableT>
cs_bool CsTableCell<TableT>::operator=(const CsVariant &val)
{
	return SetValue(val);
}

#endif // _CORE_TABLE_CELL_H_