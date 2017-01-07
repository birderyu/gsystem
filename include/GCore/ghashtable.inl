#ifndef _CORE_HASH_TABLE_INLINE_
#define _CORE_HASH_TABLE_INLINE_

#define G_HASH_TABLE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define G_HASH_TABLE_NODE_QUAL		GHashTableNode<KeyT, ValueT>
#define G_HASH_TABLE_TEMPLATE		template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
#define G_HASH_TABLE_QUAL			GHashTable<KeyT, ValueT, HashT, CompareT, NodeT>

G_HASH_TABLE_NODE_TEMPLATE
inline G_HASH_TABLE_NODE_QUAL::GHashTableNode(const KeyT &key,
	const ValueT &value,
	G_HASH_TABLE_NODE_QUAL *next)
	: GNextNodeT<G_HASH_TABLE_NODE_QUAL>(next)
	, GPairNodeT<KeyT, ValueT>(key, value)
{

}

G_HASH_TABLE_TEMPLATE
inline G_HASH_TABLE_QUAL::GHashTable(gsize module, gfloat factor, gbool allowRepeat)
: m_nModule(module), m_nFactor(factor), m_bAllowRepeat(allowRepeat), m_nSize(0)
{
	if (m_nModule < G_HASH_TABLE_DEFAULT_MODULE_SIZE)
	{
		m_nModule = G_HASH_TABLE_DEFAULT_MODULE_SIZE; // 1 << 4
	}
	else if (m_nModule > G_HASH_TABLE_MAX_MODULE_SIZE)
	{
		m_nModule = G_HASH_TABLE_MAX_MODULE_SIZE; // 1 << 30
	}
	else
	{
		for (gsize i = 5; i <= 30; i++)
		{
			gsize module = 1 << i;
			if (module >= m_nModule)
			{
				m_nModule = module;
				break;
			}
		}
	}

	if (m_nFactor <= 0)
	{
		m_nFactor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR;
	}

	m_tBuckets.Resize(m_nModule, NULL);
}

G_HASH_TABLE_TEMPLATE
inline G_HASH_TABLE_QUAL::~GHashTable()
{
	gsize len = m_tBuckets.Size();
	for (gsize i = 0; i < len; i++)
	{
		if (m_tBuckets[i])
		{
			delete m_tBuckets[i];
			m_tBuckets[i] = NULL;
		}
	}
}

G_HASH_TABLE_TEMPLATE
inline NodeT *G_HASH_TABLE_QUAL::FirstNode()
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	for (gsize i = 0; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

G_HASH_TABLE_TEMPLATE
inline const NodeT *G_HASH_TABLE_QUAL::FirstNode() const
{
	if (m_nSize <= 0)
	{
		return NULL;
	}
	for (gsize i = 0; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

G_HASH_TABLE_TEMPLATE
inline NodeT *G_HASH_TABLE_QUAL::NextNode(NodeT *node)
{
	if (!node)
	{
		return NULL;
	}
	if (node->m_pNext)
	{
		return node->m_pNext;
	}
	gsize n = IndexOf(node->m_tKey);
	for (gsize i = n + 1; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

G_HASH_TABLE_TEMPLATE
inline const NodeT *G_HASH_TABLE_QUAL::NextNode(NodeT *node) const
{
	if (!node)
	{
		return NULL;
	}
	if (node->m_pNext)
	{
		return node->m_pNext;
	}
	gsize n = IndexOf(node->m_tKey);
	for (gsize i = n + 1; i < m_nModule; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return NULL;
}

G_HASH_TABLE_TEMPLATE
inline NodeT *G_HASH_TABLE_QUAL::Find(const KeyT &key)
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

G_HASH_TABLE_TEMPLATE
inline const NodeT *G_HASH_TABLE_QUAL::Find(const KeyT &key) const
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

G_HASH_TABLE_TEMPLATE
inline gbool G_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename G_HASH_TABLE_QUAL::Nodes &nodes)
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bAllowRepeat, nodes);
}

G_HASH_TABLE_TEMPLATE
inline gbool G_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename G_HASH_TABLE_QUAL::ConstNodes &nodes) const
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bAllowRepeat, nodes);
}

G_HASH_TABLE_TEMPLATE
inline NodeT * G_HASH_TABLE_QUAL::Insert(const KeyT &key, const ValueT &value)
{
	gsize n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		m_tBuckets[n] = new GHashSlot();
	}
	if (!m_tBuckets[n])
	{
		return NULL;
	}
	gbool realInsert = false;
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
		m_nSize++;
	}
	return pnode;
}

G_HASH_TABLE_TEMPLATE
inline gvoid G_HASH_TABLE_QUAL::Delete(const KeyT &key)
{
	gsize n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		return;
	}
	gsize i = m_tBuckets[n]->Delete(key, m_bAllowRepeat);
	m_nSize -= i;
}

G_HASH_TABLE_TEMPLATE
inline gsize G_HASH_TABLE_QUAL::IndexOf(const KeyT &key) const
{
	guint h = m_fHash(key);
	h ^= (h >> 20) ^ (h >> 12);
	h = h ^ (h >> 7) ^ (h >> 4);
	return h & (m_nModule - 1);
}

#undef G_HASH_TABLE_QUAL
#undef G_HASH_TABLE_TEMPLATE
#undef G_HASH_TABLE_NODE_QUAL
#undef G_HASH_TABLE_NODE_TEMPLATE

#endif // _CORE_HASH_TABLE_INLINE_