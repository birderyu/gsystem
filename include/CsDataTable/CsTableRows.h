#ifndef _CORE_TABLE_ROWS_H_
#define _CORE_TABLE_ROWS_H_

#include "CsTableGlobal.h"

template<typename TableT>
class CsTableRows
{
public:
	CsTableRows(CsDataTable &, CsSizeTypeArray *rows = NULL);
	CsTableRows(const CsTableRows &);

	CsDataTable &Table();
	const CsDataTable &Table() const;

	gsize Count() const;

	CsTableRow operator[](gsize) const;

	CsTableRow Append();
	CsTableRows Append(gsize);
	gbool Remove(const CsTableRow &);
	gbool RemoveAt(gsize);
	gbool Clear();

	CsTableRows &operator=(const CsTableRows &);
};

#endif // _CORE_TABLE_ROWS_H_