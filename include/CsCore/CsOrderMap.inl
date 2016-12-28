#ifndef _CORE_ORDER_MAP_INLINE_
#define _CORE_ORDER_MAP_INLINE_

template<typename KeyT, typename ValueT, typename CompareT>
inline CsOrderMap<KeyT, ValueT, CompareT>::CsOrderMap()
{

}

template<typename KeyT, typename ValueT, typename CompareT>
inline CsOrderMap<KeyT, ValueT, CompareT>::CsOrderMap(const CsOrderMap<KeyT, ValueT, CompareT> &map)
: m_tTree(map.m_tTree), m_nSize(map.m_nSize)
{

}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_size_t CsOrderMap<KeyT, ValueT, CompareT>::Size() const
{
	return m_nSize;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_bool CsOrderMap<KeyT, ValueT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_void CsOrderMap<KeyT, ValueT, CompareT>::Clear()
{
	m_tTree.Destroy();
	m_nSize = 0;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_bool CsOrderMap<KeyT, ValueT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTree.Contains(key);
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &CsOrderMap<KeyT, ValueT, CompareT>::First()
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const ValueT &CsOrderMap<KeyT, ValueT, CompareT>::First() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const KeyT &CsOrderMap<KeyT, ValueT, CompareT>::FirstKey() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &CsOrderMap<KeyT, ValueT, CompareT>::Last()
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const ValueT &CsOrderMap<KeyT, ValueT, CompareT>::Last() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline const KeyT &CsOrderMap<KeyT, ValueT, CompareT>::LastKey() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_void CsOrderMap<KeyT, ValueT, CompareT>::Remove(const KeyT &key)
{
	cs_bool real_remove = false;
	m_tTree.Delete(key, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
}

template<typename KeyT, typename ValueT, typename CompareT>
inline KeyT CsOrderMap<KeyT, ValueT, CompareT>::Key(const ValueT &value, const KeyT &defaultKey) const
{
	// TODO
	return defaultKey;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT CsOrderMap<KeyT, ValueT, CompareT>::Value(const KeyT &key, const ValueT &defaultValue) const
{
	const CsOrderMapNode *node = m_tTree.Find(key);
	if (!node)
	{
		return defaultValue;
	}
	return node->m_tValue;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::Iterator CsOrderMap<KeyT, ValueT, CompareT>::Begin()
{
	return CsOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::Begin() const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::ConstBegin() const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::Iterator CsOrderMap<KeyT, ValueT, CompareT>::End()
{
	return CsOrderMap<KeyT, ValueT, CompareT>::Iterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::End() const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::ConstEnd() const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::Iterator CsOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key)
{
	return CsOrderMap<KeyT, ValueT, CompareT>::Iterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::Find(const KeyT &key) const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator CsOrderMap<KeyT, ValueT, CompareT>::ConstFind(const KeyT &key) const
{
	return CsOrderMap<KeyT, ValueT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::Iterator CsOrderMap<KeyT, ValueT, CompareT>::Insert(const KeyT &key, const ValueT &value)
{
	cs_bool real_insert = false;
	CsOrderMapNode *node = m_tTree.Insert(key, value, &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return CsOrderMap<KeyT, ValueT, CompareT>::Iterator(node);
}

template<typename KeyT, typename ValueT, typename CompareT>
inline typename CsOrderMap<KeyT, ValueT, CompareT>::Iterator CsOrderMap<KeyT, ValueT, CompareT>::Erase(const Iterator &iter)
{
	// TODO
	return CsOrderMap<KeyT, ValueT, CompareT>::Iterator();
}

template<typename KeyT, typename ValueT, typename CompareT>
inline CsOrderMap<KeyT, ValueT, CompareT> &CsOrderMap<KeyT, ValueT, CompareT>::operator=(const CsOrderMap<KeyT, ValueT, CompareT> &map)
{
	m_nSize = map.m_nSize;
	m_tTree = map.m_tTree;
	return *this;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_bool CsOrderMap<KeyT, ValueT, CompareT>::operator==(const CsOrderMap<KeyT, ValueT, CompareT> &) const
{
	// TODO
	return false;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline cs_bool CsOrderMap<KeyT, ValueT, CompareT>::operator!=(const CsOrderMap<KeyT, ValueT, CompareT> &map) const
{
	// TODO
	return false;
}

template<typename KeyT, typename ValueT, typename CompareT>
inline ValueT &CsOrderMap<KeyT, ValueT, CompareT>::operator[](const KeyT &key)
{
	cs_bool real_insert = false;
	CsOrderMapNode *node = m_tTree.Insert(key, ValueT(), &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return node->m_tValue;
}

#endif // _CORE_ORDER_MAP_INLINE_