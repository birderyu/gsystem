#ifndef _CORE_TABLE_COLUMN_H_
#define _CORE_TABLE_COLUMN_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableColumn
{
public:
	GTableColumn(TableT &, gsize column);
	GTableColumn(const GTableColumn &);
	GTableColumn(GTableColumn &&);

	TableT &Table();
	const TableT &Table() const;

	GTableField<TableT> Field() const;
	gsize FieldID() const;
	gsize ColumnID() const;

	GTableCell<TableT> operator[](gsize) const;

private:
	TableT *m_pTable;
	gsize m_nColumnID;
};

template<typename TableT>
GTableColumn<TableT>::GTableColumn(TableT &table, gsize column)
: m_tTable(table), m_nColumnID(column)
{

}

template<typename TableT>
GTableColumn<TableT>::GTableColumn(const GTableColumn &column)
: m_tTable(column.m_tTable), m_nColumnID(column.m_nColumnID)
{

}

template<typename TableT>
TableT &GTableColumn<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &GTableColumn<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
GTableField<TableT> GTableColumn<TableT>::Field() const
{
	return GTableField<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
gsize GTableColumn<TableT>::FieldID() const
{
	return m_nColumnID;
}

template<typename TableT>
gsize GTableColumn<TableT>::ColumnID() const
{
	return m_nColumnID;
}

template<typename TableT>
GTableCell<TableT> GTableColumn<TableT>::operator[](gsize row) const
{
	return GTableCell<TableT>(m_tTable, m_nColumnID, row);
}

#endif // _CORE_TABLE_COLUMN_H_