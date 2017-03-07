#ifndef _CORE_BINARY_TREE_INLINE_
#define _CORE_BINARY_TREE_INLINE_

GINLINE GBinaryTreeNode::GBinaryTreeNode(GBinaryTreeNode *parent, GBinaryTreeNode *left, GBinaryTreeNode *right)
: GBinaryTreeNodeT<GBinaryTreeNode>(parent, left, right)
{

}

template<typename NodeT>
GINLINE GBinaryTree<NodeT>::GBinaryTree(NodeT *pRoot)
: m_pRoot(pRoot)
{
	
}

template<typename NodeT>
GINLINE GBinaryTree<NodeT>::GBinaryTree(const GBinaryTree<NodeT> &tTree)
: m_pRoot(GNULL)
{
	CopyFrom(tTree);
}

template<typename NodeT>
GINLINE GBinaryTree<NodeT>::GBinaryTree(GBinaryTree<NodeT> &&tree)
: m_pRoot(tree.m_pRoot)
{
	tree.m_pRoot = GNULL;
}

template<typename NodeT>
GINLINE GBinaryTree<NodeT> &GBinaryTree<NodeT>::operator=(const GBinaryTree<NodeT> &tree)
{
	if (this == &tree)
	{
		return *this;
	}
	CopyFrom(tree);
	return *this;
}

template<typename NodeT>
GINLINE GBinaryTree<NodeT> &GBinaryTree<NodeT>::operator=(GBinaryTree<NodeT> &&tree)
{
	if (this == &tree)
	{
		return *this;
	}
	m_pRoot = tree.m_pRoot;
	tree.m_pRoot = GNULL;
	return *this;
}

template<typename NodeT>
GINLINE GBinaryTree<NodeT>::~GBinaryTree()
{
	Dispose();
}

template<typename NodeT>
GINLINE gvoid GBinaryTree<NodeT>::SetRoot(NodeT *pNode)
{
	if (!m_pRoot)
	{
		Dispose();
	}
	m_pRoot = pNode;
}

template<typename NodeT>
GINLINE gvoid GBinaryTree<NodeT>::CopyFrom(const GBinaryTree<NodeT> &tTree)
{
	if (this == &tTree)
	{
		return;
	}
	if (m_pRoot != GNULL)
	{
		Dispose();
	}
	if (GNULL != tTree.m_pRoot)
	{
		// µÝ¹é¿½±´
		m_pRoot = CopySubTree(tTree.m_pRoot);
	}
	else
	{
		m_pRoot = GNULL;
	}
}

template<typename NodeT>
GINLINE gvoid GBinaryTree<NodeT>::Dispose()
{
	DestroySubTree(m_pRoot);
	m_pRoot = GNULL;
}

template<typename NodeT>
GINLINE gbool GBinaryTree<NodeT>::IsEmpty() const
{
	return GNULL == m_pRoot;
}

template<typename NodeT>
GINLINE NodeT*& GBinaryTree<NodeT>::Root()
{
	return *(&(m_pRoot));
}

template<typename NodeT>
GINLINE NodeT* GBinaryTree<NodeT>::Root() const
{
	return m_pRoot;
}

template<typename NodeT>
template<typename VisitorT>  
GINLINE gvoid GBinaryTree<NodeT>::PreOrderTraverse(VisitorT &visitor) const
{
	PreOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
template<typename VisitorT>
GINLINE gvoid GBinaryTree<NodeT>::InOrderTraverse(VisitorT &visitor) const
{
	InOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
template<typename VisitorT>
GINLINE gvoid GBinaryTree<NodeT>::PostOrderTraverse(VisitorT &visitor) const
{
	PostOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
GINLINE gsize GBinaryTree<NodeT>::NodeCount() const
{
	std::pair
	gsize unCount = 0;
	NodeCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
GINLINE gsize GBinaryTree<NodeT>::LeafCount() const
{
	gsize unCount = 0;
	LeafCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
GINLINE gsize GBinaryTree<NodeT>::Depth() const
{
	return Depth(m_pRoot);
}

template<typename NodeT>
GINLINE gbool GBinaryTree<NodeT>::operator==(const GBinaryTree<NodeT> &tree) const
{
	return TreeEquals(m_pRoot, tree.m_pRoot);
}

template<typename NodeT>
GINLINE gbool GBinaryTree<NodeT>::operator!=(const GBinaryTree<NodeT> &tree) const
{
	return !(*this == tree);
}

template<typename NodeT>
GINLINE gvoid GBinaryTree<NodeT>::DestroySubTree(NodeT *node)
{
	if (node)
	{
		DestroySubTree(node->m_pLeft);
		DestroySubTree(node->m_pRight);
		delete node;
	}
}

template<typename NodeT>
GINLINE NodeT *GBinaryTree<NodeT>::CopySubTree(NodeT *node)
{
	if (!node)
	{
		return GNULL;
	}
	NodeT *node_new = new NodeT(*node);
	node_new->m_pLeft = CopySubTree(node->m_pLeft);
	node_new->m_pRight = CopySubTree(node->m_pRight);
	return node_new;
}

template<typename NodeT>
template<typename VisitorT>
GINLINE gvoid GBinaryTree<NodeT>::PreOrderTraverse(const NodeT *node, VisitorT &visitor) const
{
	if (node)
	{
		visitor(*node);
		PreOrderTraverse(node->m_pLeft, visitor);
		PreOrderTraverse(node->m_pRight, visitor);
	}
}

template<typename NodeT>
template<typename VisitorT>
GINLINE gvoid GBinaryTree<NodeT>::InOrderTraverse(const NodeT *node, VisitorT &visitor) const
{
	if (node)
	{
		InOrderTraverse(node->m_pLeft, visitor);
		visitor(*node);
		InOrderTraverse(node->m_pRight, visitor);
	}
}

template<typename NodeT>
template<typename VisitorT>
GINLINE gvoid GBinaryTree<NodeT>::PostOrderTraverse(const NodeT *node, VisitorT &visitor) const
{
	if (node)
	{
		PostOrderTraverse(node->m_pLeft, visitor);
		PostOrderTraverse(node->m_pRight, visitor);
		visitor(*node);
	}
}

template<typename NodeT>
GINLINE gvoid GBinaryTree<NodeT>::NodeCount(const NodeT *node, gsize &unCount) const
{
	if (GNULL == node)
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
GINLINE gvoid GBinaryTree<NodeT>::LeafCount(const NodeT *node, gsize &unCount) const
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
GINLINE gsize GBinaryTree<NodeT>::Depth(const NodeT *node) const
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
GINLINE gbool GBinaryTree<NodeT>::TreeEquals(const NodeT *node1, const NodeT *node2) const
{
	return NodeEquals(node1, node2)
		&& TreeEquals(node1->m_pLeft, node2->m_pLeft)
		&& TreeEquals(node1->m_pRight, node2->m_pRight);
}

template<typename NodeT>
GINLINE gbool GBinaryTree<NodeT>::NodeEquals(const NodeT *node1, const NodeT *node2) const
{
	if (GNULL == node1 && GNULL == node2)
	{
		return true;
	}
	else if (GNULL == node1 || GNULL == node2)
	{
		return false;
	}
	return true;
}

#endif // _CORE_BINARY_TREE_INLINE_H_