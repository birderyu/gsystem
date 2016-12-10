#ifndef _CORE_TABLE_ROW_H_
#define _CORE_TABLE_ROW_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableRow
{
public:
	CsTableRow(TableT &, cs_size_t row);
	CsTableRow(const CsTableRow<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	CsTableField<TableT> Field(cs_size_t) const;
	CsTableField<TableT> Field(const CsString &) const;
	cs_size_t RowID() const;

	CsTableCell<TableT> operator[](cs_size_t) const;
	CsTableCell<TableT> operator[](const CsString &) const;

private:
	TableT &m_tTable;
	cs_size_t m_nRowID;
};

template<typename TableT>
CsTableRow<TableT>::CsTableRow(TableT &table, cs_size_t row)
: m_tTable(table), m_nRowID(row)
{

}

template<typename TableT>
CsTableRow<TableT>::CsTableRow(const CsTableRow<TableT> &row)
: m_tTable(row.m_tTable), m_nRowID(row.m_nRowID)
{

}

template<typename TableT>
TableT &CsTableRow<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &CsTableRow<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
CsTableField<TableT> CsTableRow<TableT>::Field(cs_size_t field) const
{
	return CsTableField<TableT>(m_tTable, field);
}

template<typename TableT>
CsTableField<TableT> CsTableRow<TableT>::Field(const CsString &sFieldName) const
{
	return CsTableField<TableT>(m_tTable, m_tTable.GetFieldID(sFieldName));
}

template<typename TableT>
cs_size_t CsTableRow<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
CsTableCell<TableT> CsTableRow<TableT>::operator[](cs_size_t column) const
{
	return CsTableCell<TableT>(m_tTable, m_nRowID, column);
}

template<typename TableT>
CsTableCell<TableT> CsTableRow<TableT>::operator[](const CsString &sFieldName) const
{
	return CsTableCell<TableT>(m_tTable, m_nRowID, m_tTable.GetFieldID(sFieldName));
}

#endif // _CORE_TABLE_ROW_H_