#ifndef _CORE_TABLE_COLUMNS_H_
#define _CORE_TABLE_COLUMNS_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableColumns
{
public:
	CsTableColumns(TableT &, CsSizeTypeArray *columns = NULL);
	CsTableColumns(const CsTableColumns &);

	TableT &Table();
	const TableT &Table() const;

	gsize Count() const;

	CsTableColumn<TableT> operator[](gsize) const;
	CsTableColumn<TableT> operator[](const GString &) const;

private:
	TableT &m_tTable;
	CsSizeTypeArray *m_pColumns;
};

#endif // _CORE_TABLE_COLUMNS_H_