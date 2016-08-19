/////////////////////////////////////////////////////////////////////////////////
/// @brief 红黑树（red black tree）
/// 
///  红黑树的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-17
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "CsBSTree.h"

template<typename KeyT, typename CompareT> class CsRBTree;
template<typename KeyT, typename CompareT> class CsRBTree_Private;

/// 红黑树节点
template<typename KeyT>
struct CsRBTreeNode :public CsBTreeNode<KeyT>
{
	enum COLOR 
	{ 
		COLOR_RED = 0,
		COLOR_BLACK = 1
	};
	cs_uint8 m_nColor;

	CsRBTreeNode(
		const KeyT &data = KeyT(),
		CsBTreeNode<KeyT> *parent = NULL,
		CsBTreeNode<KeyT> *left = NULL,
		CsBTreeNode<KeyT> *right = NULL,
		COLOR color = COLOR_BLACK);
	virtual ~CsRBTreeNode();
	virtual CsBTreeNode<KeyT> *Copy() const;
};

/// 红黑树
template<typename KeyT, typename CompareT = CsCompareF<KeyT >>
class CsRBTree : public CsBSTree<KeyT, CompareT>
{
public:
	virtual ~CsRBTree();

	/// 插入一个数据
	/// 如果改变了Node的结构，Insert方法需要重新实现
	virtual Node *Insert(const KeyT &data);

	/// 删除一个数据
	virtual Node *Delete(const KeyT &data);

private:
	CsRBTree_Private<KeyT, CompareT> m_tRBTree_Private;
};

/// 红黑树功能实现类
template<typename KeyT, typename CompareT>
class CsRBTree_Private
{
	friend class CsRBTree<KeyT, CompareT>;
private:
	typedef CsBTreeNode<KeyT> Node;

	// 直接插入，可能会破坏红黑树的性质
	// insert指示是否完成了插入操作，若data值与原本的值相同，则不会进行插入操作
	Node *InsertNoCheck(const KeyT &data, Node *&p, Node *&root, cs_bool &insert);
	void InsertFixUp(Node *&p, Node *&root);

	cs_bool RotateLeft(Node *&p, Node *&root); // 左旋
	cs_bool RotateRight(Node *&p, Node *&root); // 右旋

private:
	CompareT m_fCompare;
};

template<typename KeyT>
inline CsRBTreeNode<KeyT>::CsRBTreeNode(
	const KeyT &data,
	CsBTreeNode<KeyT> *parent,
	CsBTreeNode<KeyT> *left,
	CsBTreeNode<KeyT> *right,
	COLOR color)
	: CsBTreeNode(data, parent, left, right)
	, m_nColor(color)
{

}

template<typename KeyT>
inline CsRBTreeNode<KeyT>::~CsRBTreeNode()
{

}

template<typename KeyT>
CsBTreeNode<KeyT> *CsRBTreeNode<KeyT>::Copy() const
{
	CsRBTreeNode<KeyT> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsRBTreeNode<KeyT>(m_tData, m_pParent, NULL, NULL, (COLOR)m_nColor);
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

template<typename KeyT, typename CompareT>
inline CsRBTree<KeyT, CompareT>::~CsRBTree()
{

}

template<typename KeyT, typename CompareT>
inline CsBTreeNode<KeyT> *CsRBTree<KeyT, CompareT>::Insert(const KeyT &data)
{
	cs_bool insert = false;
	CsBTreeNode<KeyT> *p = m_tRBTree_Private.InsertNoCheck(data, GetRoot(), GetRoot(), insert);
	if (!insert)
	{
		// 没有实际插入，不会影响结构
		return p;
	}
	m_tRBTree_Private.InsertFixUp(p, GetRoot());
	return p;
}

template<typename KeyT, typename CompareT>
inline CsBTreeNode<KeyT> *CsRBTree<KeyT, CompareT>::Delete(const KeyT &data)
{
	CsBTreeNode<KeyT> *p = CsBSTree<KeyT, CompareT>::Delete(data);
	return p;
}

template<typename KeyT, typename CompareT>
inline CsBTreeNode<KeyT> *CsRBTree_Private<KeyT, CompareT>::InsertNoCheck(const KeyT &data, CsBTreeNode<KeyT> *&p, CsBTreeNode<KeyT> *&root, cs_bool &insert)
{
	if (NULL == p)
	{
		insert = true;
		try
		{
			// 新建的节点为红色
			p = new CsRBTreeNode<KeyT>(data, NULL, NULL, NULL, CsRBTreeNode<KeyT>::COLOR_RED);
		}
		catch (std::bad_alloc&)
		{
			insert = false;
			return NULL;
		}
		if (NULL == root)
		{
			root = p;
		}
		return p;
	}

	cs_int ret = m_fCompare(data, p->m_tData);
	if (ret < 0)
	{
		p->m_pLeft = InsertNoCheck(data, p->m_pLeft, root, insert);
		if (p->m_pLeft)
		{
			p->m_pLeft->m_pParent = p;
		}
	}
	else if (ret > 0)
	{
		p->m_pRight = InsertNoCheck(data, p->m_pRight, root, insert);
		if (p->m_pRight)
		{
			p->m_pRight->m_pParent = p;
		}
	}
	return p;
}

template<typename KeyT, typename CompareT>
inline void CsRBTree_Private<KeyT, CompareT>::InsertFixUp(CsBTreeNode<KeyT> *&p, CsBTreeNode<KeyT> *&root)
{
	if (!p || !root)
	{
		return;
	}
	CsRBTreeNode<KeyT> *node = (CsRBTreeNode<KeyT>*)p;
	if (node == root)
	{
		node->m_nColor = CsRBTreeNode<KeyT>::COLOR_BLACK;
		return;
	}
	CsRBTreeNode<KeyT> *pnode = (CsRBTreeNode<KeyT>*)(node->m_pParent); // 双亲节点
	if (pnode == root)
	{
		return;
	}

	if (pnode->m_nColor == CsRBTreeNode<KeyT>::COLOR_RED)
	{
		CsRBTreeNode<KeyT> *unode = NULL; // 叔叔节点
		if (pnode == pnode->m_pParent->m_pLeft)
		{
			// 叔叔是祖父的右孩子
			unode = (CsRBTreeNode<KeyT>*)(pnode->m_pParent->m_pRight);
		}
		else
		{
			// 叔叔是祖父的左孩子
			unode = (CsRBTreeNode<KeyT>*)(pnode->m_pParent->m_pLeft);
		}
	}
}

template<typename KeyT, typename CompareT>
cs_bool CsRBTree_Private<KeyT, CompareT>::RotateLeft(CsBTreeNode<KeyT> *&p, CsBTreeNode<KeyT> *&root)
{
	if (p == NULL || p->m_pRight == NULL)
	{
		// 不能旋转
		return false;
	}
	CsBTreeNode<KeyT> *node = p->m_pRight;
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

template<typename KeyT, typename CompareT>
cs_bool CsRBTree_Private<KeyT, CompareT>::RotateRight(CsBTreeNode<KeyT> *&p, CsBTreeNode<KeyT> *&root)
{
	if (p == NULL || p->m_pLeft == NULL)
	{
		// 不能旋转
		return false;
	}
	CsBTreeNode<KeyT> *node = p->m_pLeft;
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