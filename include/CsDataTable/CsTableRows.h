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

	cs_size_t Count() const;

	CsTableRow operator[](cs_size_t) const;

	CsTableRow Append();
	CsTableRows Append(cs_size_t);
	cs_bool Remove(const CsTableRow &);
	cs_bool RemoveAt(cs_size_t);
	cs_bool Clear();

	CsTableRows &operator=(const CsTableRows &);
};

#endif // _CORE_TABLE_ROWS_H_