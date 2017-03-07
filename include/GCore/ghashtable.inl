#ifndef _CORE_HASH_TABLE_INLINE_
#define _CORE_HASH_TABLE_INLINE_

#define G_HASH_TABLE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define G_HASH_TABLE_NODE_QUAL		GHashTableNode<KeyT, ValueT>
#define G_HASH_TABLE_TEMPLATE		template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT>
#define G_HASH_TABLE_QUAL			GHashTable<KeyT, ValueT, HashT, CompareT, NodeT>
#define G_HASH_TABLE_MODULE			(m_tBuckets.Size())

G_HASH_TABLE_NODE_TEMPLATE
GINLINE G_HASH_TABLE_NODE_QUAL::GHashTableNode(const KeyT &key,
	const ValueT &value,
	G_HASH_TABLE_NODE_QUAL *next)
	: GNextNodeT<G_HASH_TABLE_NODE_QUAL>(next)
	, GPairNodeT<KeyT, ValueT>(key, value)
{

}

G_HASH_TABLE_TEMPLATE
const typename G_HASH_TABLE_QUAL::Table G_HASH_TABLE_QUAL::m_gTable;

G_HASH_TABLE_TEMPLATE
const HashT G_HASH_TABLE_QUAL::m_fHash;

G_HASH_TABLE_TEMPLATE
const CompareT G_HASH_TABLE_QUAL::m_fCompare;

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL::GHashTable(gsize module, gfloat factor, gbool unique)
	: m_nFactor(factor)
	, m_bUnique(unique)
	, m_nSize(0)
	, m_nThreshold(0)
{
	if (m_nFactor <= 0)
	{
		m_nFactor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR;
	}

	// 根据初始的模值初始化哈希桶
	Inflate(module);
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL::GHashTable(const G_HASH_TABLE_QUAL &table)
	: m_nFactor(table.m_nFactor)
	, m_bUnique(table.m_bUnique)
	, m_nSize(table.m_nSize)
	, m_nThreshold(table.m_nThreshold)
{
	gsize module = table.m_tBuckets.Size();
	m_tBuckets.Resize(module, GNULL);
	for (gsize i = 0; i < module; i++)
	{
		if (GNULL != table.m_tBuckets[i])
		{
			m_tBuckets[i] = new GHashSlot;

			// 依次拷贝所有元素
			NodeT *node = table.m_tBuckets[i]->m_pHead;
			while (node)
			{
				NodeT *new_node = new NodeT(*node);
				new_node->m_pNext = m_tBuckets[i]->m_pHead;
				m_tBuckets[i]->m_pHead = new_node;

				node = node->m_pNext;
			}
		}
	}
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL::GHashTable(G_HASH_TABLE_QUAL &&table)
	: m_nFactor(table.m_nFactor)
	, m_bUnique(table.m_bUnique)
	, m_nSize(table.m_nSize)
	, m_nThreshold(table.m_nThreshold)
{
	gsize module = table.m_tBuckets.Size();
	m_tBuckets.Resize(module, GNULL);
	for (gsize i = 0; i < module; i++)
	{
		if (GNULL != table.m_tBuckets[i])
		{
			m_tBuckets[i] = table.m_tBuckets[i];
			table.m_tBuckets[i] = GNULL;
		}	
	}
	table.m_nSize = 0;
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL::~GHashTable()
{
	Dispose();
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL &G_HASH_TABLE_QUAL::operator=(const G_HASH_TABLE_QUAL &table)
{
	if (this == &table)
	{
		return *this;
	}
	Dispose();

	m_nFactor = table.m_nFactor;
	m_bUnique = table.m_bUnique;
	m_nSize = table.m_nSize;
	m_nThreshold = table.m_nThreshold;
	gsize module = table.m_tBuckets.Size();
	m_tBuckets.Resize(module, GNULL);
	for (gsize i = 0; i < module; i++)
	{
		if (GNULL != table.m_tBuckets[i])
		{
			m_tBuckets[i] = new GHashSlot;

			// 依次拷贝所有元素
			NodeT *node = table.m_tBuckets[i]->m_pHead;
			while (node)
			{
				NodeT *new_node = new NodeT(*node);
				new_node->m_pNext = m_tBuckets[i]->m_pHead;
				m_tBuckets[i]->m_pHead = new_node;

				node = node->m_pNext;
			}
		}
	}
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL &G_HASH_TABLE_QUAL::operator=(G_HASH_TABLE_QUAL &&table)
{
	if (this == &table)
	{
		return *this;
	}
	Dispose();

	m_nFactor = table.m_nFactor;
	m_bUnique = table.m_bUnique;
	m_nSize = table.m_nSize;
	m_nThreshold = table.m_nThreshold;
	gsize module = table.m_tBuckets.Size();
	m_tBuckets.Resize(module, GNULL);
	for (gsize i = 0; i < module; i++)
	{
		if (GNULL != table.m_tBuckets[i])
		{
			m_tBuckets[i] = table.m_tBuckets[i];
			table.m_tBuckets[i] = GNULL;
		}
	}
	table.m_nSize = 0;
}

G_HASH_TABLE_TEMPLATE
GINLINE gsize G_HASH_TABLE_QUAL::Size() const
{
	return m_nSize;
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::IsEmpty() const
{
	return m_nSize == 0;
}

G_HASH_TABLE_TEMPLATE
GINLINE gvoid G_HASH_TABLE_QUAL::Dispose()
{
	gsize size = m_tBuckets.Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GNULL != m_tBuckets[i])
		{
			delete m_tBuckets[i];
			m_tBuckets[i] = GNULL;
		}
	}
	m_nSize = 0;
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::Contains(const KeyT &key) const
{
	gsize pos = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Contains(key);
}

G_HASH_TABLE_TEMPLATE
GINLINE NodeT *G_HASH_TABLE_QUAL::FirstNode()
{
	if (m_nSize <= 0)
	{
		return GNULL;
	}
	gsize module = G_HASH_TABLE_MODULE;
	for (gsize i = 0; i < module; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return GNULL;
}

G_HASH_TABLE_TEMPLATE
GINLINE const NodeT *G_HASH_TABLE_QUAL::FirstNode() const
{
	if (m_nSize <= 0)
	{
		return GNULL;
	}
	gsize module = G_HASH_TABLE_MODULE;
	for (gsize i = 0; i < module; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return GNULL;
}

G_HASH_TABLE_TEMPLATE
GINLINE NodeT *G_HASH_TABLE_QUAL::NextNode(NodeT *node)
{
	if (!node)
	{
		return GNULL;
	}
	if (node->m_pNext)
	{
		return node->m_pNext;
	}

	gsize module = G_HASH_TABLE_MODULE;
	gsize n = IndexOf(node->m_tKey, module);
	for (gsize i = n + 1; i < module; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return GNULL;
}

G_HASH_TABLE_TEMPLATE
GINLINE const NodeT *G_HASH_TABLE_QUAL::NextNode(const NodeT *node) const
{
	if (!node)
	{
		return GNULL;
	}
	if (node->m_pNext)
	{
		return node->m_pNext;
	}

	gsize module = G_HASH_TABLE_MODULE;
	gsize n = IndexOf(node->m_tKey, module);
	for (gsize i = n + 1; i < module; i++)
	{
		if (m_tBuckets[i] && m_tBuckets[i]->m_nSize >= 0 && m_tBuckets[i]->m_pHead)
		{
			return m_tBuckets[i]->m_pHead;
		}
	}
	return GNULL;
}

G_HASH_TABLE_TEMPLATE
GINLINE NodeT *G_HASH_TABLE_QUAL::Find(const KeyT &key)
{
	gsize pos = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[pos])
	{
		return GNULL;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

G_HASH_TABLE_TEMPLATE
GINLINE const NodeT *G_HASH_TABLE_QUAL::Find(const KeyT &key) const
{
	gsize pos = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[pos])
	{
		return GNULL;
	}
	return m_tBuckets[pos]->SearchFirst(key);
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename G_HASH_TABLE_QUAL::Nodes &nodes)
{
	gsize pos = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bUnique, nodes);
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::Find(const KeyT &key, 
	typename G_HASH_TABLE_QUAL::ConstNodes &nodes) const
{
	gsize pos = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[pos])
	{
		return false;
	}
	return m_tBuckets[pos]->Search(key, m_bUnique, nodes);
}

G_HASH_TABLE_TEMPLATE
GINLINE NodeT *G_HASH_TABLE_QUAL::Insert(const KeyT &key, const ValueT &value)
{
	if (m_nSize >= m_nThreshold)
	{
		// 扩容
		Inflate(2 * m_nSize);
	}

	gsize n = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[n])
	{
		m_tBuckets[n] = new GHashSlot;
	}
	if (!m_tBuckets[n])
	{
		return GNULL;
	}
	gbool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, value, m_bUnique, realInsert);
	if (!pnode)
	{
		// 操作失败
		return GNULL;
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
GINLINE NodeT *G_HASH_TABLE_QUAL::Insert(const KeyT &key, ValueT &&value)
{
	if (m_nSize >= m_nThreshold)
	{
		// 扩容
		Inflate(2 * m_nSize);
	}

	gsize n = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[n])
	{
		m_tBuckets[n] = new GHashSlot;
	}
	if (!m_tBuckets[n])
	{
		return GNULL;
	}
	gbool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, GForward<ValueT>(value), m_bUnique, realInsert);
	if (!pnode)
	{
		// 操作失败
		return GNULL;
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
GINLINE gvoid G_HASH_TABLE_QUAL::Delete(const KeyT &key)
{
	gsize n = IndexOf(key, G_HASH_TABLE_MODULE);
	if (!m_tBuckets[n])
	{
		return;
	}
	gsize i = m_tBuckets[n]->Delete(key, m_bUnique);
	m_nSize -= i;
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::operator==(const G_HASH_TABLE_QUAL &table) const
{
	if (m_nSize != table.m_nSize)
	{
		return false;
	}

	gsize module = G_HASH_TABLE_MODULE;
	if (module != table.m_tBuckets.Size())
	{
		return false;
	}

	for (gsize i = 0; i < module; i++)
	{
		if (!HashSlotEquals(m_tBuckets[i], table.m_tBuckets[i]))
		{
			return false;
		}
	}
	return true;
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::operator!=(const G_HASH_TABLE_QUAL &table) const
{
	return !(*this == table);
}

G_HASH_TABLE_TEMPLATE
GINLINE gbool G_HASH_TABLE_QUAL::HashSlotEquals(const typename G_HASH_TABLE_QUAL::GHashSlot *slot1, 
	const typename G_HASH_TABLE_QUAL::GHashSlot *slot2) const
{
	if (GNULL == slot1 && GNULL == slot2)
	{
		return true;
	}
	else if (GNULL == slot1 || GNULL == slot2)
	{
		return false;
	}

	if (slot1->m_nSize != slot2->m_nSize)
	{
		return false;
	}

	NodeT *node1 = slot1->m_pHead;
	while (node1)
	{
		gbool contain = false;
		NodeT *node2 = slot2->m_pHead;
		while (node2)
		{
			if (GHashSlot::m_rCompare(node1->m_tKey, node2->m_tKey))
			{
				contain = true;
				break;
			}
			node2 = node2->m_pNext;
		}
		if (!contain)
		{
			return false;
		}
		node1 = node1->m_pNext;
	}

	NodeT *_node2 = slot2->m_pHead;
	while (_node2)
	{
		gbool contain = false;
		NodeT *_node1 = slot1->m_pHead;
		while (_node1)
		{
			if (GHashSlot::m_rCompare(node1->m_tKey, _node1->m_tKey))
			{
				contain = true;
				break;
			}
			_node1 = _node1->m_pNext;
		}
		if (!contain)
		{
			return false;
		}
		_node2 = _node2->m_pNext;
	}

	return true;
}

G_HASH_TABLE_TEMPLATE
GINLINE gvoid G_HASH_TABLE_QUAL::Inflate(gsize module)
{
	gsize new_module = RoundUpToPowerOf2(module);
	m_nThreshold = new_module * m_nFactor;
	if (m_nThreshold > G_HASH_TABLE_MAX_MODULE_SIZE + 1)
	{
		m_nThreshold = G_HASH_TABLE_MAX_MODULE_SIZE + 1;
	}

	GDynamicArray<GHashSlot*> buckets(new_module, GNULL);
	gsize old_module = G_HASH_TABLE_MODULE;
	for (gsize i = 0; i < old_module; i++)
	{
		if (GNULL != m_tBuckets[i])
		{
			NodeT *node = m_tBuckets[i]->m_pHead;
			NodeT *next_node = GNULL;
			while (node)
			{
				next_node = node->m_pNext;

				gsize new_pos = IndexOf(node->m_tKey, new_module);
				if (GNULL == buckets[new_pos])
				{
					buckets[new_pos] = new GHashSlot;
				}
				node->m_pNext = buckets[new_pos]->m_pHead;
				buckets[new_pos]->m_pHead = node;

				node = next_node;
			}
		}
	}
	m_tBuckets = GMove(buckets);
}

G_HASH_TABLE_TEMPLATE
GINLINE gsize G_HASH_TABLE_QUAL::RoundUpToPowerOf2(gsize n) const
{
	if (n <= G_HASH_TABLE_DEFAULT_MODULE_SIZE)
	{
		return G_HASH_TABLE_DEFAULT_MODULE_SIZE; // 1 << 4
	}
	else if (n >= G_HASH_TABLE_MAX_MODULE_SIZE)
	{
		return G_HASH_TABLE_MAX_MODULE_SIZE; // 1 << 30
	}

	// HighestOneBit of n
	n--;
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n -= (n >> 1);

	// 将n*2
	return n << 1;

	/// 下面这个实现与n的大小有关，n越大效率越低下
	/*
	for (gsize i = 5; i <= 30; i++)
	{
		gsize module = 1 << i;
		if (module >= n)
		{
			n = module;
			break;
		}
	}
	return n;
	*/
}

G_HASH_TABLE_TEMPLATE
GINLINE gsize G_HASH_TABLE_QUAL::IndexOf(const KeyT &key, gsize module) const
{
	guint h = m_fHash(key);
	h ^= (h >> 20) ^ (h >> 12);
	h = h ^ (h >> 7) ^ (h >> 4);
	return h & (module - 1);
}

#undef G_HASH_TABLE_MODULE
#undef G_HASH_TABLE_QUAL
#undef G_HASH_TABLE_TEMPLATE
#undef G_HASH_TABLE_NODE_QUAL
#undef G_HASH_TABLE_NODE_TEMPLATE

#endif // _CORE_HASH_TABLE_INLINE_