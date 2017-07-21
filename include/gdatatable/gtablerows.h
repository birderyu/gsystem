#ifndef _CORE_TABLE_ROWS_H_
#define _CORE_TABLE_ROWS_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableRows
{
public:
	GTableRows(GDataTable &, GSizeArray *rows = GNULL);
	GTableRows(const GTableRows<TableT> &);
	GTableRows(GTableRows<TableT> &&);

	GDataTable &Table();
	const GDataTable &Table() const;

	gsize Count() const;

	GTableRow operator[](gsize) const;

	GTableRow Append();
	GTableRows Append(gsize);
	gbool Remove(const GTableRow &);
	gbool RemoveAt(gsize);
	gbool Clear();

	GTableRows &operator=(const GTableRows &);
};

#endif // _CORE_TABLE_ROWS_H_