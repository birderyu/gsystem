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

template<typename T, typename CompareT> class CsBSTree_Private;

/// 二叉排序树
template<typename T, typename CompareT = CsCompareF<T >>
class CsBSTree : public CsBTree<T>
{
public:
	virtual ~CsBSTree();
	Node *Find(const T &data) const;
	Node *FindMin() const;
	Node *FindMax() const;

	/// 插入一个数据，返回插入数据的节点
	/// 如果改变了Node的结构，Insert方法需要重新实现
	virtual Node *Insert(const T &data);

	/// 删除一个数据，返回删除数据的节点（TODO：这个需求暂未能实现）
	virtual Node *Delete(const T &data);

private:
	CsBSTree_Private<T, CompareT> m_tBSTree_Private;
};

/// 二叉排序树功能实现类
template<typename T, typename CompareT>
class CsBSTree_Private
{
	friend class CsBSTree<T, CompareT>;
private:
	typedef CsBTreeNode<T> Node;
	Node *Find(const T &data, Node *p) const;
	Node *FindMin(Node *p) const;
	Node *FindMax(Node *p) const;
	Node *Insert(const T &data, Node *&p, Node *&root);
	Node *Delete(const T &data, Node *&p, Node *&root, Node *&node);
	cs_bool SwitchNode(Node *node1, Node *node2);

private:
	CompareT m_fCompare;
};

template<typename T, typename CompareT>
inline CsBSTree<T, CompareT>::~CsBSTree()
{

}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree<T, CompareT>::Find(const T &data) const
{
	return m_tBSTree_Private.Find(data, GetRoot());
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree<T, CompareT>::FindMin() const
{
	return m_tBSTree_Private.FindMin(GetRoot());
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree<T, CompareT>::FindMax() const
{
	return m_tBSTree_Private.FindMax(GetRoot());
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree<T, CompareT>::Insert(const T &data)
{
	return m_tBSTree_Private.Insert(data, GetRoot(), GetRoot());
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree<T, CompareT>::Delete(const T &data)
{
	CsBTreeNode<T>* node = NULL;
	m_tBSTree_Private.Delete(data, GetRoot(), GetRoot(), node);
	return node;
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree_Private<T, CompareT>::Find(const T &data, CsBTreeNode<T> *p) const
{
	if (NULL == p)
	{
		return NULL;
	}
	cs_int ret = m_fCompare(data, p->m_tData);
	if (ret < 0)
	{
		return Find(data, p->m_pLeft);
	}
	else if (ret > 0)
	{
		return Find(data, p->m_pRight);
	}
	else
	{
		return p;
	}
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree_Private<T, CompareT>::FindMin(CsBTreeNode<T> *p) const
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
		return FindMin(p->m_pLeft);
	}
}

template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree_Private<T, CompareT>::FindMax(CsBTreeNode<T> *p) const
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
		return FindMax(p->m_pRight);
	}
}


//返回值：如果p为NULL，则返回值为新分配内存的指针；如果p不是NULL，则返回值即为p.  
template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree_Private<T, CompareT>::Insert(const T &data, CsBTreeNode<T> *&p, CsBTreeNode<T> *&root)
{
	if (NULL == p)
	{
		try
		{
			p = new CsBTreeNode<T>(data, NULL, NULL, NULL);
		}
		catch (std::bad_alloc&)
		{
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
		p->m_pLeft = Insert(data, p->m_pLeft, root);
		if (p->m_pLeft)
		{
			p->m_pLeft->m_pParent = p;
		}
	}
	else if (ret > 0)
	{
		p->m_pRight = Insert(data, p->m_pRight, root);
		if (p->m_pRight)
		{
			p->m_pRight->m_pParent = p;
		}
	}
	return p;
}

//返回值：如果节点p的数据与data不等，则返回值即为p;如果相等，但有两个子节点，返回值也为p，有一个子节点，返回值为该子节点指针，  
//如果无节点，返回值NULL。  
//node为待删除的节点
template<typename T, typename CompareT>
inline CsBTreeNode<T>* CsBSTree_Private<T, CompareT>::Delete(const T &data, CsBTreeNode<T> *&p, CsBTreeNode<T> *&root, CsBTreeNode<T> *&node)
{
	if (NULL == p)
	{
		// Error! data not found!
		return p;
	}
	
	cs_int ret = m_fCompare(data, p->m_tData);
	if (ret < 0)
	{
		p->m_pLeft = Delete(data, p->m_pLeft, root, node);
	}
	else if (ret > 0)
	{
		p->m_pRight = Delete(data, p->m_pRight, root, node);
	}
	else
	{
		// 查找成功
		if (p->m_pLeft && p->m_pRight)
		{
			// 有两个孩子
			// 注意为节点（Node*）的调换，而非节点值（Node->Data）的调换，以追求效率，并且避免内存泄露
			CsBTreeNode<T> *tmp = FindMin(p->m_pRight);
			SwitchNode(p, tmp);
			if (root == p)
			{
				root = tmp;
			}
			p->m_pRight = Delete(data, tmp->m_pRight, root, node);
		}
		else
		{
			// 查找成功，并且它没有孩子或只有一个孩子
			node = p;
			if (NULL == p->m_pLeft)
			{
				p = p->m_pRight;
			}
			else if (NULL == p->m_pRight)
			{
				p = p->m_pLeft;
			}
			if (p)
			{
				p->m_pParent = node->m_pParent;
			}
			if (root == node)
			{
				root = p;
			}
			// delete pTmp; 交由外界去删除
		}
	}
	return p;
}

template<typename T, typename CompareT>
inline cs_bool CsBSTree_Private<T, CompareT>::SwitchNode(CsBTreeNode<T> *node1, CsBTreeNode<T> *node2)
{
	if (!node1 || !node2)
	{
		return false;
	}
	if (node1 == node2)
	{
		return true;
	}
	CsBTreeNode<T> *pnode1 = node1->m_pParent;
	CsBTreeNode<T> *pnode2 = node2->m_pParent;

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

	CsBTreeNode<T> *tmp = node1->m_pLeft;
	node1->m_pLeft = node2->m_pLeft;
	node2->m_pLeft = tmp;

	tmp = node1->m_pRight;
	node1->m_pRight = node2->m_pRight;
	node2->m_pRight = tmp;
	return true;
}

#endif // _CORE_BINARY_SORT_TREE_H_