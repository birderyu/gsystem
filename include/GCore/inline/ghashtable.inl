#ifndef _CORE_HASH_TABLE_INLINE_
#define _CORE_HASH_TABLE_INLINE_

#define G_HASH_TABLE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define G_HASH_TABLE_NODE_QUAL		GHashTableNode<KeyT, ValueT>
#define G_HASH_TABLE_SLOT_TEMPLATE	template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
#define G_HASH_TABLE_SLOT_QUAL		GListSlot<KeyT, ValueT, CompareT, NodeT>
#define G_HASH_TABLE_TEMPLATE		template<typename KeyT, typename ValueT, typename HashT, typename CompareT, typename NodeT, typename SlotT>
#define G_HASH_TABLE_QUAL			GHashTable<KeyT, ValueT, HashT, CompareT, NodeT, SlotT>

#define G_HASH_TABLE_MODULE			(m_tBuckets.Size())

namespace gsystem { // gsystem

G_HASH_TABLE_NODE_TEMPLATE GINLINE
G_HASH_TABLE_NODE_QUAL::GHashTableNode(const KeyT &key, 
	const ValueT &value,
	G_HASH_TABLE_NODE_QUAL *next)
	: GNextNodeT<GHashTableNode<KeyT, ValueT>>(next)
	, GPairNodeT<KeyT, ValueT>(key, value)
{

}

G_HASH_TABLE_NODE_TEMPLATE GINLINE
G_HASH_TABLE_NODE_QUAL::GHashTableNode(const KeyT &key, 
	ValueT &&value,
	G_HASH_TABLE_NODE_QUAL *next)
	: GNextNodeT<GHashTableNode<KeyT, ValueT>>(next)
	, GPairNodeT<KeyT, ValueT>(key, GForward<ValueT>(value))
{

}

G_HASH_TABLE_SLOT_TEMPLATE
const CompareT G_HASH_TABLE_SLOT_QUAL::m_fCompare;

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL::GListSlot(gbool unique)
	: m_pHead(GNULL), m_nSize(0), m_bUnique(unique)
{

}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL::GListSlot(const G_HASH_TABLE_SLOT_QUAL &slot)
	: m_pHead(GNULL), m_nSize(slot.m_nSize), m_bUnique(slot.m_bUnique)
{
	if (slot.IsEmpty())
	{
		return;
	}
	
	m_pHead = new NodeT(slot->m_pHead->m_tKey, slot->m_pHead->m_tValue);
	NodeT *cur_node = m_pHead;
	NodeT *copy_node = slot->m_pFirst->m_pNext;
	while (copy_node) {
		cur_node->m_pNext = new NodeT(copy_node->m_tKey, copy_node->m_tValue);
		
		cur_node = cur_node->m_pNext;
		copy_node = copy_node->m_pNext;
	}
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL::GListSlot(G_HASH_TABLE_SLOT_QUAL &&slot)
	: m_pHead(slot.m_pHead), m_nSize(slot.m_nSize), m_bUnique(slot.m_bUnique)
{
	slot.m_pHead = GNULL;
	slot.m_nSize = 0;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL::~GListSlot()
{
	Destroy();
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL &G_HASH_TABLE_SLOT_QUAL::operator=(const G_HASH_TABLE_SLOT_QUAL &slot)
{
	if (this == &slot)
	{
		return *this;
	}

	Destroy();

	m_nSize = slot.m_nSize;
	m_bUnique = slot.m_bUnique;

	if (slot.IsEmpty())
	{
		return;
	}

	m_pHead = new NodeT(slot->m_pHead->m_tKey, slot->m_pHead->m_tValue);
	NodeT *cur_node = m_pHead;
	NodeT *copy_node = slot->m_pHead->m_pNext;
	while (copy_node) {
		cur_node->m_pNext = new NodeT(copy_node->m_tKey, copy_node->m_tValue);

		cur_node = cur_node->m_pNext;
		copy_node = copy_node->m_pNext;
	}

	return *this;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
G_HASH_TABLE_SLOT_QUAL &G_HASH_TABLE_SLOT_QUAL::operator=(G_HASH_TABLE_SLOT_QUAL &&slot)
{
	if (this == &slot)
	{
		return *this;
	}

	Destroy();

	m_pHead = slot.m_pHead;
	m_nSize = slot.m_nSize;
	m_bUnique = slot.m_bUnique;

	slot.m_pHead = GNULL;
	slot.m_nSize = 0;

	return *this;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gsize G_HASH_TABLE_SLOT_QUAL::Size() const
{
	return m_nSize;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::IsEmpty() const
{
	return m_pHead == GNULL && m_nSize <= 0;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::FirstNode()
{
	return m_pHead;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
const NodeT *G_HASH_TABLE_SLOT_QUAL::FirstNode() const
{
	return m_pHead;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::NextNode(NodeT *node)
{
	return node->m_pNext;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
const NodeT *G_HASH_TABLE_SLOT_QUAL::NextNode(const NodeT *node) const
{
	return node->m_pNext;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::Contains(const KeyT &key) const
{
	if (!m_pHead)
	{
		return false;
	}
	NodeT *node = m_pHead;
	while (node)
	{
		if (m_fCompare(node->m_tKey, key))
		{
			return true;
		}
	}
	return false;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::Search(const KeyT &key, typename G_HASH_TABLE_SLOT_QUAL::Nodes &nodes)
{
	if (!m_pHead)
	{
		return false;
	}
	NodeT *node = m_pHead;
	while (node)
	{
		if (m_fCompare(node->m_tKey, key))
		{
			nodes.PushBack(node);
			if (m_bUnique)
			{
				// 不允许有重复元素
				return true;
			}
		}
		node = node->m_pNext;
	}
	return !nodes.IsEmpty();
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::Search(const KeyT &key, typename G_HASH_TABLE_SLOT_QUAL::ConstNodes &nodes) const
{
	if (!m_pHead)
	{
		return false;
	}
	const NodeT *pNode = m_pHead;
	while (pNode)
	{
		if (m_fCompare(pNode->m_tKey, key))
		{
			nodes.PushBack(pNode);
			if (m_bUnique)
			{
				// 不允许有重复元素
				return true;
			}
		}
		pNode = pNode->m_pNext;
	}
	return !nodes.IsEmpty();
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::SearchFirst(const KeyT &key)
{
	if (!m_pHead)
	{
		return false;
	}
	NodeT *node = m_pHead;
	while (node)
	{
		if (m_fCompare(node->m_tKey, key))
		{
			return node;
		}
		node = node->m_pNext;
	}
	return GNULL;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
const NodeT *G_HASH_TABLE_SLOT_QUAL::SearchFirst(const KeyT &key) const
{
	if (!m_pHead)
	{
		return false;
	}
	const NodeT *node = m_pHead;
	while (node)
	{
		if (m_fCompare(node->m_tKey, key))
		{
			return node;
		}
		node = node->m_pNext;
	}
	return GNULL;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::Insert(const KeyT &key, const ValueT &value, gbool &realInsert)
{
	if (!m_bUnique)
	{
		// 允许有重复元素，直接插入到队首
		realInsert = true;
		return InsertNode(new NodeT(key, value));
	}
	else
	{
		// 不允许有重复元素
		NodeT *pnode = SearchFirst(key);
		if (!pnode)
		{
			// 不存在，插入到队首
			realInsert = true;
			return InsertNode(new NodeT(key, value));
		}
		else
		{
			// 已存在，返回相同的节点
			pnode->m_tValue = value;
			realInsert = false;
			return pnode;
		}
	}
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::Insert(const KeyT &key, ValueT &&value, gbool &realInsert)
{
	if (!m_bUnique)
	{
		// 允许有重复元素，直接插入到队首
		realInsert = true;
		return InsertNode(new NodeT(key, GForward<ValueT>(value)));
	}
	else
	{
		// unique = true，不允许有重复元素
		NodeT *pnode = SearchFirst(key);
		if (!pnode)
		{
			// 不存在，插入到队首
			realInsert = true;
			return InsertNode(new NodeT(key, GForward<ValueT>(value)));
		}
		else
		{
			// 已存在，返回相同的节点
			pnode->m_tValue = GForward<ValueT>(value);
			realInsert = false;
			return pnode;
		}
	}
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gsize G_HASH_TABLE_SLOT_QUAL::Delete(const KeyT &key)
{
	if (!m_pHead)
	{
		return 0;
	}

	if (!m_bUnique)
	{
		// 允许有重复元素
		gsize node_size = 0;
		NodeT *node = m_pHead;
		NodeT *preNode = GNULL;
		while (node)
		{
			if (m_fCompare(node->m_tKey, key))
			{
				// 删除节点
				if (DeleteAt(node, preNode))
				{
					node_size++;
				}
				node = preNode->m_pNext;
			}
			else
			{
				preNode = node;
				node = node->m_pNext;
			}
		}
		return node_size;
	}
	else
	{
		// 不允许有重复元素
		NodeT *node = m_pHead;
		NodeT *preNode = GNULL;
		while (node)
		{
			if (m_fCompare(node->m_tKey, key))
			{
				// 删除节点并返回
				if (DeleteAt(node, preNode))
				{
					return 1;
				}
			}
			preNode = node;
			node = node->m_pNext;
		}
	}
	return 0;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::Equals(const GHashTableSlot<KeyT, ValueT, NodeT> &slot) const
{
	if (this == &slot)
	{
		return true;
	}

	if (m_nSize != slot.Size())
	{
		return false;
	}

	const NodeT *node1 = m_pHead;
	while (node1)
	{
		gbool contain = false;
		const NodeT *node2 = slot.FirstNode();
		while (node2)
		{
			if (m_fCompare(node1->m_tKey, node2->m_tKey))
			{
				contain = true;
				break;
			}
			node2 = slot.NextNode(node2);
		}
		if (!contain)
		{
			return false;
		}
		node1 = node1->m_pNext;
	}

	const NodeT *_node2 = slot.FirstNode();
	while (_node2)
	{
		gbool contain = false;
		const NodeT *_node1 = m_pHead;
		while (_node1)
		{
			if (m_fCompare(node1->m_tKey, _node1->m_tKey))
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
		_node2 = NextNode(_node2);
	}

	return true;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::Equals(const G_HASH_TABLE_SLOT_QUAL &slot) const
{
	if (this == &slot)
	{
		return true;
	}

	if (m_nSize != slot.m_nSize)
	{
		return false;
	}

	const NodeT *node1 = m_pHead;
	while (node1)
	{
		gbool contain = false;
		const NodeT *node2 = slot.m_pHead;
		while (node2)
		{
			if (m_fCompare(node1->m_tKey, node2->m_tKey))
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

	const NodeT *_node2 = slot.m_pHead;
	while (_node2)
	{
		gbool contain = false;
		const NodeT *_node1 = m_pHead;
		while (_node1)
		{
			if (m_fCompare(node1->m_tKey, _node1->m_tKey))
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

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::InsertNode(NodeT *node)
{
	node->m_pNext = m_pHead;
	m_pHead = node;
	m_nSize++;
	return node;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
NodeT *G_HASH_TABLE_SLOT_QUAL::RemoveNode()
{
	if (m_pHead == GNULL)
	{
		return GNULL;
	}
	NodeT *node = m_pHead;
	m_pHead = node->m_pNext;
	node->m_pNext = GNULL;
	m_nSize--;
	return node;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gbool G_HASH_TABLE_SLOT_QUAL::DeleteAt(NodeT *node, NodeT *preNode)
{
	if (!node)
	{
		return false;
	}

	if (preNode)
	{
		preNode->m_pNext = node->m_pNext;
	}
	else
	{
		m_pHead = node->m_pNext;
	}

	delete node;
	m_nSize--;
	return true;
}

G_HASH_TABLE_SLOT_TEMPLATE GINLINE
gvoid G_HASH_TABLE_SLOT_QUAL::Destroy()
{
	if (!m_pHead)
	{
		return;
	}
	NodeT *node = m_pHead;
	while (node)
	{
		m_pHead = node;
		node = node->m_pNext;
		delete m_pHead;
	}
	m_pHead = GNULL;
	m_nSize = 0;
}

G_HASH_TABLE_TEMPLATE
const HashT G_HASH_TABLE_QUAL::m_fHash;

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
			m_tBuckets[i] = new SlotT(&table.m_tBuckets[i]);
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
	Destroy();
}

G_HASH_TABLE_TEMPLATE
GINLINE G_HASH_TABLE_QUAL &G_HASH_TABLE_QUAL::operator=(const G_HASH_TABLE_QUAL &table)
{
	if (this == &table)
	{
		return *this;
	}
	Destroy();

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
			m_tBuckets[i] = new SlotT(*table.m_tBuckets[i]);
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
	Destroy();

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
GINLINE gvoid G_HASH_TABLE_QUAL::Destroy()
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
		if (m_tBuckets[i] && !m_tBuckets[i]->IsEmpty())
		{
			return m_tBuckets[i]->FirstNode();
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
		if (m_tBuckets[i] && !m_tBuckets[i]->IsEmpty())
		{
			return m_tBuckets[i]->FirstNode();
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
	gsize module = G_HASH_TABLE_MODULE;
	gsize n = IndexOf(node->m_tKey, module);
	NodeT *next_node = m_tBuckets[n]->NextNode(node);
	if (next_node)
	{
		return next_node;
	}
	for (gsize i = n + 1; i < module; i++)
	{
		if (m_tBuckets[i] && !m_tBuckets[i]->IsEmpty())
		{
			return m_tBuckets[i]->FirstNode();
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
	gsize module = G_HASH_TABLE_MODULE;
	gsize n = IndexOf(node->m_tKey, module);
	const NodeT *next_node = m_tBuckets[n]->NextNode(node);
	if (next_node)
	{
		return next_node;
	}
	for (gsize i = n + 1; i < module; i++)
	{
		if (m_tBuckets[i] && !m_tBuckets[i]->IsEmpty())
		{
			return m_tBuckets[i]->FirstNode();
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
	return m_tBuckets[pos]->Search(key, nodes);
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
		m_tBuckets[n] = new SlotT(m_bUnique);
	}
	if (!m_tBuckets[n])
	{
		return GNULL;
	}
	gbool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, value, realInsert);
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
		m_tBuckets[n] = new SlotT(m_bUnique);
	}
	if (!m_tBuckets[n])
	{
		return GNULL;
	}
	gbool realInsert = false;
	NodeT *pnode = m_tBuckets[n]->Insert(key, GForward<ValueT>(value), realInsert);
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
GINLINE gbool G_HASH_TABLE_QUAL::HashSlotEquals(const SlotT *slot1, const SlotT *slot2) const
{
	if (GNULL == slot1 && GNULL == slot2)
	{
		return true;
	}
	else if (GNULL == slot1 || GNULL == slot2)
	{
		return false;
	}
	return slot1->Equals(&slot2);
}

G_HASH_TABLE_TEMPLATE
GINLINE 
gvoid G_HASH_TABLE_QUAL::Inflate(gsize module)
{
	gsize new_module = RoundUpToPowerOf2(module);
	m_nThreshold = new_module * m_nFactor;
	if (m_nThreshold > G_HASH_TABLE_MAX_MODULE_SIZE + 1)
	{
		m_nThreshold = G_HASH_TABLE_MAX_MODULE_SIZE + 1;
	}

	GDynamicArray<SlotT*> buckets(new_module, GNULL);
	gsize old_module = G_HASH_TABLE_MODULE;
	for (gsize i = 0; i < old_module; i++)
	{
		if (GNULL == m_tBuckets[i])
		{
			continue;
		}

		NodeT *node = m_tBuckets[i]->RemoveNode();
		while (node)
		{
			gsize new_pos = IndexOf(node->m_tKey, new_module);
			if (GNULL == buckets[new_pos])
			{
				buckets[new_pos] = new SlotT(m_bUnique);
			}
			buckets[new_pos]->InsertNode(node);
			node = m_tBuckets[i]->RemoveNode();
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

} // namespace gsystem

#undef G_HASH_TABLE_MODULE
#undef G_HASH_TABLE_QUAL
#undef G_HASH_TABLE_TEMPLATE
#undef G_HASH_TABLE_SLOT_QUAL
#undef G_HASH_TABLE_SLOT_TEMPLATE
#undef G_HASH_TABLE_NODE_QUAL
#undef G_HASH_TABLE_NODE_TEMPLATE

#endif // _CORE_HASH_TABLE_INLINE_