// 有序Map
#ifndef _CORE_ORDER_MAP_H_
#define _CORE_ORDER_MAP_H_

#include "CsReadBlackTree.h"

template < typename KeyT,
	typename ValueT,
	typename CompareT>
class CsOrderMap;

/// 节点
template < typename KeyT,
	typename ValueT>
struct CsOrderMapNode 
	: public CsObject
{
	enum COLOR
	{
		COLOR_RED = 0,
		COLOR_BLACK = 1
	};
	KeyT m_tKey;								// 数据，需要由外部去析构，否则可能造成内存泄露
	ValueT m_tValue;							// 数据，需要由外部去析构，否则可能造成内存泄露
	CsOrderMapNode<KeyT, ValueT> *m_pParent;		// 双亲
	CsOrderMapNode<KeyT, ValueT> *m_pLeft;		// 左孩子
	CsOrderMapNode<KeyT, ValueT> *m_pRight;		// 右孩子
	cs_byte m_nColor;

	CsOrderMapNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsOrderMapNode<KeyT, ValueT> *parent = NULL,
		CsOrderMapNode<KeyT, ValueT> *left = NULL,
		CsOrderMapNode<KeyT, ValueT> *right = NULL,
		COLOR color = COLOR_BLACK);
	~CsOrderMapNode();
	CsOrderMapNode<KeyT, ValueT> *Copy() const;
};

template<typename KeyT,
	typename ValueT,
	typename CompareT = CsCompareF<KeyT >>
class CsOrderMap :public CsObject
{
	typedef CsOrderMapNode<KeyT, ValueT> Node;
	typedef CsReadBlackTree<KeyT, CompareT, Node> Tree;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator(Node *node = NULL, Tree *tree = NULL)
			:m_pNode(node), m_pTree(tree)
		{

		}
		Iterator(const Iterator &iter)
			:m_pNode(iter.m_pNode), m_pTree(iter.m_pTree)
		{

		}
		inline const KeyT &Key() const { return node->m_tKey; }
		inline ValueT &Value() const { return node->m_tValue; }
		inline ValueT &operator*() const { return node->m_tValue; }
		inline ValueT *operator->() const { return &node->m_tValue; }
		inline cs_bool operator==(const Iterator &o) const { return node == o.node; }
		inline cs_bool operator!=(const Iterator &o) const { return node != o.node; }
		inline Iterator &operator++() 
		{
			if (m_pTree)
			{
				node = m_pTree->NextNode(node);
			}
			return *this;
		}
		inline Iterator &operator--()
		{
			if (m_pTree)
			{
				node = m_pTree->PreviousNode(node);
			}
			return *this;
		}
		inline Iterator &operator=(const Iterator &iter)
		{
			m_pNode = iter.m_pNode;
			m_pTree = iter.m_pTree;
		}

	private:
		Node *m_pNode;
		Tree *m_pTree;
	};

public:
	CsOrderMap();
	CsOrderMap(const CsOrderMap<KeyT, ValueT, CompareT> &map);

	cs_size_t Length() const
	{
		return 0;
	}
	cs_bool IsEmpty() const
	{
		return m_tTree.IsEmpty();
	}

	Iterator &GetValue(const KeyT &key)
	{
		return m_tTree.
	}
	const ValueT &GetValue(const KeyT &key) const;

	Iterator Insert(const KeyT &key, const ValueT &value)
	{
		Node node(key, value);
		Node *p = m_tTree.InsertByNode(node);
		return Iterator(p, &m_tTree);
	}

	cs_bool Contains(const KeyT &key) const
	{
		return m_tTree.Find(key) != NULL;
	}

	Iterator Remove(const KeyT &key)
	{
		Node *p = m_tTree.Delete(key);
		return Iterator(p);
	}

private:
	Tree m_tTree;
};

#endif // _CORE_ORDER_MAP_H_