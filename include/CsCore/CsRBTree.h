/////////////////////////////////////////////////////////////////////////////////
/// @brief 红黑树（red black tree）
/// 
///  红黑树的定义及实现
///  满足以下五个性质的二叉排序树，被称为红黑树：
///   1）每个结点要么是红的，要么是黑的。
///   2）根结点是黑的。
///   3）每个叶结点，即空结点（NIL）是黑的。
///   4）如果一个结点是红的，那么它的俩个儿子都是黑的。
///   5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-17
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "CsBSTree.h"

template<typename KeyT, typename CompareT, typename NodeT> class CsRBTree;
template<typename KeyT, typename CompareT, typename NodeT> class CsRBTree_Private;

template<typename KeyT>
struct CsRBTreeNode :public CsObject
{
	enum COLOR 
	{ 
		COLOR_RED = 0,
		COLOR_BLACK = 1
	};
	KeyT m_tKey;					// 数据，需要由外部去析构，否则可能造成内存泄露
	CsRBTreeNode<KeyT> *m_pParent;	// 双亲
	CsRBTreeNode<KeyT> *m_pLeft;		// 左孩子
	CsRBTreeNode<KeyT> *m_pRight;	// 右孩子
	cs_uint8 m_nColor;

	CsRBTreeNode(
		const KeyT &key = KeyT(),
		CsRBTreeNode<KeyT> *parent = NULL,
		CsRBTreeNode<KeyT> *left = NULL,
		CsRBTreeNode<KeyT> *right = NULL,
		COLOR color = COLOR_BLACK);
	~CsRBTreeNode();
	CsRBTreeNode<KeyT> *Copy() const;
};

/// 红黑树
template<typename KeyT, 
	typename CompareT = CsCompareF<KeyT >,
	typename NodeT = CsRBTreeNode<KeyT> >
class CsRBTree : public CsBSTree<KeyT, CompareT, NodeT>
{
public:
	virtual ~CsRBTree();

	/// 插入一个数据
	/// 如果改变了Node的结构，Insert方法需要重新实现
	virtual NodeT *InsertByKey(const KeyT &key, cs_bool *realInsert = NULL);

	/// 删除一个数据
	virtual NodeT *Delete(const KeyT &key);

private:
	CsRBTree_Private<KeyT, CompareT, NodeT> m_tRBTree_Private;
};

/// 红黑树功能实现类
template<typename KeyT, typename CompareT, typename NodeT>
class CsRBTree_Private
{
	friend class CsRBTree<KeyT, CompareT, NodeT>;

private:
	cs_bool InsertFixUp(NodeT *&p, NodeT *&root);
	cs_bool RotateLeft(NodeT *&p, NodeT *&root); // 左旋
	cs_bool RotateRight(NodeT *&p, NodeT *&root); // 右旋

private:
	CompareT m_fCompare;
};

template<typename KeyT>
inline CsRBTreeNode<KeyT>::CsRBTreeNode(
	const KeyT &key,
	CsRBTreeNode<KeyT> *parent,
	CsRBTreeNode<KeyT> *left,
	CsRBTreeNode<KeyT> *right,
	COLOR color)
	: m_tKey(key)
	, m_pParent(parent)
	, m_pLeft(left)
	, m_pRight(right)
	, m_nColor(color)
{

}

template<typename KeyT>
inline CsRBTreeNode<KeyT>::~CsRBTreeNode()
{

}

template<typename KeyT>
CsRBTreeNode<KeyT> *CsRBTreeNode<KeyT>::Copy() const
{
	CsRBTreeNode<KeyT> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsRBTreeNode<KeyT>(m_tKey, m_pParent, NULL, NULL, (COLOR)m_nColor);
	}
	catch (std::bad_alloc&)
	{
		pNode = NULL;
	}
	if (!pNode)
	{
		return NULL;
	}
	if (m_pLeft)
	{
		pNode->m_pLeft = m_pLeft->Copy();
	}
	if (m_pRight)
	{
		pNode->m_pRight = m_pRight->Copy();
	}
	return pNode;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline CsRBTree<KeyT, CompareT, NodeT>::~CsRBTree()
{

}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsRBTree<KeyT, CompareT, NodeT>::InsertByKey(const KeyT &key, cs_bool *realInsert)
{
	cs_bool insert = false;
	NodeT *p = CsBSTree<KeyT, CompareT, NodeT>::InsertByKey(key, &insert);
	if (realInsert)
	{
		*realInsert = insert;
	}
	if (!insert)
	{
		return p;
	}
	m_tRBTree_Private.InsertFixUp(p, GetRoot());
	return p;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline NodeT *CsRBTree<KeyT, CompareT, NodeT>::Delete(const KeyT &key)
{
	NodeT *p = CsBSTree<KeyT, CompareT, NodeT>::Delete(key);
	return p;
}

template<typename KeyT, typename CompareT, typename NodeT>
inline cs_bool CsRBTree_Private<KeyT, CompareT, NodeT>::InsertFixUp(NodeT *&node, NodeT *&root)
{
	if (!node || !root)
	{
		return false;
	}
	if (node == root)
	{
		node->m_nColor = NodeT::COLOR_BLACK;
		return true;
	}
	NodeT *pnode = node->m_pParent; // 双亲节点
	if (pnode == root)
	{
		return true;
	}

	if (pnode->m_nColor == NodeT::COLOR_RED)
	{
		NodeT *gnode = pnode->m_pParent; // 祖父节点
		NodeT *unode = NULL; // 叔叔节点
		pnode->m_nColor = NodeT::COLOR_BLACK;
		gnode->m_nColor = NodeT::COLOR_RED;
		if (pnode == gnode->m_pLeft)
		{
			// 双亲是祖父的左孩子，叔叔是祖父的右孩子
			unode = gnode->m_pRight;
			if (NULL == unode)
			{
				return true;
			}
			if (unode->m_nColor == NodeT::COLOR_RED)
			{
				// 叔叔是红色
				unode->m_nColor = NodeT::COLOR_BLACK;
				return InsertFixUp(gnode, root);
			}
			else
			{
				// 叔叔是黑色
				RotateLeft(pnode, root); // 以双亲为支点进行左旋
				return InsertFixUp(pnode, root);
			}
			
		}
		else
		{
			// 双亲是祖父的右孩子，叔叔是祖父的左孩子
			unode = pnode->m_pParent->m_pLeft;
			if (NULL == unode)
			{
				return true;
			}
			if (unode->m_nColor == NodeT::COLOR_RED)
			{
				// 叔叔是红色
			}
			else
			{
				// 叔叔是黑色
				RotateLeft(gnode, root); // 以祖父为支点进行左旋
			}
		}
	}
}

template<typename KeyT, typename CompareT, typename NodeT>
cs_bool CsRBTree_Private<KeyT, CompareT, NodeT>::RotateLeft(NodeT *&p, NodeT *&root)
{
	if (p == NULL || p->m_pRight == NULL)
	{
		// 不能旋转
		return false;
	}
	NodeT *node = p->m_pRight;
	node->m_pParent = p->m_pParent;
	p->m_pRight = node->m_pLeft;
	if (node->m_pLeft != NULL)
	{
		node->m_pLeft->m_pParent = p;
	}
	if (root == p)
	{
		root = node;
	}
	else
	{
		if (p == p->m_pParent->m_pLeft)
		{
			p->m_pParent->m_pLeft = node;
		}
		else
		{
			p->m_pParent->m_pRight = node;
		}
	}
	p->m_pParent = node;
	node->m_pLeft = p;
	return true;
}

template<typename KeyT, typename CompareT, typename NodeT>
cs_bool CsRBTree_Private<KeyT, CompareT, NodeT>::RotateRight(NodeT *&p, NodeT *&root)
{
	if (p == NULL || p->m_pLeft == NULL)
	{
		// 不能旋转
		return false;
	}
	NodeT *node = p->m_pLeft;
	p->m_pLeft = node->m_pRight;
	node->m_pParent = p->m_pParent;
	if (node->m_pRight != NULL)
	{
		node->m_pRight->m_pParent = p;
	}
	if (root == p)
	{
		root = node;
	}
	else
	{
		if (p == p->m_pParent->m_pRight)
		{
			p->m_pParent->m_pRight = node;
		}
		else
		{
			p->m_pParent->m_pLeft = node;
		}
	}
	p->m_pParent = node;
	node->m_pRight = p;
	return true;
}

#endif // _CORE_RED_BLACK_TREE_H_