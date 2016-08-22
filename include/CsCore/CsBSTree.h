/////////////////////////////////////////////////////////////////////////////////
/// @brief 二叉排序树（binary sort tree）
/// 
///  二叉排序树的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_BINARY_SORT_TREE_H_
#define _CORE_BINARY_SORT_TREE_H_

#include "CsBTree.h"

template<typename KeyT, typename CompareT, typename NodeT> class CsBSTree_Private;

/// 二叉排序树
template<typename KeyT, 
	typename CompareT = CsCompareF<KeyT >,
	typename NodeT = CsBTreeNode<KeyT >>
class CsBSTree : public CsBTree<KeyT, NodeT>
{
public:
	virtual ~CsBSTree();
	NodeT *Find(const KeyT &key) const;
	NodeT *FirstNode() const;
	NodeT *LastNode() const;
	NodeT *NextNode(NodeT *node) const;
	NodeT *PreviousNode(NodeT *node) const;

	/// 插入一个数据，返回插入数据的节点
	/// 如果改变了Node的结构，Insert方法需要重新实现
	/// realInsert指示是否进行了实际的插入操作，返回false则表明并没有插入任何元素（元素原本就已经存在）
	virtual NodeT *InsertByNode(const NodeT &node, cs_bool *realInsert = NULL);
	virtual NodeT *InsertByKey(const KeyT &key, cs_bool *realInsert = NULL);
	
	/// 删除一个数据，返回实际删除数据的节点
	virtual NodeT *Delete(const KeyT &key);

private:
	CsBSTree_Private<KeyT, CompareT, NodeT> m_tBSTree_Private;
};

/// 二叉排序树功能实现类
template<typename KeyT, typename CompareT, typename NodeT>
class CsBSTree_Private
{
	friend class CsBSTree<KeyT, CompareT, NodeT>;
private:
	NodeT *Find(const KeyT &key, NodeT *p) const;
	NodeT *FirstNode(NodeT *p) const;
	NodeT *LastNode(NodeT *p) const;
	NodeT *NextNode(NodeT *node) const;
	NodeT *PreviousNode(NodeT *node) const;

	// insert指示是否完成了插入操作，若data值与原本的值相同，则不会进行插入操作
	NodeT *InsertByNode(const NodeT &node, NodeT *&p, NodeT *&root, NodeT *&insNode, cs_bool &insert);
	NodeT *Delete(const KeyT &key, NodeT *&p, NodeT *&root, NodeT *&delNode);

	cs_bool SwitchNode(NodeT *node1, NodeT *node2);

private:
	CompareT m_fCompare;
};

template<typename KeyT, typename CompareT, typename NodeT>
inline CsBSTree<KeyT, CompareT, NodeT>::~CsBSTree()
{

}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::Find(const KeyT &key) const
{
	return m_tBSTree_Private.Find(key, GetRoot());
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::FirstNode() const
{
	return m_tBSTree_Private.FirstNode(GetRoot());
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::LastNode() const
{
	return m_tBSTree_Private.LastNode(GetRoot());
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsBSTree<KeyT, CompareT, NodeT>::NextNode(NodeT *node) const
{
	return m_tBSTree_Private.NextNode(node);
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsBSTree<KeyT, CompareT, NodeT>::PreviousNode(NodeT *node) const
{
	return m_tBSTree_Private.PreviousNode(node);
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::InsertByKey(const KeyT &key, cs_bool *realInsert)
{
	return InsertByNode(NodeT(key), realInsert);
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::InsertByNode(const NodeT &node, cs_bool *realInsert)
{
	cs_bool insert = false;
	NodeT* pInsNode = NULL;
	m_tBSTree_Private.InsertByNode(node, GetRoot(), GetRoot(), pInsNode, insert);
	if (realInsert)
	{
		*realInsert = insert;
	}
	return pInsNode;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree<KeyT, CompareT, NodeT>::Delete(const KeyT &key)
{
	NodeT* pDelNode = NULL;
	m_tBSTree_Private.Delete(key, GetRoot(), GetRoot(), pDelNode);
	return pDelNode;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree_Private<KeyT, CompareT, NodeT>::Find(const KeyT &key, NodeT *p) const
{
	if (NULL == p)
	{
		return NULL;
	}
	cs_int ret = m_fCompare(key, p->m_tKey);
	if (ret < 0)
	{
		return Find(key, p->m_pLeft);
	}
	else if (ret > 0)
	{
		return Find(key, p->m_pRight);
	}
	else
	{
		return p;
	}
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree_Private<KeyT, CompareT, NodeT>::FirstNode(NodeT *p) const
{
	if (NULL == p)
	{
		return NULL;
	}
	else if (NULL == p->m_pLeft)
	{
		return p;
	}
	else
	{
		return FirstNode(p->m_pLeft);
	}
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree_Private<KeyT, CompareT, NodeT>::LastNode(NodeT *p) const
{
	if (NULL == p)
	{
		return NULL;
	}
	else if (NULL == p->m_pRight)
	{
		return p;
	}
	else
	{
		return LastNode(p->m_pRight);
	}
}


template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsBSTree_Private<KeyT, CompareT, NodeT>::NextNode(NodeT *node) const
{
	if (!node)
	{
		return NULL;
	}
	NodeT *n = NULL;
	if (node->m_pRight)
	{
		n = node->m_pRight;
		while (n->m_pLeft)
		{
			n = n->m_pLeft;
		}
	}
	else
	{
		if (!node->m_pParent)
		{
			return NULL;
		}
		n = node;
		NodeT *p = n->m_pParent;
		while (p && n == p->m_pRight)
		{
			n = p;
			p = n->m_pParent;
		}
		n = p;
	}
	return n;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsBSTree_Private<KeyT, CompareT, NodeT>::PreviousNode(NodeT *node) const
{
	if (!node)
	{
		return NULL;
	}
	NodeT *n = NULL;
	if (node->m_pLeft)
	{
		n = node->m_pLeft;
		while (n->m_pRight)
		{
			n = n->m_pRight;
		}
	}
	else
	{
		if (!node->m_pParent)
		{
			return NULL;
		}
		n = node;
		NodeT *p = n->m_pParent;
		while (p && n == p->m_pLeft)
		{
			n = p;
			p = n->m_pParent;
		}
		n = p;
	}
	return n;
}

//返回值：如果p为NULL，则返回值为新分配内存的指针；如果p不是NULL，则返回值即为p.  
template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree_Private<KeyT, CompareT, NodeT>::InsertByNode(const NodeT &node, NodeT *&p, NodeT *&root, NodeT *&insNode, cs_bool &insert)
{
	if (NULL == p)
	{
		insert = true;
		insNode = (NodeT*)node.Copy();
		if (NULL == insNode)
		{
			insert = false;
		}
		if (NULL == root)
		{
			root = insNode;
		}
		return insNode;
	}
	
	cs_int ret = m_fCompare(node.m_tKey, p->m_tKey);
	if (ret < 0)
	{
		p->m_pLeft = InsertByNode(node, p->m_pLeft, root, insNode, insert);
		if (p->m_pLeft)
		{
			p->m_pLeft->m_pParent = p;
		}
	}
	else if (ret > 0)
	{
		p->m_pRight = InsertByNode(node, p->m_pRight, root, insNode, insert);
		if (p->m_pRight)
		{
			p->m_pRight->m_pParent = p;
		}
	}
	else
	{
		insNode = p;
	}
	return p;
}

//返回值：如果节点p的数据与data不等，则返回值即为p;如果相等，但有两个子节点，返回值也为p，有一个子节点，返回值为该子节点指针，  
//如果无节点，返回值NULL。  
//node为待删除的节点
template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT* CsBSTree_Private<KeyT, CompareT, NodeT>::Delete(const KeyT &key, NodeT *&p, NodeT *&root, NodeT *&delNode)
{
	if (NULL == p)
	{
		// Error! data not found!
		return p;
	}
	
	cs_int ret = m_fCompare(key, p->m_tKey);
	if (ret < 0)
	{
		p->m_pLeft = Delete(key, p->m_pLeft, root, delNode);
	}
	else if (ret > 0)
	{
		p->m_pRight = Delete(key, p->m_pRight, root, delNode);
	}
	else
	{
		// 查找成功
		if (p->m_pLeft && p->m_pRight)
		{
			// 有两个孩子
			// 注意为节点（Node*）的调换，而非节点值（Node->Data）的调换，以追求效率，并且避免内存泄露
			NodeT *tmp = FirstNode(p->m_pRight);
			SwitchNode(p, tmp);
			if (root == p)
			{
				root = tmp;
			}
			p->m_pRight = Delete(key, tmp->m_pRight, root, delNode);
		}
		else
		{
			// 查找成功，并且它没有孩子或只有一个孩子
			delNode = p;
			if (NULL == p->m_pLeft)
			{
				p = (NodeT*)p->m_pRight;
			}
			else if (NULL == p->m_pRight)
			{
				p = (NodeT*)p->m_pLeft;
			}
			if (p)
			{
				p->m_pParent = delNode->m_pParent;
			}
			if (root == delNode)
			{
				root = p;
			}
			// delete pTmp; 交由外界去删除
		}
	}
	return p;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline cs_bool CsBSTree_Private<KeyT, CompareT, NodeT>::SwitchNode(NodeT *node1, NodeT *node2)
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

	node1->m_pParent = pnode2;
	node2->m_pParent = pnode1;

	NodeT *tmp = node1->m_pLeft;
	node1->m_pLeft = node2->m_pLeft;
	node2->m_pLeft = tmp;

	tmp = node1->m_pRight;
	node1->m_pRight = node2->m_pRight;
	node2->m_pRight = tmp;
	return true;
}

#endif // _CORE_BINARY_SORT_TREE_H_