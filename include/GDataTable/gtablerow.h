#ifndef _CORE_TABLE_ROW_H_
#define _CORE_TABLE_ROW_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableRow
{
public:
	GTableRow(TableT &, gsize row);
	GTableRow(const GTableRow<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	GTableField<TableT> Field(gsize field) const;
	GTableField<TableT> Field(const GString &field) const;
	gsize RowID() const;

	GTableCell<TableT> operator[](gsize) const;
	GTableCell<TableT> operator[](const GString &) const;

private:
	TableT &m_tTable;
	gsize m_nRowID;
};

template<typename TableT>
GTableRow<TableT>::GTableRow(TableT &table, gsize row)
: m_tTable(table), m_nRowID(row)
{

}

template<typename TableT>
GTableRow<TableT>::GTableRow(const GTableRow<TableT> &row)
: m_tTable(row.m_tTable), m_nRowID(row.m_nRowID)
{

}

template<typename TableT>
TableT &GTableRow<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &GTableRow<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
GTableField<TableT> GTableRow<TableT>::Field(gsize field) const
{
	return GTableField<TableT>(m_tTable, field);
}

template<typename TableT>
GTableField<TableT> GTableRow<TableT>::Field(const GString &sFieldName) const
{
	return GTableField<TableT>(m_tTable, m_tTable.GetFieldID(sFieldName));
}

template<typename TableT>
gsize GTableRow<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
GTableCell<TableT> GTableRow<TableT>::operator[](gsize column) const
{
	return GTableCell<TableT>(m_tTable, m_nRowID, column);
}

template<typename TableT>
GTableCell<TableT> GTableRow<TableT>::operator[](const GString &sFieldName) const
{
	return GTableCell<TableT>(m_tTable, m_nRowID, m_tTable.GetFieldID(sFieldName));
}

#endif // _CORE_TABLE_ROW_H_