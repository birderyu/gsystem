#ifndef _CORE_STRUCTURE_INLINE_
#define _CORE_STRUCTURE_INLINE_

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline GNextNodeT<NodeT>::GNextNodeT(NodeT *next)
: m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline GPreviousNextNodeT<NodeT>::GPreviousNextNodeT(NodeT *previous, NodeT *next)
: m_pPrevious(previous), m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline GBinaryTreeNodeT<NodeT>::GBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right)
: m_pParent(parent), m_pLeft(left), m_pRight(left)
{

}

template<typename NodeT>
inline const NodeT *GBinaryTreeNodeT<NodeT>::LeftSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pLeft;
	}
	return NULL;
}

template<typename NodeT>
inline const NodeT *GBinaryTreeNodeT<NodeT>::RightSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pRight;
	}
	return NULL;
}

template<typename NodeT>
inline const NodeT *GBinaryTreeNodeT<NodeT>::Next() const
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
inline const NodeT *GBinaryTreeNodeT<NodeT>::Previous() const
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
inline const NodeT *GBinaryTreeNodeT<NodeT>::First() const
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
inline NodeT *GBinaryTreeNodeT<NodeT>::First()
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
inline const NodeT *GBinaryTreeNodeT<NodeT>::Last() const
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
inline NodeT *GBinaryTreeNodeT<NodeT>::Last()
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
inline GDataNodeT<DataT>::GDataNodeT(const DataT &data)
: m_tData(data)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
inline GChildNodeT<NodeT>::GChildNodeT(const NodeT *child)
: m_pChild(child)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValueT>
inline GPairNodeT<KeyT, ValueT>::GPairNodeT(const KeyT &key, const ValueT &value)
: m_tKey(key)
, m_tValue(value)
{

}

#endif // _CORE_STRUCTURE_INLINE_