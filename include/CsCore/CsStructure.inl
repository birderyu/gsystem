#ifndef _CORE_NODE_INLINE_
#define _CORE_NODE_INLINE_

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline CsSingleLinkedListNodeT<NodeT>::CsSingleLinkedListNodeT(NodeT *next)
: m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline CsDoubleLinkedListNodeT<NodeT>::CsDoubleLinkedListNodeT(NodeT *previous, NodeT *next)
: m_pPrevious(previous), m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline CsBinaryTreeNodeT<NodeT>::CsBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right)
: m_pParent(parent), m_pLeft(left), m_pRight(left)
{

}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::LeftSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pLeft;
	}
	return NULL;
}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::RightSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pRight;
	}
	return NULL;
}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::Next() const
{
	const NodeT *node = NULL;
	if (m_pRight)
	{
		node = m_pRight;
		while (node->m_pLeft)
		{
			node = node->m_pLeft;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return NULL;
		}
		node = (const NodeT *)this;
		NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pRight)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::Previous() const
{
	const NodeT *node = NULL;
	if (m_pLeft)
	{
		node = m_pLeft;
		while (node->m_pRight)
		{
			node = node->m_pRight;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return NULL;
		}
		node = (const NodeT *)this;
		NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pLeft)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::First() const
{
	if (!m_pLeft)
	{
		return (const NodeT *)this;
	}
	const NodeT *node = (const NodeT *)this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename NodeT>
inline NodeT *CsBinaryTreeNodeT<NodeT>::First()
{
	if (!m_pLeft)
	{
		return (NodeT *)this;
	}
	NodeT *node = (NodeT *)this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename NodeT>
inline const NodeT *CsBinaryTreeNodeT<NodeT>::Last() const
{
	if (!m_pRight)
	{
		return (const NodeT *)this;
	}
	const NodeT *node = (const NodeT *)this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

template<typename NodeT>
inline NodeT *CsBinaryTreeNodeT<NodeT>::Last()
{
	if (!m_pRight)
	{
		return (NodeT *)this;
	}
	NodeT *node = (NodeT *)this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

//////////////////////////////////////////////////////////////////////////
template<typename DataT>
inline CsDataNodeT<DataT>::CsDataNodeT(const DataT &data)
: m_tData(data)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValueT>
inline CsKeyValueNodeT<KeyT, ValueT>::CsKeyValueNodeT(const KeyT &key, const ValueT &value)
: m_tKey(key)
, m_tValue(value)
{

}

#endif // _CORE_NODE_INLINE_