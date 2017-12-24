#ifndef _CORE_BINARY_TREE_INLINE_
#define _CORE_BINARY_TREE_INLINE_

namespace gsystem { // gsystem

GINLINE GBinTreeNode::GBinTreeNode(GBinTreeNode *parent, GBinTreeNode *left, GBinTreeNode *right)
: GBinTreeNodeT<GBinTreeNode>(parent, left, right)
{

}

template<typename NodeT>
GINLINE GBinTree<NodeT>::GBinTree(NodeT *pRoot)
: m_pRoot(pRoot)
{
	
}

template<typename NodeT>
GINLINE GBinTree<NodeT>::GBinTree(const GBinTree<NodeT> &tTree)
: m_pRoot(GNULL)
{
	CopyFrom(tTree);
}

template<typename NodeT>
GINLINE GBinTree<NodeT>::GBinTree(GBinTree<NodeT> &&tree)
: m_pRoot(tree.m_pRoot)
{
	tree.m_pRoot = GNULL;
}

template<typename NodeT>
GINLINE GBinTree<NodeT> &GBinTree<NodeT>::operator=(const GBinTree<NodeT> &tree)
{
	if (this == &tree)
	{
		return *this;
	}
	CopyFrom(tree);
	return *this;
}

template<typename NodeT>
GINLINE GBinTree<NodeT> &GBinTree<NodeT>::operator=(GBinTree<NodeT> &&tree)
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
GINLINE GBinTree<NodeT>::~GBinTree()
{
	Destroy();
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::SetRoot(NodeT *pNode)
{
	if (!m_pRoot)
	{
		Destroy();
	}
	m_pRoot = pNode;
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::CopyFrom(const GBinTree<NodeT> &tTree)
{
	if (this == &tTree)
	{
		return;
	}
	if (m_pRoot != GNULL)
	{
		Destroy();
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
GINLINE gvoid GBinTree<NodeT>::Destroy()
{
	DestroySubTree(m_pRoot);
	m_pRoot = GNULL;
}

template<typename NodeT>
GINLINE gbool GBinTree<NodeT>::IsEmpty() const
{
	return GNULL == m_pRoot;
}

template<typename NodeT>
GINLINE NodeT*& GBinTree<NodeT>::Root()
{
	return *(&(m_pRoot));
}

template<typename NodeT>
GINLINE NodeT* GBinTree<NodeT>::Root() const
{
	return m_pRoot;
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::PreOrderTraverse(const GFunction<gbool(const NodeT &)> &visitor) const
{
	PreOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::InOrderTraverse(const GFunction<gbool(const NodeT &)> &visitor) const
{
	InOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::PostOrderTraverse(const GFunction<gbool(const NodeT &)> &visitor) const
{
	PostOrderTraverse(m_pRoot, visitor);
}

template<typename NodeT>
GINLINE gsize GBinTree<NodeT>::NodeCount() const
{
	std::pair
	gsize unCount = 0;
	NodeCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
GINLINE gsize GBinTree<NodeT>::LeafCount() const
{
	gsize unCount = 0;
	LeafCount(m_pRoot, unCount);
	return unCount;
}

template<typename NodeT>
GINLINE gsize GBinTree<NodeT>::Depth() const
{
	return Depth(m_pRoot);
}

template<typename NodeT>
GINLINE gbool GBinTree<NodeT>::operator==(const GBinTree<NodeT> &tree) const
{
	return TreeEquals(m_pRoot, tree.m_pRoot);
}

template<typename NodeT>
GINLINE gbool GBinTree<NodeT>::operator!=(const GBinTree<NodeT> &tree) const
{
	return !(*this == tree);
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::DestroySubTree(NodeT *node)
{
	if (node)
	{
		DestroySubTree(node->m_pLeft);
		DestroySubTree(node->m_pRight);
		delete node;
	}
}

template<typename NodeT>
GINLINE NodeT *GBinTree<NodeT>::CopySubTree(NodeT *node)
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
GINLINE gvoid GBinTree<NodeT>::PreOrderTraverse(const NodeT *node, const GFunction<gbool(const NodeT &)> &visitor) const
{
	if (node && visitor)
	{
		if (!visitor(*node))
		{
			return;
		}
		PreOrderTraverse(node->m_pLeft, visitor);
		PreOrderTraverse(node->m_pRight, visitor);
	}
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::InOrderTraverse(const NodeT *node, const GFunction<gbool(const NodeT &)> &visitor) const
{
	if (node && visitor)
	{
		InOrderTraverse(node->m_pLeft, visitor);
		if (!visitor(*node))
		{
			return;
		}
		InOrderTraverse(node->m_pRight, visitor);
	}
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::PostOrderTraverse(const NodeT *node, const GFunction<gbool(const NodeT &)> &visitor) const
{
	if (node && visitor)
	{
		PostOrderTraverse(node->m_pLeft, visitor);
		PostOrderTraverse(node->m_pRight, visitor);
		if (!visitor(*node))
		{
			return;
		}
	}
}

template<typename NodeT>
GINLINE gvoid GBinTree<NodeT>::NodeCount(const NodeT *node, gsize &unCount) const
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
GINLINE gvoid GBinTree<NodeT>::LeafCount(const NodeT *node, gsize &unCount) const
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
GINLINE gsize GBinTree<NodeT>::Depth(const NodeT *node) const
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
GINLINE gbool GBinTree<NodeT>::TreeEquals(const NodeT *node1, const NodeT *node2) const
{
	return NodeEquals(node1, node2)
		&& TreeEquals(node1->m_pLeft, node2->m_pLeft)
		&& TreeEquals(node1->m_pRight, node2->m_pRight);
}

template<typename NodeT>
GINLINE gbool GBinTree<NodeT>::NodeEquals(const NodeT *node1, const NodeT *node2) const
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

}  // namespace gsystem

#endif // _CORE_BINARY_TREE_INLINE_H_