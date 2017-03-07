#ifndef _CORE_ORDER_MAP_INLINE_
#define _CORE_ORDER_MAP_INLINE_

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE GOrderMap<KeyT, ValueT, CompareT>::GOrderMap()
{

}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE GOrderMap<KeyT, ValueT, CompareT>::GOrderMap(const GOrderMap<KeyT, ValueT, CompareT> &map)
: m_tTree(map.m_tTree), m_nSize(map.m_nSize)
{

}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE GOrderMap<KeyT, ValueT, CompareT>::GOrderMap(GOrderMap<KeyT, ValueT, CompareT> &&map)
	: m_tTree(GMove(map.m_tTree)), m_nSize(map.m_nSize)
{
	map.m_nSize = 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gsize GOrderMap<KeyT, ValueT, CompareT>::Size() const
{
	return m_nSize;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gbool GOrderMap<KeyT, ValueT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gvoid GOrderMap<KeyT, ValueT, CompareT>::Clear()
{
	m_tTree.Dispose();
	m_nSize = 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gbool GOrderMap<KeyT, ValueT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTree.Contains(key);
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE ValueT &GOrderMap<KeyT, ValueT, CompareT>::First()
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE const ValueT &GOrderMap<KeyT, ValueT, CompareT>::First() const
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE const KeyT &GOrderMap<KeyT, ValueT, CompareT>::FirstKey() const
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE ValueT &GOrderMap<KeyT, ValueT, CompareT>::Last()
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE const ValueT &GOrderMap<KeyT, ValueT, CompareT>::Last() const
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE const KeyT &GOrderMap<KeyT, ValueT, CompareT>::LastKey() const
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gvoid GOrderMap<KeyT, ValueT, CompareT>::Remove(const KeyT &key)
{
	gbool real_remove = false;
	m_tTree.Delete(key, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE ValueT GOrderMap<KeyT, ValueT, CompareT>::Value(const KeyT &key, const ValueT &defaultValue) const
{
	const GOrderMapNode *node = m_tTree.Find(key);
	if (!node)
	{
		return defaultValue;
	}
	return node->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Begin()
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::Begin() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstBegin() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::End()
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::End() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstEnd() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key)
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key) const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstFind(const KeyT &key) const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Insert(const KeyT &key, const ValueT &value)
{
	gbool real_insert = false;
	GOrderMapNode *node = m_tTree.Insert(key, value, &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(node);
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Insert(const KeyT &key, ValueT &&value)
{
	gbool real_insert = false;
	GOrderMapNode *node = m_tTree.Insert(key, GForward<ValueT>(value), &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(node);
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Erase(const typename GOrderMap<KeyT, ValueT, CompareT>::Iterator &iter)
{
	Iterator next_iter = iter.Next();
	gbool real_remove = false;
	m_tTree.Delete(iter.m_pNode, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
	return next_iter;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE GOrderMap<KeyT, ValueT, CompareT> &GOrderMap<KeyT, ValueT, CompareT>::operator=(const GOrderMap<KeyT, ValueT, CompareT> &map)
{
	if (this == &map)
	{
		return *this;
	}
	m_nSize = map.m_nSize;
	m_tTree = map.m_tTree;
	return *this;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE GOrderMap<KeyT, ValueT, CompareT> &GOrderMap<KeyT, ValueT, CompareT>::operator=(GOrderMap<KeyT, ValueT, CompareT> &&map)
{
	if (this == &map)
	{
		return *this;
	}
	m_nSize = map.m_nSize;
	m_tTree = GMove(map.m_tTree);
	map.m_nSize = 0;
	return *this;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gbool GOrderMap<KeyT, ValueT, CompareT>::operator==(const GOrderMap<KeyT, ValueT, CompareT> &map) const
{
	return m_nSize == map.m_nSize 
		&& m_tTree == map.m_tTree;
}

template<typename KeyT, typename ValueT, typename CompareT>
GINLINE gbool GOrderMap<KeyT, ValueT, CompareT>::operator!=(const GOrderMap<KeyT, ValueT, CompareT> &map) const
{
	return m_nSize != map.m_nSize 
		|| m_tTree != map.m_tTree;
}

#endif // _CORE_ORDER_MAP_INLINE_