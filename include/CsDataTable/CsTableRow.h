#ifndef _CORE_TABLE_ROW_H_
#define _CORE_TABLE_ROW_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableRow
{
public:
	CsTableRow(TableT &, gsize row);
	CsTableRow(const CsTableRow<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	CsTableField<TableT> Field(gsize) const;
	CsTableField<TableT> Field(const GString &) const;
	gsize RowID() const;

	CsTableCell<TableT> operator[](gsize) const;
	CsTableCell<TableT> operator[](const GString &) const;

private:
	TableT &m_tTable;
	gsize m_nRowID;
};

template<typename TableT>
CsTableRow<TableT>::CsTableRow(TableT &table, gsize row)
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
CsTableField<TableT> CsTableRow<TableT>::Field(gsize field) const
{
	return CsTableField<TableT>(m_tTable, field);
}

template<typename TableT>
CsTableField<TableT> CsTableRow<TableT>::Field(const GString &sFieldName) const
{
	return CsTableField<TableT>(m_tTable, m_tTable.GetFieldID(sFieldName));
}

template<typename TableT>
gsize CsTableRow<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
CsTableCell<TableT> CsTableRow<TableT>::operator[](gsize column) const
{
	return CsTableCell<TableT>(m_tTable, m_nRowID, column);
}

template<typename TableT>
CsTableCell<TableT> CsTableRow<TableT>::operator[](const GString &sFieldName) const
{
	return CsTableCell<TableT>(m_tTable, m_nRowID, m_tTable.GetFieldID(sFieldName));
}

#endif // _CORE_TABLE_ROW_H_