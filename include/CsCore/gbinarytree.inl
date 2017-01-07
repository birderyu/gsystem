#ifndef _CORE_BINARY_TREE_INLINE_
#define _CORE_BINARY_TREE_INLINE_

inline GBinaryTreeNode::GBinaryTreeNode(GBinaryTreeNode *parent, GBinaryTreeNode *left, GBinaryTreeNode *right)
: GBinaryTreeNodeT<GBinaryTreeNode>(parent, left, right)
{

}

template<typename NodeT>
inline GBinaryTree<NodeT>::GBinaryTree(NodeT *pRoot)
: m_pRoot(pRoot)
{

}

template<typename NodeT>
inline GBinaryTree<NodeT>::GBinaryTree(const GBinaryTree<NodeT> &tTree)
: m_pRoot(NULL)
{
	CopyFrom(tTree);
}

template<typename NodeT>
inline GBinaryTree<NodeT>::~GBinaryTree()
{
	Destroy();
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::SetRoot(NodeT *pNode)
{
	if (!m_pRoot)
	{
		Destroy();
	}
	m_pRoot = pNode;
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::CopyFrom(const GBinaryTree<NodeT> &tTree)
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
inline gvoid GBinaryTree<NodeT>::Destroy()
{
	DestroySubTree(m_pRoot);
	m_pRoot = NULL;
}

template<typename NodeT>
inline gbool GBinaryTree<NodeT>::IsEmpty() const
{
	return NULL == m_pRoot;
}

template<typename NodeT>
inline NodeT*& GBinaryTree<NodeT>::Root()
{
	return *(&(m_pRoot));
}

template<typename NodeT>
inline NodeT* GBinaryTree<NodeT>::Root() const
{
	return m_pRoot;
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::PreOrderTraverse(funtype fVisit) const
{
	PreOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::InOrderTraverse(funtype fVisit) const
{
	InOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::PostOrderTraverse(funtype fVisit) const
{
	PostOrderTraverse(m_pRoot, fVisit);
}

template<typename NodeT>
inline gsize GBinaryTree<NodeT>::NodeCount() const
{
	gsize unCount = 0;
	NodeCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
inline gsize GBinaryTree<NodeT>::LeafCount() const
{
	gsize unCount = 0;
	LeafCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
inline gsize GBinaryTree<NodeT>::Depth() const
{
	return Depth(m_pRoot);
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::DestroySubTree(NodeT *node)
{
	if (node)
	{
		DestroySubTree(node->m_pLeft);
		DestroySubTree(node->m_pRight);
		delete node;
	}
}

template<typename NodeT>
inline NodeT *GBinaryTree<NodeT>::CopySubTree(NodeT *node)
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
inline gvoid GBinaryTree<NodeT>::PreOrderTraverse(const NodeT *node, funtype fVisit) const
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
inline gvoid GBinaryTree<NodeT>::InOrderTraverse(const NodeT *node, funtype fVisit) const
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
inline gvoid GBinaryTree<NodeT>::PostOrderTraverse(const NodeT *node, funtype fVisit) const
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
inline gvoid GBinaryTree<NodeT>::NodeCount(const NodeT *node, gsize &unCount) const
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
		gsize unLeftCount = 0;
		gsize unRightCount = 0;
		NodeCount(node->m_pLeft, unLeftCount);
		NodeCount(node->m_pRight, unRightCount);
		unCount = 1 + unLeftCount + unRightCount;
	}
}

template<typename NodeT>
inline gvoid GBinaryTree<NodeT>::LeafCount(const NodeT *node, gsize &unCount) const
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
inline gsize GBinaryTree<NodeT>::Depth(const NodeT *node) const
{
	gsize unDepthLeft;
	gsize unDepthRight;

	if (node)
	{
		unDepthLeft = Depth(node->m_pLeft);
		unDepthRight = Depth(node->m_pRight);
		return 1 + (unDepthLeft > unDepthRight ? unDepthLeft : unDepthRight);
	}

	return 0;
}

template<typename NodeT>
inline GBinaryTree<NodeT>& GBinaryTree<NodeT>::operator=(const GBinaryTree<NodeT> &tTree)
{
	CopyFrom(tTree);
	return *this;
}

#endif // _CORE_BINARY_TREE_INLINE_H_