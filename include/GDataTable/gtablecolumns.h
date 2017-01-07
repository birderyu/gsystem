#ifndef _CORE_TABLE_COLUMNS_H_
#define _CORE_TABLE_COLUMNS_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableColumns
{
public:
	GTableColumns(TableT &, CsSizeTypeArray *columns = NULL);
	GTableColumns(const GTableColumns &);

	TableT &Table();
	const TableT &Table() const;

	gsize Count() const;

	GTableColumn<TableT> operator[](gsize) const;
	GTableColumn<TableT> operator[](const GString &) const;

private:
	TableT &m_tTable;
	CsSizeTypeArray *m_pColumns;
};

#endif // _CORE_TABLE_COLUMNS_H_