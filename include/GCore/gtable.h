#ifndef _CORE_TABLE_H_
#define _CORE_TABLE_H_

#include "gobject.h"
#include "gtuple.h"
#include "gvector.h"

namespace gnova {

template<typename ...TS>
class GTable
	: virtual public GObject
{
public:
	typedef GTuple<TS...> RowType;

public:
	GTable(gsize row_count = 0)
		: m_tTable(row_count)
	{

	}

	gsize RowCount() const
	{
		return m_tTable.Size();
	}

	gvoid AddRow(const RowType &row)
	{
		m_tTable.PushBack(GMakeTuple<TS...>(row...));
	}

	gvoid AddRow(RowType &&row)
	{
		m_tTable.PushBack(GForward<RowType>(row));
	}

	gvoid AddRow(const TS&... row)
	{
		m_tTable.PushBack(row);
	}

	gvoid AddRow(TS&&... row)
	{
		m_tTable.PushBack(GMove(GMakeTuple<TS...>(GForward<TS>(row)...)));
	}

	const RowType &GetRow(gsize row_id) const
	{
		return m_tTable.GetAt(row_id);
	}

	RowType &GetRow(gsize row_id)
	{
		return m_tTable.GetAt(row_id);
	}

	gvoid SetRow(gsize row_id, const RowType &row)
	{
		m_tTable[row_id] = row;
	}

	gvoid SetRow(gsize row_id, RowType &&row)
	{
		m_tTable[row_id] = GForward<RowType>(row);
	}

	gvoid SetRow(gsize row_id, const TS&... row)
	{
		m_tTable[row_id] = GMakeTuple<TS...>(row...);
	}

	gvoid SetRow(gsize row_id, TS&&... row)
	{
		m_tTable[row_id] = GMove(GMakeTuple<TS...>(GForward<TS>(row)...));
	}

	template<gsize COLUMN_ID>
	const typename GTupleAt<COLUMN_ID, RowType>::ValueType &
	GetValue(gsize row_id) const
	{
		return GTupleConstGet<COLUMN_ID>(m_tTable[row_id]);
	}

	template<gsize COLUMN_ID>
	typename GTupleAt<COLUMN_ID, RowType>::ValueType &
	GetValue(gsize row_id)
	{
		return GTupleGet<COLUMN_ID>(m_tTable[row_id]);
	}

	template<gsize COLUMN_ID>
	gvoid SetValue(gsize row_id, const typename GTupleAt<COLUMN_ID, RowType>::ValueType &value)
	{
		GTupleSet<COLUMN_ID>(m_tTable[row_id], value);
	}

	template<gsize ROW_ID, gsize COLUMN_ID>
	gvoid SetValue(gsize row_id, typename GTupleAt<COLUMN_ID, RowType>::ValueType &&value)
	{
		GTupleSet<COLUMN_ID>(m_tTable[row_id],
			GForward<typename GTupleAt<COLUMN_ID, RowType>::ValueType>(value));
	}

private:
	GVector<RowType> m_tTable;
};

#include "gtable.inl"

}

#endif // _CORE_TABLE_H_
