#ifndef _CORE_ORDER_SET_INLINE_
#define _CORE_ORDER_SET_INLINE_

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT>::GOrderSet()
{

}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT>::GOrderSet(const GOrderSet<KeyT, CompareT> &set)
	: m_tTree(set.m_tTree), m_nSize(set.m_nSize)
{

}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT>::GOrderSet(GOrderSet<KeyT, CompareT> &&set)
	: m_tTree(GMove(set.m_tTree)), m_nSize(set.m_nSize)
{
	set.m_nSize = 0;
}

template < typename KeyT, typename CompareT>
GINLINE gsize GOrderSet<KeyT, CompareT>::Size() const
{
	return m_nSize;
}

template < typename KeyT, typename CompareT>
GINLINE gbool GOrderSet<KeyT, CompareT>::IsEmpty() const
{
	return m_nSize == 0;
}

template < typename KeyT, typename CompareT>
GINLINE gvoid GOrderSet<KeyT, CompareT>::Clear()
{
	m_tTree.Dispose();
	m_nSize = 0;
}

template < typename KeyT, typename CompareT>
GINLINE gbool GOrderSet<KeyT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTree.Contains(key);
}

template < typename KeyT, typename CompareT>
GINLINE const KeyT &GOrderSet<KeyT, CompareT>::First() const
{
	GASSERT(!IsEmpty());
	return m_tTree.FirstNode()->m_tKey;
}

template < typename KeyT, typename CompareT>
GINLINE const KeyT &GOrderSet<KeyT, CompareT>::Last() const
{
	GASSERT(!IsEmpty());
	return m_tTree.LastNode()->m_tKey;
}

template < typename KeyT, typename CompareT>
GINLINE gvoid GOrderSet<KeyT, CompareT>::Remove(const KeyT &key)
{
	gbool real_remove = false;
	m_tTree.Delete(key, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::Iterator GOrderSet<KeyT, CompareT>::Begin()
{
	return GOrderSet<KeyT, CompareT>::Iterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::Begin() const
{
	return GOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::ConstBegin() const
{
	return GOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.FirstNode());
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::Iterator GOrderSet<KeyT, CompareT>::End()
{
	return GOrderSet<KeyT, CompareT>::Iterator();
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::End() const
{
	return GOrderSet<KeyT, CompareT>::ConstIterator();
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::ConstEnd() const
{
	return GOrderSet<KeyT, CompareT>::ConstIterator();
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::Iterator GOrderSet<KeyT, CompareT>::Find(const KeyT &key)
{
	return GOrderSet<KeyT, CompareT>::Iterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::Find(const KeyT &key) const
{
	return GOrderSet<KeyT, CompareT>::Iterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::ConstIterator GOrderSet<KeyT, CompareT>::ConstFind(const KeyT &key) const
{
	return GOrderSet<KeyT, CompareT>::ConstIterator(m_tTree.Find(key));
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::Iterator GOrderSet<KeyT, CompareT>::Insert(const KeyT &key)
{
	gbool real_insert = false;
	GOrderSetNode *node = m_tTree.Insert(key, GDummyNodeT(), &real_insert);
	if (real_insert)
	{
		m_nSize++;
	}
	return GOrderSet<KeyT, CompareT>::Iterator(node);
}

template < typename KeyT, typename CompareT>
GINLINE typename GOrderSet<KeyT, CompareT>::Iterator GOrderSet<KeyT, CompareT>::Erase(const Iterator &iter)
{
	Iterator next_iter = iter + 1;
	gbool real_remove = false;
	m_tTree.Delete(iter.m_pNode, &real_remove);
	if (real_remove)
	{
		m_nSize--;
	}
	return next_iter;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::Intersect(const GOrderSet<KeyT, CompareT> &set)
{
	GOrderSet<KeyT, CompareT> set_move(GMove(*this));
	for (GOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		if (set_move.Contains(*citer))
		{
			Insert(*citer)
		}
	}
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::Unite(const GOrderSet<KeyT, CompareT> &set)
{
	for (GOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Insert(*citer);
	}
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE gbool GOrderSet<KeyT, CompareT>::operator==(const GOrderSet<KeyT, CompareT> &set) const
{
	return m_nSize == set.m_nSize
		&& m_tTree == set.m_tTree;
}

template < typename KeyT, typename CompareT>
GINLINE gbool GOrderSet<KeyT, CompareT>::operator!=(const GOrderSet<KeyT, CompareT> &set) const
{
	return m_nSize != set.m_nSize
		|| m_tTree != set.m_tTree;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> GOrderSet<KeyT, CompareT>::operator&(const GOrderSet<KeyT, CompareT> &set) const
{
	GOrderSet<KeyT, CompareT> set_copy;
	for (GOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		if (Contains(*citer))
		{
			set_copy.Insert(*citer)
		}
	}
	return set_copy;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator&=(const GOrderSet<KeyT, CompareT> &set)
{
	return Intersect(set);
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator&=(const KeyT &key)
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
GINLINE GOrderSet<KeyT, CompareT> GOrderSet<KeyT, CompareT>::operator|(const GOrderSet<KeyT, CompareT> &set) const
{
	GOrderSet<KeyT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator|=(const GOrderSet<KeyT, CompareT> &set)
{
	return Unite(set);
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator|=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> GOrderSet<KeyT, CompareT>::operator+(const GOrderSet<KeyT, CompareT> &set) const
{
	GOrderSet<KeyT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator+=(const GOrderSet<KeyT, CompareT> &set)
{
	return Unite(set);
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator+=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> GOrderSet<KeyT, CompareT>::operator-(const GOrderSet<KeyT, CompareT> &set) const
{
	GOrderSet<KeyT, CompareT> set_copy(*this);
	for (GOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		set_copy.Remove(*citer);
	}
	return set_copy;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator-=(const GOrderSet<KeyT, CompareT> &set)
{
	for (GOrderSet<KeyT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Remove(*citer);
	}
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator-=(const KeyT &key)
{
	Remove(key);
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator>>(KeyT &key)
{
	key = Last();
	Remove(key);
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator<<(const KeyT &key)
{
	Insert(key);
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator=(const GOrderSet<KeyT, CompareT> &set)
{
	if (this == &set)
	{
		return *this;
	}
	m_nSize = set.m_nSize;
	m_tTree = set.m_tTree;
	return *this;
}

template < typename KeyT, typename CompareT>
GINLINE GOrderSet<KeyT, CompareT> &GOrderSet<KeyT, CompareT>::operator=(GOrderSet<KeyT, CompareT> &&set)
{
	if (this == &set)
	{
		return *this;
	}
	m_nSize = set.m_nSize;
	m_tTree = GMove(set.m_tTree);
	set.m_nSize = 0;
	return *this;
}

#endif // _CORE_ORDER_SET_INLINE_