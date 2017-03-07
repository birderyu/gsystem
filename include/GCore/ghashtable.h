#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "ghash.h"
#include "glist.h"
#include "gdynamicarray.h"
#include "gstructure.h"
#include "gnocopyable.h"

#define G_HASH_TABLE_DEFAULT_MODULE_SIZE		0x10
#define G_HASH_TABLE_MAX_MODULE_SIZE			0x40000000 // 2 30
#define G_HASH_TABLE_DEFAULT_LOAD_FACTOR		0.75f

// 一个默认的hash节点
template<typename KeyT, typename ValueT>
struct GHashTableNode 
	: public GNextNodeT<GHashTableNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GHashTableNode<KeyT, ValueT>>
{
	GHashTableNode(const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GHashTableNode<KeyT, ValueT> *next = GNULL);
};

/// 哈希表
template<typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>,
	typename NodeT = GHashTableNode<KeyT, ValueT>>
class GHashTable
	: public GObject
{
public:
	typedef GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> Table;
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

private:
	static const Table m_gTable;

private:
	// 哈希冲突
	// 不允许拷贝
	class GHashSlot
		: public GNewT<GHashSlot>
		, private GNocopyable
	{
	public:
		NodeT *m_pHead;
		gsize m_nSize;

		GHashSlot() 
			: m_pHead(GNULL), m_nSize(0), m_rCompare(m_gTable.m_fCompare) {}
		~GHashSlot() { Free(); }

		GHashSlot &operator=(const GHashSlot &slot)
		{
			m_pHead = slot.m_pHead;
			m_nSize = slot.m_nSize;
			return *this;
		}

		gvoid Free()
		{
			if (!m_pHead)
			{
				return;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				m_pHead = pNode;
				pNode = pNode->m_pNext;
				delete m_pHead;
			}
			m_pHead = GNULL;
			m_nSize = 0;
		}
		gsize Size()
		{
			return m_nSize;
		}
		gbool IsEmpty()
		{
			return m_pHead == GNULL || m_nSize == 0;
		}
		
		gbool Search(const KeyT &key, gbool unique, Nodes &nodes)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (unique)
					{
						// 不允许有重复元素
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
		gbool Search(const KeyT &key, gbool unique, ConstNodes &nodes) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (unique)
					{
						// 不允许有重复元素
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
				
		// 只搜索第一个
		NodeT *SearchFirst(const KeyT &key)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return GNULL;
		}
		const NodeT *SearchFirst(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return GNULL;
		}
		gbool Contains(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_rCompare(pNode->m_tKey, key))
				{
					return true;
				}
			}
			return false;
		}

		NodeT *Insert(const KeyT &key, const ValueT &value, gbool unique, gbool &realInsert)
		{
			if (!unique)
			{
				// unique = false，允许有重复元素
				// 直接插入到队首
				NodeT *node = new NodeT(key, value);
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nSize++;
				realInsert = true;
				return node; // 操作成功
			}
			else
			{
				// unique = true，不允许有重复元素
				NodeT *pnode = SearchFirst(key);
				if (!pnode)
				{
					// 不存在，插入到队首
					NodeT *node = new NodeT(key, value);
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nSize++;
					realInsert = true;
					return node;
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
		NodeT *Insert(const KeyT &key, ValueT &&value, gbool unique, gbool &realInsert)
		{
			if (!unique)
			{
				// unique = false，允许有重复元素
				// 直接插入到队首
				NodeT *node = new NodeT(key, GForward<ValueT>(value));
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nSize++;
				realInsert = true;
				return node; // 操作成功
			}
			else
			{
				// unique = true，不允许有重复元素
				NodeT *pnode = SearchFirst(key);
				if (!pnode)
				{
					// 不存在，插入到队首
					NodeT *node = new NodeT(key, GForward<ValueT>(value));
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nSize++;
					realInsert = true;
					return node;
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
		// 返回删除数据的数量，无则返回0
		gsize Delete(const KeyT &key, gbool unique)
		{
			if (!m_pHead)
			{
				return 0;
			}

			if (!unique)
			{
				// unique = false，允许有重复元素
				gsize node_size = 0;
				NodeT *pNode = m_pHead;
				NodeT *preNode = GNULL;
				while (pNode)
				{
					if (m_rCompare(pNode->m_tKey, key))
					{
						// 删除节点
						if (DeleteAt(pNode, preNode))
						{
							node_size++;
						}
						pNode = preNode->m_pNext;
					}
					else
					{
						preNode = pNode;
						pNode = pNode->m_pNext;
					}
				}
				return node_size;
			}
			else
			{
				// unique = true，不允许有重复元素
				NodeT *pNode = m_pHead;
				NodeT *preNode = GNULL;
				while (pNode)
				{
					if (m_rCompare(pNode->m_tKey, key))
					{
						// 删除节点并返回
						if (DeleteAt(pNode, preNode))
						{
							return 1;
						}
					}
					preNode = pNode;
					pNode = pNode->m_pNext;
				}
				return 0;
			}
			return 0;
		}

		// node :待删除的节点
		// preNode：待删除节点的前驱节点
		gbool DeleteAt(NodeT *node, NodeT *preNode)
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

		const CompareT &m_rCompare;
	};

public:
	GHashTable(gsize module = G_HASH_TABLE_DEFAULT_MODULE_SIZE, 
		gfloat factor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR,
		gbool unique = true);
	GHashTable(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table);
	GHashTable(GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &&table);
	~GHashTable();

	GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &operator=(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table);
	GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &operator=(GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &&table);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Dispose();

	gbool Contains(const KeyT &key) const;

	NodeT *FirstNode();
	const NodeT *FirstNode() const;

	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(const NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	gbool Find(const KeyT &key, Nodes &nodes);
	gbool Find(const KeyT &key, ConstNodes &nodes) const;

	NodeT *Insert(const KeyT &key, const ValueT &value);
	NodeT *Insert(const KeyT &key, ValueT &&value);
	gvoid Delete(const KeyT &key);

	gbool operator==(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table) const;
	gbool operator!=(const GHashTable<KeyT, ValueT, HashT, CompareT, NodeT> &table) const;

protected:
	/// 判断两个GHashSlot是否相等
	gbool HashSlotEquals(const GHashSlot *slot1, const GHashSlot *slot2) const;

	/// 表扩容
	gvoid Inflate(gsize module);

	/// 返回 >= n的最小2的n次方值，如n = 30，则返回32
	/// 特殊处理：令这个值一定位于2的4次方与2的30次方之间
	gsize RoundUpToPowerOf2(gsize module) const;

	/// 获取key的下标
	gsize IndexOf(const KeyT &key, gsize module) const;

private:
	gfloat m_nFactor;						// 负载因子，一旦确定了就不能修改
	gbool m_bUnique;						// 主键是否唯一，一旦确定了就不能修改

	gsize m_nSize;							// 实际元素的个数
	gsize m_nThreshold;						// 扩容阈值，其值等于模值*m_nFactor，为了减少浮点运算，将这个值存储下来
	GDynamicArray<GHashSlot*> m_tBuckets;	// 哈希桶
	static const HashT m_fHash;
	static const CompareT m_fCompare;
};

#include "ghashtable.inl"

#undef G_HASH_TABLE_DEFAULT_LOAD_FACTOR
#undef G_HASH_TABLE_MAX_MODULE_SIZE
#undef G_HASH_TABLE_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_