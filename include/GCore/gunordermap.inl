#ifndef _CORE_UNORDER_MAP_INLINE_
#define _CORE_UNORDER_MAP_INLINE_

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE GUnorderMap<KeyT, ValueT, HashT, CompareT>::GUnorderMap()
{

}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE GUnorderMap<KeyT, ValueT, HashT, CompareT>::GUnorderMap(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &map)
	: m_tTable(map.m_tTable)
{

}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE GUnorderMap<KeyT, ValueT, HashT, CompareT>::GUnorderMap(GUnorderMap<KeyT, ValueT, HashT, CompareT> &&map)
	: m_tTable(GMove(map.m_tTable))
{

}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gsize GUnorderMap<KeyT, ValueT, HashT, CompareT>::Size() const
{
	return m_tTable.Size();
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gbool GUnorderMap<KeyT, ValueT, HashT, CompareT>::IsEmpty() const
{
	return m_tTable.IsEmpty();
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gvoid GUnorderMap<KeyT, ValueT, HashT, CompareT>::Clear()
{
	m_tTable.Dispose();
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gbool GUnorderMap<KeyT, ValueT, HashT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTable.Contains(key);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE ValueT &GUnorderMap<KeyT, ValueT, HashT, CompareT>::First()
{
	GASSERT(!IsEmpty());
	return m_tTable.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE const ValueT &GUnorderMap<KeyT, ValueT, HashT, CompareT>::First() const
{
	GASSERT(!IsEmpty());
	return m_tTable.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE const KeyT &GUnorderMap<KeyT, ValueT, HashT, CompareT>::FirstKey() const
{
	GASSERT(!IsEmpty());
	return m_tTable.FirstNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gvoid GUnorderMap<KeyT, ValueT, HashT, CompareT>::Remove(const KeyT &key)
{
	m_tTable.Delete(key);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE ValueT GUnorderMap<KeyT, ValueT, HashT, CompareT>::Value(const KeyT &key, const ValueT &defaultValue) const
{
	const GUnorderMapNode *node = m_tTable.Find(key);
	if (!node)
	{
		return defaultValue;
	}
	return node->m_tValue;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Begin()
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Begin() const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstBegin() const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::End()
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator(GNULL, *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::End() const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(GNULL, *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstEnd() const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(GNULL, *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Find(const KeyT &key)
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Find(const KeyT &key) const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstFind(const KeyT &key) const
{
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::ConstIterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Insert(const KeyT &key, const ValueT &value)
{
	GUnorderMapNode *node = m_tTable.Insert(key, value);
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator(node, *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Insert(const KeyT &key, ValueT &&value)
{
	GUnorderMapNode *node = m_tTable.Insert(key, GForward<ValueT>(value));
	return GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator(node, *this);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE typename GUnorderMap<KeyT, ValueT, HashT, CompareT>::Iterator GUnorderMap<KeyT, ValueT, HashT, CompareT>::Erase(const Iterator &iter)
{
	Iterator next_iter = iter.Next();
	Remove(iter.Key());
	return next_iter;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE GUnorderMap<KeyT, ValueT, HashT, CompareT> &GUnorderMap<KeyT, ValueT, HashT, CompareT>::operator=(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &map)
{
	if (this == &map)
	{
		return *this;
	}
	m_tTable = map.m_tTable;
	return *this;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE GUnorderMap<KeyT, ValueT, HashT, CompareT> &GUnorderMap<KeyT, ValueT, HashT, CompareT>::operator=(GUnorderMap<KeyT, ValueT, HashT, CompareT> &&map)
{
	if (this == &map)
	{
		return *this;
	}
	m_tTable = GMove(map.m_tTable);
	return *this;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gbool GUnorderMap<KeyT, ValueT, HashT, CompareT>::operator==(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &) const
{
	// TODO
	return false;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT>
GINLINE gbool GUnorderMap<KeyT, ValueT, HashT, CompareT>::operator!=(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &) const
{
	// TODO
	return false;
}

#endif // _CORE_UNORDER_MAP_INLINE_
