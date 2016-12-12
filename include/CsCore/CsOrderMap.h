// ÓÐÐòMap
#ifndef _CORE_ORDER_MAP_H_
#define _CORE_ORDER_MAP_H_

#include "CsReadBlackTree.h"

#define CS_ORDER_MAPM_NODE_RED		CS_RED_BLACK_TREE_NODE_RED
#define CS_ORDER_MAPM_NODE_BLACK	CS_RED_BLACK_TREE_NODE_BLACK

template < typename KeyT,
	typename ValueT,
	typename CompareT>
class CsOrderMap;

/// ½Úµã
template < typename KeyT, typename ValueT>
struct CsOrderMapNode 
	: public CsBinaryTreeNodeT<CsOrderMapNode<KeyT, ValueT>>
	, public CsKeyValueNodeT<KeyT, ValueT>
	, public CsNewT<CsOrderMapNode<KeyT, ValueT>>
{
	cs_small m_nColor;

	CsOrderMapNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsOrderMapNode<KeyT, ValueT> *parent = NULL,
		CsOrderMapNode<KeyT, ValueT> *left = NULL,
		CsOrderMapNode<KeyT, ValueT> *right = NULL,
		cs_small color = CS_ORDER_MAPM_NODE_RED);
};

template<typename KeyT, typename ValueT,
	typename CompareT = CsCompareF<KeyT >>
class CsOrderMap 
	: public CsObject
{
	typedef CsOrderMapNode<KeyT, ValueT> Node;
	typedef CsReadBlackTree<KeyT, ValueT, CompareT, CsOrderMapNode<KeyT, ValueT>> Tree;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator(Node *node = NULL)
			:m_pNode(node)
		{

		}
		Iterator(const Iterator &iter)
			:m_pNode(iter.m_pNode)
		{

		}
		inline const KeyT &Key() const { return m_pNode->m_tKey; }
		inline ValueT &Value() const { return m_pNode->m_tValue; }
		inline ValueT &operator*() const { return m_pNode->m_tValue; }
		inline ValueT *operator->() const { return &m_pNode->m_tValue; }
		inline cs_bool operator==(const Iterator &o) const { return m_pNode == o.m_pNode; }
		inline cs_bool operator!=(const Iterator &o) const { return m_pNode != o.m_pNode; }
		inline Iterator &operator++() 
		{
			if (m_pNode)
			{
				m_pNode = m_pNode->Next();
			}
			return *this;
		}
		inline Iterator &operator--()
		{
			if (m_pNode)
			{
				m_pNode = m_pNode->Previous();
			}
			return *this;
		}
		inline Iterator &operator=(const Iterator &iter)
		{
			m_pNode = iter.m_pNode;
		}

	private:
		Node *m_pNode;
	};

public:
	CsOrderMap();
	CsOrderMap(const CsOrderMap<KeyT, ValueT, CompareT> &map);

	cs_size_t Size() const
	{
		return 0;
	}
	cs_bool IsEmpty() const
	{
		
	}

	Iterator GetValue(const KeyT &key)
	{
		Node *node = m_tTree.Find(key);
		return Iterator(node);
	}

	Iterator Insert(const KeyT &key, const ValueT &value)
	{
		Node *node = m_tTree.Insert(key, value);
		return Iterator(node);
	}

	cs_bool Contains(const KeyT &key) const
	{
		return m_tTree.Find(key) != NULL;
	}

	cs_void Remove(const KeyT &key)
	{
		m_tTree.Delete(key);
	}

private:
	Tree m_tTree;
	cs_size_t m_nSize;
};

#endif // _CORE_ORDER_MAP_H_