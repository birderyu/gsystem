#ifndef _DATA_TABLE_TABLE_CELL_H_
#define _DATA_TABLE_TABLE_CELL_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableCell
{
public:
	GTableCell(TableT &, gsize row, gsize column);
	GTableCell(const GTableCell<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	GTableField<TableT> Field() const;
	GTableRow<TableT> Row() const;
	GTableColumn<TableT> Column() const;

	gsize FieldID() const;
	gsize RowID() const;
	gsize ColumnID() const;

	gbool GetValue(gbool &) const;
	gbool GetValue(gchar &) const;
	gbool GetValue(gschar &) const;
	gbool GetValue(guchar &) const;
	gbool GetValue(gwchar &) const;
	gbool GetValue(gshort &) const;
	gbool GetValue(gushort &) const;
	gbool GetValue(gint &) const;
	gbool GetValue(guint &) const;
	gbool GetValue(glong &) const;
	gbool GetValue(gulong &) const;
	gbool GetValue(glonglong &) const;
	gbool GetValue(gulonglong &) const;
	gbool GetValue(gfloat &) const;
	gbool GetValue(gdouble &) const;
	gbool GetValue(gdecimal &) const;
	gbool GetValue(GString &) const;
	GVariety GetValue() const;

	gbool SetValue(gbool);
	gbool SetValue(gchar);
	gbool SetValue(gschar);
	gbool SetValue(guchar);
	gbool SetValue(gwchar);
	gbool SetValue(gshort);
	gbool SetValue(gushort);
	gbool SetValue(gint);
	gbool SetValue(guint);
	gbool SetValue(glong);
	gbool SetValue(gulong);
	gbool SetValue(glonglong);
	gbool SetValue(gulonglong);
	gbool SetValue(gfloat);
	gbool SetValue(gdouble);
	gbool SetValue(gdecimal);
	gbool SetValue(const GString &);
	gbool SetValue(const GVariety &);

	gbool operator=(gbool);
	gbool operator=(gchar);
	gbool operator=(gschar);
	gbool operator=(guchar);
	gbool operator=(gwchar);
	gbool operator=(gshort);
	gbool operator=(gushort);
	gbool operator=(gint);
	gbool operator=(guint);
	gbool operator=(glong);
	gbool operator=(gulong);
	gbool operator=(glonglong);
	gbool operator=(gulonglong);
	gbool operator=(gfloat);
	gbool operator=(gdouble);
	gbool operator=(gdecimal);
	gbool operator=(const GString &);
	gbool operator=(const GVariety &);

private:
	TableT &m_tTable;
	gsize m_nRowID;
	gsize m_nColumnID;
};

template<typename TableT>
GTableCell<TableT>::GTableCell(TableT &table, gsize row, gsize column)
: m_tTable(table), m_nRowID(row), m_nColumnID(column)
{

}

template<typename TableT>
GTableCell<TableT>::GTableCell(const GTableCell<TableT> &cell)
: m_tTable(cell.m_tTable), m_nRowID(cell.m_nRowID), m_nColumnID(cell.m_nColumnID)
{

}

template<typename TableT>
TableT &GTableCell<TableT>::Table()
{
	return m_tTable;
}

template<typename TableT>
const TableT &GTableCell<TableT>::Table() const
{
	return m_tTable;
}

template<typename TableT>
GTableField<TableT> GTableCell<TableT>::Field() const
{
	return GTableField<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
GTableRow<TableT> GTableCell<TableT>::Row() const
{
	return GTableRow<TableT>(m_tTable, m_nRowID);
}

template<typename TableT>
GTableColumn<TableT> GTableCell<TableT>::Column() const
{
	return GTableColumn<TableT>(m_tTable, m_nColumnID);
}

template<typename TableT>
gsize GTableCell<TableT>::FieldID() const
{
	return m_nColumnID;
}


template<typename TableT>
gsize GTableCell<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
gsize GTableCell<TableT>::ColumnID() const
{
	return m_nColumnID;
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gbool &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gschar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(guchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gwchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gshort &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gushort &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gint &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(guint &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(glong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gulong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(glonglong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gulonglong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gfloat &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gdouble &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(gdecimal &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::GetValue(GString &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
GVariety GTableCell<TableT>::GetValue() const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gbool val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gschar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(guchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gwchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gshort val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gushort val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gint val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(guint val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(glong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gulong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(glonglong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gulonglong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gfloat val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gdouble val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(gdecimal val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(const GString &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::SetValue(const GVariety &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gbool val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gschar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(guchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gwchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gshort val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gushort val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gint val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(guint val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(glong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gulong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(glonglong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gulonglong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gfloat val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gdouble val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(gdecimal val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(const GString &val)
{
	return SetValue(val);
}

template<typename TableT>
gbool GTableCell<TableT>::operator=(const GVariety &val)
{
	return SetValue(val);
}

#endif // _CORE_TABLE_CELL_H_