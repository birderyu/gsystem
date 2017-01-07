#ifndef _CORE_HASH_TABLE_INLINE_
#define _CORE_HASH_TABLE_INLINE_

#define CS_HASH_TABLE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define CS_HASH_TABLE_NODE_QUAL		GHashTableNode<KeyT, ValueT>
#define CS_HASH_TABLE_TEMPLATE		template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
#define CS_HASH_TABLE_QUAL			GHashTable<KeyT, ValueT, HashT, CompareT, NodeT>

CS_HASH_TABLE_NODE_TEMPLATE
inline CS_HASH_TABLE_NODE_QUAL::GHashTableNode(const KeyT &key,
	const ValueT &value,
	CS_HASH_TABLE_NODE_QUAL *next)
	: GNextNodeT<CS_HASH_TABLE_NODE_QUAL>(next)
	, GPairNodeT<KeyT, ValueT>(key, value)
{

}

CS_HASH_TABLE_TEMPLATE
inline CS_HASH_TABLE_QUAL::GHashTable(gsize module, gfloat factor, gbool allowRepeat)
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

CS_HASH_TABLE_TEMPLATE
inline CS_HASH_TABLE_QUAL::~GHashTable()
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

CS_HASH_TABLE_TEMPLATE
inline NodeT *CS_HASH_TABLE_QUAL::FirstNode()
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

CS_HASH_TABLE_TEMPLATE
inline const NodeT *CS_HASH_TABLE_QUAL::FirstNode() const
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

CS_HASH_TABLE_TEMPLATE
inline NodeT *CS_HASH_TABLE_QUAL::NextNode(NodeT *node)
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

CS_HASH_TABLE_TEMPLATE
inline const NodeT *CS_HASH_TABLE_QUAL::NextNode(NodeT *node) const
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

CS_HASH_TABLE_TEMPLATE
inline NodeT *CS_HASH_TABLE_QUAL::Find(const KeyT &key)
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

CS_HASH_TABLE_TEMPLATE
inline const NodeT *CS_HASH_TABLE_QUAL::Find(const KeyT &key) const
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

CS_HASH_TABLE_TEMPLATE
inline gbool CS_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename CS_HASH_TABLE_QUAL::Nodes &nodes)
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bAllowRepeat, nodes);
}

CS_HASH_TABLE_TEMPLATE
inline gbool CS_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename CS_HASH_TABLE_QUAL::ConstNodes &nodes) const
{
	gsize pos = IndexOf(key);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bAllowRepeat, nodes);
}

CS_HASH_TABLE_TEMPLATE
inline NodeT * CS_HASH_TABLE_QUAL::Insert(const KeyT &key, const ValueT &value)
{
	gsize n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		m_tBuckets[n] = new CsHashSlot();
	}
	if (!m_tBuckets[n])
	{
		return NULL;
	}
	gbool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, value, m_bAllowRepeat, realInsert);
	if (!pnode)
	{
		// ����ʧ��
		return NULL;
	}

	// �����ɹ�
	if (realInsert)
	{
		// ʵ�ʽ����˲������
		m_nSize++;
	}
	return pnode;
}

CS_HASH_TABLE_TEMPLATE
inline gvoid CS_HASH_TABLE_QUAL::Delete(const KeyT &key)
{
	gsize n = IndexOf(key);
	if (!m_tBuckets[n])
	{
		return;
	}
	gsize i = m_tBuckets[n]->Delete(key, m_bAllowRepeat);
	m_nSize -= i;
}

CS_HASH_TABLE_TEMPLATE
inline gsize CS_HASH_TABLE_QUAL::IndexOf(const KeyT &key) const
{
	guint h = m_fHash(key);
	h ^= (h >> 20) ^ (h >> 12);
	h = h ^ (h >> 7) ^ (h >> 4);
	return h & (m_nModule - 1);
}

#undef CS_HASH_TABLE_QUAL
#undef CS_HASH_TABLE_TEMPLATE
#undef CS_HASH_TABLE_NODE_QUAL
#undef CS_HASH_TABLE_NODE_TEMPLATE

#endif // _CORE_HASH_TABLE_INLINE_