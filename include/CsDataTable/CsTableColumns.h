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

	cs_size_t Count() const;

	CsTableColumn<TableT> operator[](cs_size_t) const;
	CsTableColumn<TableT> operator[](const CsString &) const;

private:
	TableT &m_tTable;
	CsSizeTypeArray *m_pColumns;
};

#endif // _CORE_TABLE_COLUMNS_H_