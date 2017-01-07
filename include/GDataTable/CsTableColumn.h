#ifndef _CORE_TABLE_COLUMN_H_
#define _CORE_TABLE_COLUMN_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableColumn
{
public:
	CsTableColumn(TableT &, gsize column);
	CsTableColumn(const CsTableColumn &);

	TableT &Table();
	const TableT &Table() const;

	CsTableField<TableT> Field() const;
	gsize FieldID() const;
	gsize ColumnID() const;

	CsTableCell<TableT> operator[](gsize) const;

private:
	TableT &m_tTable;
	gsize m_nColumnID;
};

template<typename TableT>
CsTableColumn<TableT>::CsTableColumn(TableT &table, gsize column)
: m_tTable(table), m_nColumnID(column)
{

}

template<typename TableT>
CsTableColumn<TableT>::CsTableColumn(const CsTableColumn &column)
: m_tTable(column.m_tTable), m_nColumnID(column.m_nColumnID)
{

}

template<typename TableT>
TableT &CsTableColumn<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &CsTableColumn<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
CsTableField<TableT> CsTableColumn<TableT>::Field() const
{
	return CsTableField<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
gsize CsTableColumn<TableT>::FieldID() const
{
	return m_nColumnID;
}

template<typename TableT>
gsize CsTableColumn<TableT>::ColumnID() const
{
	return m_nColumnID;
}

template<typename TableT>
CsTableCell<TableT> CsTableColumn<TableT>::operator[](gsize row) const
{
	return CsTableCell<TableT>(m_tTable, m_nColumnID, row);
}

#endif // _CORE_TABLE_COLUMN_H_