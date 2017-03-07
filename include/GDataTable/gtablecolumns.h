#ifndef _CORE_TABLE_COLUMNS_H_
#define _CORE_TABLE_COLUMNS_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableColumns
{
public:
	GTableColumns(TableT &, GSizeArray *columns = GNULL);
	GTableColumns(const GTableColumns<TableT> &);
	GTableColumns(GTableColumns<TableT> &&);

	TableT &Table();
	const TableT &Table() const;

	gsize Count() const;

	GTableColumn<TableT> operator[](gsize) const;
	GTableColumn<TableT> operator[](const GString &) const;

private:
	TableT &m_tTable;
	GSizeArray *m_pColumns;
};

#endif // _CORE_TABLE_COLUMNS_H_