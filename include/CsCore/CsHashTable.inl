#ifndef _CORE_HASH_TABLE_INLINE_
#define _CORE_HASH_TABLE_INLINE_

template<typename KeyT, typename ValueT>
inline CsHashTableNode<KeyT, ValueT>::CsHashTableNode(const KeyT &key,
	const ValueT &value,
	CsHashTableNode<KeyT, ValueT> *next)
	: CsNextNodeT<CsHashTableNode<KeyT, ValueT>>(next)
	, CsKeyValueNodeT<KeyT, ValueT>(key, value)
{

}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::CsHashTable(cs_size_t module, cs_float factor, cs_bool allowRepeat)
: m_nModule(module), m_nFactor(factor), m_bAllowRepeat(allowRepeat), m_nLength(0)
{
	if (m_nModule < CS_HASH_DEFAULT_MODULE_SIZE)
	{
		m_nModule = CS_HASH_DEFAULT_MODULE_SIZE; // 1 << 4
	}
	else if (m_nModule > CS_HASH_MAX_MODULE_SIZE)
	{
		m_nModule = CS_HASH_MAX_MODULE_SIZE; // 1 << 30
	}
	else
	{
		for (cs_size_t i = 5; i <= 30; i++)
		{
			cs_size_t module = 1 << i;
			if (module >= m_nModule)
			{
				m_nModule = module;
				break;
			}
		}
	}

	if (m_nFactor <= 0)
	{
		m_nFactor = CS_HASH_DEFAULT_LOAD_FACTOR;
	}

	m_tBuckets.Resize(m_nModule, NULL);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::~CsHashTable()
{
	cs_size_t len = m_tBuckets.Size();
	for (cs_size_t i = 0; i < len; i++)
	{
		if (m_tBuckets[i])
		{
			delete m_tBuckets[i];
			m_tBuckets[i] = NULL;
		}
	}
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline NodeT *CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::FirstNode() const
{
	if (m_nLength <= 0)
	{
		return NULL;
	}
	for (cs_size_t i = 0; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nLength >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline NodeT *CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::NextNode(NodeT *node) const
{
	if (!node)
	{
		return NULL;
	}
	if (node->m_pNext)
	{
		return node->m_pNext;
	}
	cs_size_t n = IndexOf(node->m_tKey);
	for (cs_size_t i = n + 1; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nLength >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline NodeT * CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::Insert(const KeyT &key, const ValueT &value)
{
	cs_size_t n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		m_tBuckets[n] = new CsHashSlot<KeyT, ValueT, CompareT, NodeT>();
	}
	if (!m_tBuckets[n])
	{
		return NULL;
	}
	cs_bool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, value, m_bAllowRepeat, realInsert);
	if (!pnode)
	{
		// 操作失败
		return NULL;
	}

	// 操作成功
	if (realInsert)
	{
		// 实际进行了插入操作
		m_nLength++;
	}
	return pnode;
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline NodeT * CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::Find(const KeyT &key) const
{
	cs_size_t n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		return false;
	}
	return m_tBuckets[n]->Search(key);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline cs_bool CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::Find(const KeyT &key, CsHashNodes<NodeT> &nodes) const
{
	cs_size_t n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		return false;
	}
	return m_tBuckets[n]->Search(key, m_bAllowRepeat, nodes);
}

template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
inline cs_size_t CsHashTable<KeyT, ValueT, HashT, CompareT, NodeT>::IndexOf(const KeyT &key) const
{
	cs_uint h = m_fHash(key);
	h ^= (h >> 20) ^ (h >> 12);
	h = h ^ (h >> 7) ^ (h >> 4);
	return h & (m_nModule - 1);
}

#endif // _CORE_HASH_TABLE_INLINE_