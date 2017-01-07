#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "ghash.h"
#include "glist.h"
#include "gdynamicarray.h"
#include "gstructure.h"

#define G_HASH_TABLE_DEFAULT_MODULE_SIZE		0x10
#define G_HASH_TABLE_MAX_MODULE_SIZE			0x40000000
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
		GHashTableNode<KeyT, ValueT> *next = NULL);
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
	// 哈希Node和Node的集合
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

private:
	// 哈希冲突
	struct GHashSlot 
		: public GNewT<GHashSlot>
	{
		NodeT *m_pHead;
		gsize m_nSize;
		CompareT m_fCompare;

		GHashSlot() :m_pHead(NULL), m_nSize(0) {}
		GHashSlot(const GHashSlot &slot) :m_pHead(slot.m_pHead), m_nSize(slot.m_nSize)
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
			m_pHead = NULL;
			m_nSize = 0;
		}
		gsize Size()
		{
			return m_nSize;
		}
		gbool IsEmpty()
		{
			return m_pHead == NULL || m_nSize == 0;
		}
		
		gbool Search(const KeyT &key, gbool allowRepeat, Nodes &nodes)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (!allowRepeat)
					{
						// 不允许有重复元素
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
		gbool Search(const KeyT &key, gbool allowRepeat, ConstNodes &nodes) const
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
					if (!allowRepeat)
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
				if (m_fCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return NULL;
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
				if (m_fCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return NULL;
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
				if (m_fCompare(pNode->m_tKey, key))
				{
					return true;
				}
			}
			return false;
		}

		NodeT *Insert(const KeyT &key, const ValueT &value, gbool allowRepeat, gbool &realInsert)
		{
			if (allowRepeat)
			{
				// allowRepeat = true，允许有重复元素
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
				// allowRepeat = false，不允许有重复元素
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
		// 返回删除数据的数量，无则返回0
		gsize Delete(const KeyT &key, gbool allowRepeat)
		{
			if (!m_pHead)
			{
				return 0;
			}

			if (allowRepeat)
			{
				// allowRepeat = true，允许有重复元素
				gsize node_size = 0;
				NodeT *pNode = m_pHead;
				NodeT *preNode = NULL;
				while (pNode)
				{
					if (m_fCompare(pNode->m_tKey, key))
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
				// allowRepeat = false，不允许有重复元素
				NodeT *pNode = m_pHead;
				NodeT *preNode = NULL;
				while (pNode)
				{
					if (m_fCompare(pNode->m_tKey, key))
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
	};

public:
	GHashTable(gsize module = G_HASH_TABLE_DEFAULT_MODULE_SIZE, 
		gfloat factor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR,
		gbool allowRepeat = false);
	~GHashTable();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	gbool Find(const KeyT &key, Nodes &nodes);
	gbool Find(const KeyT &key, ConstNodes &nodes) const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual gvoid Delete(const KeyT &key);

protected:
	virtual gsize IndexOf(const KeyT &key) const;

private:
	gsize m_nModule;
	gsize m_nSize; // 实际元素的个数
	gfloat m_nFactor;	// 负载因子
	GDynamicArray<GHashSlot*> m_tBuckets;
	HashT m_fHash;
	gbool m_bAllowRepeat; // 是否允许重复
};

#include "ghashtable.inl"

#undef G_HASH_TABLE_DEFAULT_LOAD_FACTOR
#undef G_HASH_TABLE_MAX_MODULE_SIZE
#undef G_HASH_TABLE_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_