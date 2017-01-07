#ifndef _CORE_ORDER_MAP_INLINE_
#define _CORE_ORDER_MAP_INLINE_

template<typename KeyT, typename ValueT, typename CompareT>
inline GOrderMap<KeyT, ValueT, CompareT>::GOrderMap()
{

}

template<typename KeyT, typename ValueT, typename CompareT>
inline GOrderMap<KeyT, ValueT, CompareT>::GOrderMap(const GOrderMap<KeyT, ValueT, CompareT> &map)
: m_tTree(map.m_tTree), m_nSize(map.m_nSize)
{

}

template<typename KeyT, typename ValueT, typename CompareT>
inline gsize GOrderMap<KeyT, ValueT, CompareT>::Size() const
{
	return m_nSize;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gbool GOrderMap<KeyT, ValueT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gvoid GOrderMap<KeyT, ValueT, CompareT>::Clear()
{
	m_tTree.Destroy();
	m_nSize = 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gbool GOrderMap<KeyT, ValueT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTree.Contains(key);
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &GOrderMap<KeyT, ValueT, CompareT>::First()
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const ValueT &GOrderMap<KeyT, ValueT, CompareT>::First() const
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const KeyT &GOrderMap<KeyT, ValueT, CompareT>::FirstKey() const
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &GOrderMap<KeyT, ValueT, CompareT>::Last()
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const ValueT &GOrderMap<KeyT, ValueT, CompareT>::Last() const
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const KeyT &GOrderMap<KeyT, ValueT, CompareT>::LastKey() const
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gvoid GOrderMap<KeyT, ValueT, CompareT>::Remove(const KeyT &key)
{
	gbool real_remove = false;
	m_tTree.Delete(key, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
}

template<typename KeyT, typename ValueT, typename CompareT>
inline KeyT GOrderMap<KeyT, ValueT, CompareT>::Key(const ValueT &value, const KeyT &defaultKey) const
{
	// TODO
	return defaultKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT GOrderMap<KeyT, ValueT, CompareT>::Value(const KeyT &key, const ValueT &defaultValue) const
{
	const CsOrderMapNode *node = m_tTree.Find(key);
	if (!node)
	{
		return defaultValue;
	}
	return node->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Begin()
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::Begin() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstBegin() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::End()
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::End() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstEnd() const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key)
{
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key) const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::ConstIterator GOrderMap<KeyT, ValueT, CompareT>::ConstFind(const KeyT &key) const
{
	return GOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Insert(const KeyT &key, const ValueT &value)
{
	gbool real_insert = false;
	CsOrderMapNode *node = m_tTree.Insert(key, value, &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator(node);
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename GOrderMap<KeyT, ValueT, CompareT>::Iterator GOrderMap<KeyT, ValueT, CompareT>::Erase(const Iterator &iter)
{
	// TODO
	return GOrderMap<KeyT, ValueT, CompareT>::Iterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline GOrderMap<KeyT, ValueT, CompareT> &GOrderMap<KeyT, ValueT, CompareT>::operator=(const GOrderMap<KeyT, ValueT, CompareT> &map)
{
	m_nSize = map.m_nSize;
	m_tTree = map.m_tTree;
	return *this;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gbool GOrderMap<KeyT, ValueT, CompareT>::operator==(const GOrderMap<KeyT, ValueT, CompareT> &) const
{
	// TODO
	return false;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline gbool GOrderMap<KeyT, ValueT, CompareT>::operator!=(const GOrderMap<KeyT, ValueT, CompareT> &map) const
{
	// TODO
	return false;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &GOrderMap<KeyT, ValueT, CompareT>::operator[](const KeyT &key)
{
	gbool real_insert = false;
	CsOrderMapNode *node = m_tTree.Insert(key, ValueT(), &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return node->m_tValue;
}

#endif // _CORE_ORDER_MAP_INLINE_