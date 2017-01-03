#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "CsHash.h"
#include "CsList.h"
#include "CsDynamicArray.h"
#include "CsStructure.h"

#define CS_HASH_DEFAULT_MODULE_SIZE		0x10
#define CS_HASH_MAX_MODULE_SIZE			0x40000000
#define CS_HASH_DEFAULT_LOAD_FACTOR		0.75f

// 一个默认的hash节点
template<typename KeyT, typename ValueT>
struct CsHashTableNode 
	: public CsNextNodeT<CsHashTableNode<KeyT, ValueT>>
	, public CsPairNodeT<KeyT, ValueT>
	, public CsNewT<CsHashTableNode<KeyT, ValueT>>
{
	CsHashTableNode(const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsHashTableNode<KeyT, ValueT> *next = NULL);
};

/// 哈希表
template<typename KeyT, typename ValueT,
	typename HashT = CsHashF<KeyT>,
	typename CompareT = CsEqualToF<KeyT>,
	typename NodeT = CsHashTableNode<KeyT, ValueT>>
class CsHashTable
	: public CsObject
{
public:
	// 哈希Node和Node的集合
	typedef NodeT Node;
	typedef CsList<NodeT *> Nodes;
	typedef CsList<const NodeT *> ConstNodes;

private:
	// 哈希冲突
	struct CsHashSlot 
		: public CsNewT<CsHashSlot>
	{
		NodeT *m_pHead;
		cs_size_t m_nSize;
		CompareT m_fCompare;

		CsHashSlot() :m_pHead(NULL), m_nSize(0) {}
		CsHashSlot(const CsHashSlot &slot) :m_pHead(slot.m_pHead), m_nSize(slot.m_nSize)
		~CsHashSlot() { Free(); }

		CsHashSlot &operator=(const CsHashSlot &slot)
		{
			m_pHead = slot.m_pHead;
			m_nSize = slot.m_nSize;
			return *this;
		}

		cs_void Free()
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
		cs_size_t Size()
		{
			return m_nSize;
		}
		cs_bool IsEmpty()
		{
			return m_pHead == NULL || m_nSize == 0;
		}
		
		cs_bool Search(const KeyT &key, cs_bool allowRepeat, Nodes &nodes)
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
		cs_bool Search(const KeyT &key, cs_bool allowRepeat, ConstNodes &nodes) const
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
		cs_bool Contains(const KeyT &key) const
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

		NodeT *Insert(const KeyT &key, const ValueT &value, cs_bool allowRepeat, cs_bool &realInsert)
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
		cs_size_t Delete(const KeyT &key, cs_bool allowRepeat)
		{
			if (!m_pHead)
			{
				return 0;
			}

			if (allowRepeat)
			{
				// allowRepeat = true，允许有重复元素
				cs_size_t node_size = 0;
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
		cs_bool DeleteAt(NodeT *node, NodeT *preNode)
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
	CsHashTable(cs_size_t module = CS_HASH_DEFAULT_MODULE_SIZE, 
		cs_float factor = CS_HASH_DEFAULT_LOAD_FACTOR,
		cs_bool allowRepeat = false);
	~CsHashTable();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	cs_bool Find(const KeyT &key, Nodes &nodes);
	cs_bool Find(const KeyT &key, ConstNodes &nodes) const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual cs_void Delete(const KeyT &key);

protected:
	virtual cs_size_t IndexOf(const KeyT &key) const;

private:
	cs_size_t m_nModule;
	cs_size_t m_nSize; // 实际元素的个数
	cs_float m_nFactor;	// 负载因子
	CsDynamicArray<CsHashSlot*> m_tBuckets;
	HashT m_fHash;
	cs_bool m_bAllowRepeat; // 是否允许重复
};

#include "CsHashTable.inl"

#undef CS_HASH_DEFAULT_LOAD_FACTOR
#undef CS_HASH_MAX_MODULE_SIZE
#undef CS_HASH_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_