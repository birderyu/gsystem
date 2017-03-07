#ifndef _CORE_UNORDER_SET_INLINE_
#define _CORE_UNORDER_SET_INLINE_

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT>::GUnorderSet()
{

}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT>::GUnorderSet(const GUnorderSet<KeyT, HashT, CompareT> &set)
	: m_tTable(set.m_tTable)
{

}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT>::GUnorderSet(GUnorderSet<KeyT, HashT, CompareT> &&set)
	: m_tTable(GMove(set.m_tTable))
{

}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gsize GUnorderSet<KeyT, HashT, CompareT>::Size() const
{
	return m_tTable.Size();
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gbool GUnorderSet<KeyT, HashT, CompareT>::IsEmpty() const
{
	return m_tTable.IsEmpty();
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gvoid GUnorderSet<KeyT, HashT, CompareT>::Clear()
{
	m_tTable.Dispose();
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gbool GUnorderSet<KeyT, HashT, CompareT>::Contains(const KeyT &key) const
{
	return m_tTable.Contains(key);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE const KeyT &GUnorderSet<KeyT, HashT, CompareT>::First() const
{
	GASSERT(!IsEmpty());
	return m_tTable.FirstNode()->m_tKey;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gvoid GUnorderSet<KeyT, HashT, CompareT>::Remove(const KeyT &key)
{
	m_tTable.Delete(key);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::Iterator GUnorderSet<KeyT, HashT, CompareT>::Begin()
{
	return GUnorderSet<KeyT, HashT, CompareT>::Iterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::Begin() const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::ConstBegin() const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(m_tTable.FirstNode(), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::Iterator GUnorderSet<KeyT, HashT, CompareT>::End()
{
	return GUnorderSet<KeyT, HashT, CompareT>::Iterator(GNULL, *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::End() const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(GNULL, *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::ConstEnd() const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(GNULL, *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::Iterator GUnorderSet<KeyT, HashT, CompareT>::Find(const KeyT &key)
{
	return GUnorderSet<KeyT, HashT, CompareT>::Iterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::Find(const KeyT &key) const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::ConstIterator GUnorderSet<KeyT, HashT, CompareT>::ConstFind(const KeyT &key) const
{
	return GUnorderSet<KeyT, HashT, CompareT>::ConstIterator(m_tTable.Find(key), *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::Iterator GUnorderSet<KeyT, HashT, CompareT>::Insert(const KeyT &key)
{
	GUnorderSetNode *node = m_tTable.Insert(key, GDummyNodeT());
	return GUnorderSet<KeyT, HashT, CompareT>::Iterator(node, *this);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE typename GUnorderSet<KeyT, HashT, CompareT>::Iterator GUnorderSet<KeyT, HashT, CompareT>::Erase(const Iterator &)
{
	// TODO
	return GUnorderSet<KeyT, HashT, CompareT>::Iterator();
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::Intersect(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	GUnorderSet<KeyT, HashT, CompareT> set_move(GMove(*this));
	for (GUnorderSet<KeyT, HashT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		if (set_move.Contains(*citer))
		{
			Insert(*citer)
		}
	}
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::Unite(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	for (GUnorderSet<KeyT, HashT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Insert(*citer);
	}
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gbool GUnorderSet<KeyT, HashT, CompareT>::operator==(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	// TODO
	return false;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE gbool GUnorderSet<KeyT, HashT, CompareT>::operator!=(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	// TODO
	return false;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> GUnorderSet<KeyT, HashT, CompareT>::operator&(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	GUnorderSet<KeyT, HashT, CompareT> set_copy;
	for (GUnorderSet<KeyT, HashT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		if (Contains(*citer))
		{
			set_copy.Insert(*citer)
		}
	}
	return set_copy;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator&=(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	return Intersect(set);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator&=(const KeyT &key)
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

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> GUnorderSet<KeyT, HashT, CompareT>::operator|(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	GUnorderSet<KeyT, HashT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator|=(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	return Unite(set);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator|=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> GUnorderSet<KeyT, HashT, CompareT>::operator+(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	GUnorderSet<KeyT, HashT, CompareT> set_copy(*this);
	set_copy.Unite(set);
	return set_copy;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator+=(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	return Unite(set);
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator+=(const KeyT &key)
{
	Insert(key);
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> GUnorderSet<KeyT, HashT, CompareT>::operator-(const GUnorderSet<KeyT, HashT, CompareT> &set) const
{
	GUnorderSet<KeyT, HashT, CompareT> set_copy(*this);
	for (GUnorderSet<KeyT, HashT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		set_copy.Remove(*citer);
	}
	return set_copy;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator-=(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	for (GUnorderSet<KeyT, HashT, CompareT>::ConstIterator citer = set.ConstBegin();
		citer != set.ConstEnd(); citer++)
	{
		Remove(*citer);
	}
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator-=(const KeyT &key)
{
	Remove(key);
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator>>(KeyT &key)
{
	key = First();
	Remove(key);
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator<<(const KeyT &key)
{
	Insert(key);
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator=(const GUnorderSet<KeyT, HashT, CompareT> &set)
{
	if (this == &set)
	{
		return *this;
	}
	m_tTable = set.m_tTable;
	return *this;
}

template<typename KeyT, typename HashT, typename CompareT>
GINLINE GUnorderSet<KeyT, HashT, CompareT> &GUnorderSet<KeyT, HashT, CompareT>::operator=(GUnorderSet<KeyT, HashT, CompareT> &&set)
{
	if (this == &set)
	{
		return *this;
	}
	m_tTable = GMove(set.m_tTable);
	return *this;
}

#endif // _CORE_UNORDER_SET_INLINE_
