#ifndef _DATA_TABLE_TABLE_CELL_H_
#define _DATA_TABLE_TABLE_CELL_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableCell
{
public:
	CsTableCell(TableT &, gsize row, gsize column);
	CsTableCell(const CsTableCell<TableT> &);

	TableT &Table();
	const TableT &Table() const;

	CsTableField<TableT> Field() const;
	CsTableRow<TableT> Row() const;
	CsTableColumn<TableT> Column() const;

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
	GVariant GetValue() const;

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
	gbool SetValue(const GVariant &);

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
	gbool operator=(const GVariant &);

private:
	TableT &m_tTable;
	gsize m_nRowID;
	gsize m_nColumnID;
};

template<typename TableT>
CsTableCell<TableT>::CsTableCell(TableT &table, gsize row, gsize column)
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
gsize CsTableCell<TableT>::FieldID() const
{
	return m_nColumnID;
}


template<typename TableT>
gsize CsTableCell<TableT>::RowID() const
{
	return m_nRowID;
}

template<typename TableT>
gsize CsTableCell<TableT>::ColumnID() const
{
	return m_nColumnID;
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gbool &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gschar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(guchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gwchar &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gshort &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gushort &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gint &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(guint &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(glong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gulong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(glonglong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gulonglong &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gfloat &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gdouble &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(gdecimal &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::GetValue(GString &val) const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
GVariant CsTableCell<TableT>::GetValue() const
{
	return m_tTable.GetValue(m_nRowID, m_nColumnID);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gbool val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gschar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(guchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gwchar val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gshort val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gushort val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gint val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(guint val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(glong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gulong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(glonglong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gulonglong val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gfloat val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gdouble val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(gdecimal val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(const GString &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::SetValue(const GVariant &val)
{
	return m_tTable.SetValue(m_nRowID, m_nColumnID, val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gbool val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gschar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(guchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gwchar val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gshort val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gushort val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gint val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(guint val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(glong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gulong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(glonglong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gulonglong val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gfloat val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gdouble val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(gdecimal val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(const GString &val)
{
	return SetValue(val);
}

template<typename TableT>
gbool CsTableCell<TableT>::operator=(const GVariant &val)
{
	return SetValue(val);
}

#endif // _CORE_TABLE_CELL_H_