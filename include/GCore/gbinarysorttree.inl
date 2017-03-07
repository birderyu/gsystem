#ifndef _CORE_BINARY_SORT_TREE_INLINE_
#define _CORE_BINARY_SORT_TREE_INLINE_

template<typename KeyT, typename ValueT>
GINLINE GBinarySortTreeNode<KeyT, ValueT>::GBinarySortTreeNode(
	const KeyT &key,
	const ValueT &value,
	GBinarySortTreeNode<KeyT, ValueT> *parent,
	GBinarySortTreeNode<KeyT, ValueT> *left,
	GBinarySortTreeNode<KeyT, ValueT> *right)
	: GBinaryTreeNodeT<GBinarySortTreeNode<KeyT, ValueT>>(parent, left, right)
	, GPairNodeT<KeyT, ValueT>(key, value)
{

}

template<typename KeyT, typename ValueT>
GINLINE GBinarySortTreeNode<KeyT, ValueT>::GBinarySortTreeNode(
	const KeyT &key,
	ValueT &&value,
	GBinarySortTreeNode<KeyT, ValueT> *parent,
	GBinarySortTreeNode<KeyT, ValueT> *left,
	GBinarySortTreeNode<KeyT, ValueT> *right)
	: GBinaryTreeNodeT<GBinarySortTreeNode<KeyT, ValueT>>(parent, left, right)
	, GPairNodeT<KeyT, ValueT>(key, GForward<ValueT>(value))
{

}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
const typename GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Tree GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::m_gTree;

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
const CompareT GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::m_fCompare;

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::~GBinarySortTree()
{

}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::FirstNode()
{
	if (!m_pRoot)
	{
		return GNULL;
	}
	return m_pRoot->First();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE const NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::FirstNode() const
{
	if (!m_pRoot)
	{
		return GNULL;
	}
	return m_pRoot->First();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::LastNode()
{
	if (!m_pRoot)
	{
		return GNULL;
	}
	return m_pRoot->Last();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE const NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::LastNode() const
{
	if (!m_pRoot)
	{
		return GNULL;
	}
	return m_pRoot->Last();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gbool GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Contains(const KeyT &key) const
{
	NodeT *root = m_pRoot;
	if (!root)
	{
		return false;
	}

	// 递归实现
	//return Contains_Recursive(key, root);

	// 非递归实现
	return Contains_Unrecursive(key, root);
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find(const KeyT &key)
{
	NodeT *root = m_pRoot;
	if (!root)
	{
		return GNULL;
	}

	// 递归实现
	//return Find_Recursive(key, root);

	// 非递归实现
	return Find_Unrecursive(key, root);
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE const NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find(const KeyT &key) const
{
	const NodeT *root = m_pRoot;
	if (!root)
	{
		return GNULL;
	}

	// 递归实现
	//return Find_Recursive(key, root);

	// 非递归实现
	return Find_Unrecursive(key, root);
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
template<typename FilterT>
GINLINE typename GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Nodes GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Search(FilterT &filter)
{
	Nodes nodes;
	Search_Recursive(m_pRoot, filter, nodes);
	return nodes;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
template<typename FilterT> 
GINLINE typename GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::ConstNodes GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Search(FilterT &filter) const
{
	ConstNodes nodes;
	Search_Recursive(m_pRoot, filter, nodes);
	return nodes;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert(const KeyT &key, const ValueT &value, gbool *realInsert)
{
	NodeT *node = GNULL;
	gbool _realInsert = false;

	// 递归实现
	//Insert_Recursive(key, value, m_pRoot, node, _realInsert);

	// 非递归实现
	Insert_Unrecursive(key, value, m_pRoot, node, _realInsert);

	if (realInsert)
	{
		*realInsert = _realInsert;
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert(const KeyT &key, ValueT &&value, gbool *realInsert)
{
	NodeT *node = GNULL;
	gbool _realInsert = false;

	// 递归实现
	//Insert_Recursive(key, GForward<ValueT>(value), m_pRoot, node, _realInsert);

	// 非递归实现
	Insert_Unrecursive(key, GForward<ValueT>(value), m_pRoot, node, _realInsert);

	if (realInsert)
	{
		*realInsert = _realInsert;
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete(const KeyT &key, gbool *realDelete)
{
	gbool _realDelete = false;

	// 递归实现
	//Delete_Recursive(key, m_pRoot, _realDelete);

	// 非递归实现
	Delete_Unrecursive(key, m_pRoot, _realDelete);

	if (realDelete)
	{
		*realDelete = _realDelete;
	}
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete(NodeT *delete_point, gbool *realDelete)
{
	// 非递归删除节点
	if (!delete_point)
	{
		if (realDelete)
		{
			*realDelete = false;
		}
		return;
	}

	if (delete_point->m_pLeft && delete_point->m_pRight)
	{
		// 找到节点，且该节点有左右两个孩子
		NodeT *successor = delete_point->m_pRight->First();
		SwitchNode(delete_point, successor);
	}

	NodeT *delete_point_child = GNULL;
	if (!delete_point->m_pLeft)
	{
		delete_point_child = delete_point->m_pRight;
	}
	else if (!delete_point->m_pRight)
	{
		delete_point_child = delete_point->m_pLeft;
	}

	NodeT *delete_point_parent = delete_point->m_pParent;
	if (delete_point_child)
	{
		delete_point_child->m_pParent = delete_point_parent;
	}

	if (!delete_point_parent)
	{
		m_pRoot = delete_point_child;
	}
	else
	{
		if (delete_point == delete_point_parent->m_pLeft)
		{
			delete_point_parent->m_pLeft = delete_point_child;
		}
		else
		{
			delete_point_parent->m_pRight = delete_point_child;
		}
	}

	if (realDelete)
	{
		*realDelete = true;
	}
	delete delete_point;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gbool GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::NodeEquals(const NodeT *node1, const NodeT *node2) const
{
	if (GNULL == node1 && GNULL == node2)
	{
		return true;
	}
	else if (GNULL == node1 || GNULL == node2)
	{
		return false;
	}

	return m_fCompare(node1->m_tKey, node2->m_tKey) == 0;
}

//////////////////////////////////////////////////////////////////////////

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gbool GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Contains_Unrecursive(const KeyT &key, NodeT *node) const
{
	while (node)
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			return true;
		}
	}
	return false;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find_Unrecursive(const KeyT &key, NodeT *node)
{
	while (node)
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			break;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE const NodeT* GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find_Unrecursive(const KeyT &key, const NodeT *node) const
{
	while (node)
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			break;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert_Unrecursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert)
{
	NodeT* insert_point = GNULL; // 插入位置的双亲节点
	while (node)
	{
		insert_point = node;
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			realInsert = false;
			node->m_tValue = value;
			node_ins = node;
			return;
		}
	}

	// 新增插入节点
	NodeT* insert_node = new NodeT(key, value);
	if (!insert_point)
	{
		//插入的是一颗空树
		m_pRoot = insert_node;
	}
	else
	{
		// 找到具体的插入位置
		gint ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// 处理数据相同的情况
		}
		insert_node->m_pParent = insert_point;
	}
	realInsert = true;
	node_ins = insert_node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert_Unrecursive(const KeyT &key, ValueT &&value, NodeT *node, NodeT *&node_ins, gbool &realInsert)
{
	NodeT* insert_point = GNULL; // 插入位置的双亲节点
	while (node)
	{
		insert_point = node;
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			realInsert = false;
			node->m_tValue = GForward<ValueT>(value);
			node_ins = node;
			return;
		}
	}

	// 新增插入节点
	NodeT* insert_node = new NodeT(key, GForward<ValueT>(value));
	if (!insert_point)
	{
		//插入的是一颗空树
		m_pRoot = insert_node;
	}
	else
	{
		// 找到具体的插入位置
		gint ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// 处理数据相同的情况
		}
		insert_node->m_pParent = insert_point;
	}
	realInsert = true;
	node_ins = insert_node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete_Unrecursive(const KeyT &key, NodeT *node, gbool &realDelete)
{
	NodeT* delete_point = Find_Unrecursive(key, node);
	if (!delete_point)
	{
		realDelete = false;
		return;
	}
	if (delete_point->m_pLeft && delete_point->m_pRight)
	{
		// 找到节点，且该节点有左右两个孩子
		NodeT *successor = delete_point->m_pRight->First();
		SwitchNode(delete_point, successor);
	}

	NodeT *delete_point_child = GNULL;
	if (!delete_point->m_pLeft)
	{
		delete_point_child = delete_point->m_pRight;
	}
	else if (!delete_point->m_pRight)
	{
		delete_point_child = delete_point->m_pLeft;
	}

	NodeT *delete_point_parent = delete_point->m_pParent;
	if (delete_point_child)
	{
		delete_point_child->m_pParent = delete_point_parent;
	}

	if (!delete_point_parent)
	{
		m_pRoot = delete_point_child;
	}
	else
	{
		if (delete_point == delete_point_parent->m_pLeft)
		{
			delete_point_parent->m_pLeft = delete_point_child;
		}
		else
		{
			delete_point_parent->m_pRight = delete_point_child;
		}
	}

	realDelete = true;
	delete delete_point;
}

//////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gbool GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Contains_Recursive(const KeyT &key, NodeT *node) const
{
	if (!node)
	{
		return false;
	}
	gint ret = m_fCompare(key, node->m_tKey);
	if (ret < 0)
	{
		return Contains_Recursive(key, node->m_pLeft);
	}
	else if (ret > 0)
	{
		return Contains_Recursive(key, node->m_pRight);
	}
	return true;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find_Recursive(const KeyT &key, NodeT *node)
{
	if (!node)
	{
		return GNULL;
	}
	gint ret = m_fCompare(key, node->m_tKey);
	if (ret < 0)
	{
		return Find_Recursive(key, node->m_pLeft);
	}
	else if (ret > 0)
	{
		return Find_Recursive(key, node->m_pRight);
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE const NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find_Recursive(const KeyT &key, const NodeT *node) const
{
	if (!node)
	{
		return GNULL;
	}
	gint ret = m_fCompare(key, node->m_tKey);
	if (ret < 0)
	{
		return Find_Recursive(key, node->m_pLeft);
	}
	else if (ret > 0)
	{
		return Find_Recursive(key, node->m_pRight);
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
template<typename FilterT>
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Search_Recursive(NodeT *node, FilterT &filter,
	typename GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Nodes &nodes)
{
	if (GNULL == node)
	{
		return;
	}
	gint ret = filter(node->m_tKey);
	if ((ret & Filter::FIT) == Filter::FIT)
	{
		nodes.PushBack(node);
	}
	if ((ret & Filter::TURN_LEFT) == Filter::TURN_LEFT)
	{
		Search_Recursive(node->m_pLeft, filter, nodes);
	}
	if ((ret & Filter::TURN_RIGHT) == Filter::TURN_RIGHT)
	{
		Search_Recursive(node->m_pRight, filter, nodes);
	}
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
template<typename FilterT> 
GINLINE gvoid GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Search_Recursive(const NodeT *node, FilterT &filter,
	typename GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::ConstNodes &nodes) const
{
	if (GNULL == node)
	{
		return;
	}
	gint ret = filter(node->m_tKey);
	if ((ret & Filter::FIT) == Filter::FIT)
	{
		nodes.PushBack(node);
	}
	if ((ret & Filter::TURN_LEFT) == Filter::TURN_LEFT)
	{
		Search_Recursive(node->m_pLeft, filter, nodes);
	}
	if ((ret & Filter::TURN_RIGHT) == Filter::TURN_RIGHT)
	{
		Search_Recursive(node->m_pRight, filter, nodes);
	}
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert)
{
	if (GNULL == node)
	{
		try
		{
			node = new NodeT(key, value);
		}
		catch (std::bad_alloc&)
		{
			return GNULL;
		}

		node_ins = node;
		if (IsEmpty())
		{
			m_pRoot = node;
		}
		realInsert = true;
	}
	else
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			NodeT *_node = Insert_Recursive(key, value, node->m_pLeft, node_ins);
			if (_node && !node->m_pLeft)
			{
				node->m_pLeft = _node;
				_node->m_pParent = node;
			}
		}
		else if (ret > 0)
		{
			NodeT *_node = Insert_Recursive(key, value, node->m_pRight, node_ins);
			if (_node && !node->m_pRight)
			{
				node->m_pRight = _node;
				_node->m_pParent = node;
			}
		}
		else
		{
			// 相等，不做任何操作
			realInsert = false;
			node_ins = node;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert_Recursive(const KeyT &key, ValueT &&value, NodeT *node, NodeT *&node_ins, gbool &realInsert)
{
	if (GNULL == node)
	{
		try
		{
			node = new NodeT(key, GForward<ValueT>(value));
		}
		catch (std::bad_alloc&)
		{
			return GNULL;
		}

		node_ins = node;
		if (IsEmpty())
		{
			m_pRoot = node;
		}
		realInsert = true;
	}
	else
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			NodeT *_node = Insert_Recursive(key, GForward<ValueT>(value), node->m_pLeft, node_ins);
			if (_node && !node->m_pLeft)
			{
				node->m_pLeft = _node;
				_node->m_pParent = node;
			}
		}
		else if (ret > 0)
		{
			NodeT *_node = Insert_Recursive(key, GForward<ValueT>(value), node->m_pRight, node_ins);
			if (_node && !node->m_pRight)
			{
				node->m_pRight = _node;
				_node->m_pParent = node;
			}
		}
		else
		{
			// 相等，不做任何操作
			realInsert = false;
			node_ins = node;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE NodeT *GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete_Recursive(const KeyT &key, NodeT *node, gbool &realDelete)
{
	if (GNULL == node)
	{
		// 未能查找到元素
	}
	else
	{
		gint ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node->m_pLeft = Delete_Recursive(key, node->m_pLeft);
		}
		else if (ret > 0)
		{
			node->m_pRight = Delete_Recursive(key, node->m_pRight);
		}
		else if (node->m_pLeft && node->m_pRight)
		{
			// 找到节点，且该节点有左右两个孩子
			NodeT *temp = node->m_pRight->First();
			SwitchNode(node, temp);
			node->m_pRight = Delete_Recursive(key, temp->m_pRight);
		}
		else
		{
			// 找到节点，且该节点只有一个孩子或没有孩子
			NodeT *temp = node;
			if (!node->m_pLeft)
			{
				node = node->m_pRight;
			}
			else if (!node->m_pRight)
			{
				node = node->m_pLeft;
			}

			NodeT *pnode = temp->m_pParent;
			if (node)
			{
				node->m_pParent = pnode;
			}

			if (!pnode)
			{
				m_pRoot = node;
			}
			else
			{
				if (temp == pnode->m_pLeft)
				{
					pnode->m_pLeft = node;
				}
				else
				{
					pnode->m_pRight = node;
				}
			}
			realDelete = true;
			delete temp;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
GINLINE gbool GBinarySortTree<KeyT, ValueT, CompareT, NodeT>::SwitchNode(NodeT *node1, NodeT *node2)
{
	if (!node1 || !node2)
	{
		return false;
	}
	if (node1 == node2)
	{
		return true;
	}
	NodeT *pnode1 = node1->m_pParent;
	NodeT *pnode2 = node2->m_pParent;

	if (pnode1)
	{
		if (pnode1->m_pLeft == node1)
		{
			pnode1->m_pLeft = node2;
		}
		else
		{
			pnode1->m_pRight = node2;
		}
	}

	if (pnode2)
	{
		if (pnode2->m_pLeft == node2)
		{
			pnode2->m_pLeft = node1;
		}
		else
		{
			pnode2->m_pRight = node1;
		}
	}

	// 交换node1和node2的双亲
	node1->m_pParent = pnode2;
	node2->m_pParent = pnode1;

	// 交换node1和node2孩子的双亲
	if (node1->m_pLeft)
	{
		node1->m_pLeft->m_pParent = node2;
	}
	if (node1->m_pRight)
	{
		node1->m_pRight->m_pParent = node2;
	}

	if (node2->m_pLeft)
	{
		node2->m_pLeft->m_pParent = node1;
	}
	if (node2->m_pRight)
	{
		node2->m_pRight->m_pParent = node1;
	}

	// 交换node1和node2的孩子
	NodeT *tmp = node1->m_pLeft;
	node1->m_pLeft = node2->m_pLeft;
	node2->m_pLeft = tmp;

	tmp = node1->m_pRight;
	node1->m_pRight = node2->m_pRight;
	node2->m_pRight = tmp;

	if (node1->m_pParent == GNULL)
	{
		m_pRoot = node1;
	}
	if (node2->m_pParent == GNULL)
	{
		m_pRoot = node2;
	}

	return true;
}

#endif // _CORE_BINARY_SORT_TREE_INLINE_