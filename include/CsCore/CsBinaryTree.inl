#ifndef _CORE_BINARY_TREE_INLINE_
#define _CORE_BINARY_TREE_INLINE_

inline CsBinaryTreeNode::CsBinaryTreeNode(CsBinaryTreeNode *parent, CsBinaryTreeNode *left, CsBinaryTreeNode *right)
: CsBinaryTreeNodeT<CsBinaryTreeNode>(parent, left, right)
{

}

template<typename NodeT>
inline CsBinaryTree<NodeT>::CsBinaryTree(NodeT *pRoot)
: m_pRoot(pRoot)
{

}

template<typename NodeT>
inline CsBinaryTree<NodeT>::CsBinaryTree(const CsBinaryTree<NodeT> &tTree)
: m_pRoot(NULL)
{
	CopyFrom(tTree);
}

template<typename NodeT>
inline CsBinaryTree<NodeT>::~CsBinaryTree()
{
	Destroy();
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::SetRoot(NodeT *pNode)
{
	if (!m_pRoot)
	{
		Destroy();
	}
	m_pRoot = pNode;
}

template<typename NodeT>
inline CsBinaryTree<NodeT>& CsBinaryTree<NodeT>::operator=(const CsBinaryTree<NodeT> &tTree)
{
	CopyFrom(tTree);
	return *this;
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::CopyFrom(const CsBinaryTree<NodeT> &tTree)
{
	if (this == &tTree)
	{
		return;
	}
	if (m_pRoot != NULL)
	{
		Destroy();
	}
	if (NULL != tTree.m_pRoot)
	{
		// µÝ¹é¿½±´
		m_pRoot = CopySubTree(tTree.m_pRoot);
	}
	else
	{
		m_pRoot = NULL;
	}
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::Destroy()
{
	DestroySubTree(m_pRoot);
	m_pRoot = NULL;
}

template<typename NodeT>
inline cs_bool CsBinaryTree<NodeT>::IsEmpty() const
{
	return NULL == m_pRoot;
}

template<typename NodeT>
inline NodeT*& CsBinaryTree<NodeT>::Root()
{
	return *(&(m_pRoot));
}

template<typename NodeT>
inline NodeT* CsBinaryTree<NodeT>::Root() const
{
	return m_pRoot;
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::PreOrderTraverse(funtype fVisit) const
{
	PreOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::InOrderTraverse(funtype fVisit) const
{
	InOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::PostOrderTraverse(funtype fVisit) const
{
	PostOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline cs_size_t CsBinaryTree<NodeT>::NodeCount() const
{
	cs_size_t unCount = 0;
	NodeCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
inline cs_size_t CsBinaryTree<NodeT>::LeafCount() const
{
	cs_size_t unCount = 0;
	LeafCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
inline cs_size_t CsBinaryTree<NodeT>::Depth() const
{
	return Depth(m_pRoot);
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::DestroySubTree(NodeT *node)
{
	if (node)
	{
		DestroySubTree(node->m_pLeft);
		DestroySubTree(node->m_pRight);
		delete node;
	}
}

template<typename NodeT>
inline NodeT *CsBinaryTree<NodeT>::CopySubTree(NodeT *node)
{
	if (!node)
	{
		return NULL;
	}
	NodeT *node_new = new NodeT(*node);
	node_new->m_pLeft = CopySubTree(node->m_pLeft);
	node_new->m_pRight = CopySubTree(node->m_pRight);
	return node_new;
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::PreOrderTraverse(const NodeT *node, funtype fVisit) const
{
	if (node)
	{
		if (fVisit)
		{
			fVisit(*node);
		}
		PreOrderTraverse(node->m_pLeft, fVisit);
		PreOrderTraverse(node->m_pRight, fVisit);
	}
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::InOrderTraverse(const NodeT *node, funtype fVisit) const
{
	if (node)
	{
		InOrderTraverse(node->m_pLeft, fVisit);
		if (fVisit)
		{
			fVisit(*node);
		}
		InOrderTraverse(node->m_pRight, fVisit);
	}
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::PostOrderTraverse(const NodeT *node, funtype fVisit) const
{
	if (node)
	{
		PostOrderTraverse(node->m_pLeft, fVisit);
		PostOrderTraverse(node->m_pRight, fVisit);
		if (fVisit)
		{
			fVisit(*node);
		}
	}
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::NodeCount(const NodeT *node, cs_size_t &unCount) const
{
	if (NULL == node)
	{
		unCount = 0;
	}
	else if ((!node->m_pLeft) && (!node->m_pRight))
	{
		unCount = 1;
	}
	else
	{
		cs_size_t unLeftCount = 0;
		cs_size_t unRightCount = 0;
		NodeCount(node->m_pLeft, unLeftCount);
		NodeCount(node->m_pRight, unRightCount);
		unCount = 1 + unLeftCount + unRightCount;
	}
}

template<typename NodeT>
inline cs_void CsBinaryTree<NodeT>::LeafCount(const NodeT *node, cs_size_t &unCount) const
{
	if (node)
	{
		if ((!node->m_pLeft) && (!node->m_pRight))
		{
			++unCount;
		}
		LeafCount(node->m_pLeft, unCount);
		LeafCount(node->m_pRight, unCount);
	}
}

template<typename NodeT>
inline cs_size_t CsBinaryTree<NodeT>::Depth(const NodeT *node) const
{
	cs_size_t unDepthLeft;
	cs_size_t unDepthRight;

	if (node)
	{
		unDepthLeft = Depth(node->m_pLeft);
		unDepthRight = Depth(node->m_pRight);
		return 1 + (unDepthLeft > unDepthRight ? unDepthLeft : unDepthRight);
	}

	return 0;
}

#endif // _CORE_BINARY_TREE_INLINE_H_