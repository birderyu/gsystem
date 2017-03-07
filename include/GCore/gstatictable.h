/// 静态表，静态表的行数是固定的，不可以扩展
#ifndef _CORE_STATIC_TABLE_H_
#define _CORE_STATIC_TABLE_H_

#include "gobject.h"
#include "gtuple.h"

template<gsize ROW_SIZE, typename ...TS>
class GStaticTable
	: virtual public GObject
{
public:
	typedef GTuple<TS...> RowType;

public:
	template<gsize ROW_ID>
	const RowType &GetRow() const
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		return m_tTable[ROW_ID];
	}

	template<gsize ROW_ID>
	RowType &GetRow()
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		return m_tTable[ROW_ID];
	}

	template<gsize ROW_ID>
	gvoid SetRow(const RowType &row)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		m_tTable[ROW_ID] = row;
	}

	template<gsize ROW_ID>
	gvoid SetRow(RowType &&row)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		m_tTable[ROW_ID] = GForward<RowType>(row);
	}

	template<gsize ROW_ID>
	gvoid SetRow(const TS&... row)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		m_tTable[ROW_ID] = GMakeTuple<TS...>(row...);
	}

	template<gsize ROW_ID>
	gvoid SetRow(TS&&... row)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		m_tTable[ROW_ID] = GMove(GMakeTuple<TS...>(GForward<TS>(row)...));
	}

	template<gsize ROW_ID, gsize COLUMN_ID>
	const typename GTupleAt<COLUMN_ID, RowType>::ValueType &
	GetValue() const
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		return GTupleConstGet<COLUMN_ID>(m_tTable[ROW_ID]);
	}

	template<gsize ROW_ID, gsize COLUMN_ID>
	typename GTupleAt<COLUMN_ID, RowType>::ValueType &
	GetValue()
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		return GTupleGet<COLUMN_ID>(m_tTable[ROW_ID]);
	}

	template<gsize ROW_ID, gsize COLUMN_ID>
	gvoid SetValue(const typename GTupleAt<COLUMN_ID, RowType>::ValueType &value)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		GTupleSet<COLUMN_ID>(m_tTable[ROW_ID], value);
	}

	template<gsize ROW_ID, gsize COLUMN_ID>
	gvoid SetValue(typename GTupleAt<COLUMN_ID, RowType>::ValueType &&value)
	{
		static_assert(ROW_ID < ROW_SIZE, "row id must less than row size.");
		GTupleSet<COLUMN_ID>(m_tTable[ROW_ID], 
			GForward<typename GTupleAt<COLUMN_ID, RowType>::ValueType>(value));
	}

private:
	RowType m_tTable[ROW_SIZE];
};

#endif // _CORE_STATIC_TABLE_H_
