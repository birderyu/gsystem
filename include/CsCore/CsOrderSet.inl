#ifndef _CORE_ORDER_SET_INLINE_
#define _CORE_ORDER_SET_INLINE_

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT>::CsOrderSet()
{

}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT>::CsOrderSet(const CsOrderSet<KeyT, CompareT> &set)
: m_tTree(set.m_tTree), m_nSize(set.m_nSize)
{

}

template < typename KeyT, typename CompareT>
inline cs_size_t CsOrderSet<KeyT, CompareT>::Size() const
{
	return m_nSize;
}

template < typename KeyT, typename CompareT>
inline cs_bool CsOrderSet<KeyT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template < typename KeyT, typename CompareT>
inline cs_void CsOrderSet<KeyT, CompareT>::Clear()
{
	m_tTree.Destroy();
	m_nSize = 0;
}

template < typename KeyT, typename CompareT>
inline cs_bool CsOrderSet<KeyT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTree.Contains(key);
}

template < typename KeyT, typename CompareT>
inline const KeyT &CsOrderSet<KeyT, CompareT>::First() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tKey;
}

template < typename KeyT, typename CompareT>
inline const KeyT &CsOrderSet<KeyT, CompareT>::Last() const
{
	CS_ASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tKey;
}

template < typename KeyT, typename CompareT>
inline cs_void CsOrderSet<KeyT, CompareT>::Remove(const KeyT &key)
{
	cs_bool real_remove = false;
	m_tTree.Delete(key, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::Iterator CsOrderSet<KeyT, CompareT>::Begin()
{
	return CsOrderSet<KeyT, CompareT>::Iterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::Begin() const
{
	return CsOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::ConstBegin() const
{
	return CsOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::Iterator CsOrderSet<KeyT, CompareT>::End()
{
	return CsOrderSet<KeyT, CompareT>::Iterator();
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::End() const
{
	return CsOrderSet<KeyT, CompareT>::ConstIterator();
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::ConstEnd() const
{
	return CsOrderSet<KeyT, CompareT>::ConstIterator();
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::Iterator CsOrderSet<KeyT, CompareT>::Find(const KeyT &key)
{
	return CsOrderSet<KeyT, CompareT>::Iterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::Find(const KeyT &key) const
{
	return CsOrderSet<KeyT, CompareT>::Iterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::ConstIterator CsOrderSet<KeyT, CompareT>::ConstFind(const KeyT &key) const
{
	return CsOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::Iterator CsOrderSet<KeyT, CompareT>::Insert(const KeyT &key)
{
	cs_bool real_insert = false;
	CsOrderSetNode *node = m_tTree.Insert(key, CsDummyNodeT(), &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return CsOrderSet<KeyT, CompareT>::Iterator(node);
}

template < typename KeyT, typename CompareT>
inline typename CsOrderSet<KeyT, CompareT>::Iterator CsOrderSet<KeyT, CompareT>::Erase(const Iterator &iter)
{
	// TODO
	return CsOrderSet<KeyT, CompareT>::Iterator();
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::Intersect(const CsOrderSet<KeyT, CompareT> &set)
{
	CsOrderSet<KeyT, CompareT> set_copy(*this);
	Clear();
	for (CsOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		if (set_copy.Contains(*citer))
		{
			Insert(*citer)
		}
	}
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::Unite(const CsOrderSet<KeyT, CompareT> &set)
{
	for (CsOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Insert(*citer);
	}
	return *this;
}

template < typename KeyT, typename CompareT>
inline cs_bool CsOrderSet<KeyT, CompareT>::operator==(const CsOrderSet<KeyT, CompareT> &set) const
{
	// TODO
	return false;
}

template < typename KeyT, typename CompareT>
inline cs_bool CsOrderSet<KeyT, CompareT>::operator!=(const CsOrderSet<KeyT, CompareT> &set) const
{
	// TODO
	return false;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> CsOrderSet<KeyT, CompareT>::operator&(const CsOrderSet<KeyT, CompareT> &set) const
{
	CsOrderSet<KeyT, CompareT> set_copy(*this);
	set_copy.Intersect(set);
	return set_copy;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator&=(const CsOrderSet<KeyT, CompareT> &set)
{
	return Intersect(set);
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator&=(const KeyT &key)
{
	if (!Contains(key))
	{
		Clear();
		return *this;
	}
	else
	{
		Clear();
		Insert(key);
	}
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> CsOrderSet<KeyT, CompareT>::operator|(const CsOrderSet<KeyT, CompareT> &set) const
{
	CsOrderSet<KeyT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator|=(const CsOrderSet<KeyT, CompareT> &set)
{
	return Unite(set);
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator|=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> CsOrderSet<KeyT, CompareT>::operator+(const CsOrderSet<KeyT, CompareT> &set) const
{
	CsOrderSet<KeyT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator+=(const CsOrderSet<KeyT, CompareT> &set)
{
	return Unite(set);
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator+=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> CsOrderSet<KeyT, CompareT>::operator-(const CsOrderSet<KeyT, CompareT> &set) const
{
	CsOrderSet<KeyT, CompareT> set_copy(*this);
	for (CsOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		set_copy.Remove(*citer);
	}
	return set_copy;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator-=(const CsOrderSet<KeyT, CompareT> &set)
{
	for (CsOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Remove(*citer);
	}
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator-=(const KeyT &key)
{
	Remove(key);
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator>>(KeyT &key)
{
	key = Last();
	Remove(key);
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator<<(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
inline CsOrderSet<KeyT, CompareT> &CsOrderSet<KeyT, CompareT>::operator=(const CsOrderSet<KeyT, CompareT> &set)
{
	m_nSize = set.m_nSize;
	m_tTree = set.m_tTree;
	return *this;
}

#endif // _CORE_ORDER_SET_INLINE_