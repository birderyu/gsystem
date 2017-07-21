#ifndef _CORE_TABLE_INLINE_
#define _CORE_TABLE_INLINE_

namespace gsystem {

template<typename ...TS> GINLINE
GTable<TS...>::GTable(gsize row_count)
	: m_tTable(row_count)
{

}

template<typename ...TS> GINLINE
gsize GTable<TS...>::RowCount() const
{
	return m_tTable.Size();
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::AddRow(const RowType &row)
{
	m_tTable.PushBack(GMakeTuple<TS...>(row...));
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::AddRow(RowType &&row)
{
	m_tTable.PushBack(GForward<RowType>(row));
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::AddRow(const TS&... row)
{
	m_tTable.PushBack(row);
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::AddRow(TS&&... row)
{
	m_tTable.PushBack(GMove(GMakeTuple<TS...>(GForward<TS>(row)...)));
}

template<typename ...TS> GINLINE
const typename GTable<TS...>::RowType &GTable<TS...>::GetRow(gsize row_id) const
{
	return m_tTable.GetAt(row_id);
}

template<typename ...TS> GINLINE
typename GTable<TS...>::RowType &GTable<TS...>::GetRow(gsize row_id)
{
	return m_tTable.GetAt(row_id);
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::SetRow(gsize row_id, const typename GTable<TS...>::RowType &row)
{
	m_tTable[row_id] = row;
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::SetRow(gsize row_id, typename GTable<TS...>::RowType &&row)
{
	m_tTable[row_id] = GForward<RowType>(row);
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::SetRow(gsize row_id, const TS&... row)
{
	m_tTable[row_id] = GMakeTuple<TS...>(row...);
}

template<typename ...TS> GINLINE
gvoid GTable<TS...>::SetRow(gsize row_id, TS&&... row)
{
	m_tTable[row_id] = GMove(GMakeTuple<TS...>(GForward<TS>(row)...));
}

template<typename ...TS>
template<gsize COLUMN_ID> GINLINE
const typename GTupleAt<COLUMN_ID, typename GTable<TS...>::RowType>::ValueType &
GTable<TS...>::GetValue(gsize row_id) const
{
	return GTupleConstGet<COLUMN_ID>(m_tTable[row_id]);
}

template<typename ...TS>
template<gsize COLUMN_ID> GINLINE
typename GTupleAt<COLUMN_ID, typename GTable<TS...>::RowType>::ValueType &
GTable<TS...>::GetValue(gsize row_id)
{
	return GTupleGet<COLUMN_ID>(m_tTable[row_id]);
}

template<typename ...TS>
template<gsize COLUMN_ID> GINLINE
gvoid GTable<TS...>::SetValue(gsize row_id, 
	const typename GTupleAt<COLUMN_ID, typename GTable<TS...>::RowType>::ValueType &value)
{
	GTupleSet<COLUMN_ID>(m_tTable[row_id], value);
}

template<typename ...TS>
template<gsize ROW_ID, gsize COLUMN_ID> GINLINE
gvoid GTable<TS...>::SetValue(gsize row_id, 
	typename GTupleAt<COLUMN_ID, typename GTable<TS...>::RowType>::ValueType &&value)
{
	GTupleSet<COLUMN_ID>(m_tTable[row_id],
		GForward<typename GTupleAt<COLUMN_ID, RowType>::ValueType>(value));
}

}

#endif // _CORE_TABLE_INLINE_
