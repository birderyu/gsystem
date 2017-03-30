#ifndef _CORE_TABLE_H_
#define _CORE_TABLE_H_

#include "gobject.h"
#include "gtuple.h"
#include "gvector.h"

namespace gsystem { // gsystem

template<typename ...TS>
class GTable
	: virtual public GObject
{
public:
	typedef GTuple<TS...> RowType;

public:
	GTable(gsize row_count = 0);
	gsize RowCount() const;
	gvoid AddRow(const RowType &row);
	gvoid AddRow(RowType &&row);
	gvoid AddRow(const TS&... row);
	gvoid AddRow(TS&&... row);
	const RowType &GetRow(gsize row_id) const;
	RowType &GetRow(gsize row_id);
	gvoid SetRow(gsize row_id, const RowType &row);
	gvoid SetRow(gsize row_id, RowType &&row);
	gvoid SetRow(gsize row_id, const TS&... row);
	gvoid SetRow(gsize row_id, TS&&... row);

	template<gsize COLUMN_ID>
	const typename GTupleAt<COLUMN_ID, RowType>::ValueType &
		GetValue(gsize row_id) const;

	template<gsize COLUMN_ID>
	typename GTupleAt<COLUMN_ID, RowType>::ValueType &
		GetValue(gsize row_id);

	template<gsize COLUMN_ID>
	gvoid SetValue(gsize row_id, const typename GTupleAt<COLUMN_ID, RowType>::ValueType &value);

	template<gsize ROW_ID, gsize COLUMN_ID>
	gvoid SetValue(gsize row_id, typename GTupleAt<COLUMN_ID, RowType>::ValueType &&value);

private:
	GVector<RowType> m_tTable;
};

} // namespace gsystem

#include "gtable.inl"

#endif // _CORE_TABLE_H_
