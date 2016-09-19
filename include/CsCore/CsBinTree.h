/////////////////////////////////////////////////////////////////////////////////
/// @brief 二叉树（binary tree）
/// 
///  二叉树的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_BINARY_TREE_H_
#define _CORE_BINARY_TREE_H_

#include "CsObject.h"

template<typename KeyT, typename NodeT> class CsBTree_Private;

/// 二叉树节点
template<typename KeyT>
struct CsBinTreeNode :public CsObject
{
	KeyT m_tKey;					// 数据，需要由外部去析构，否则可能造成内存泄露
	CsBinTreeNode<KeyT> *m_pParent;	// 双亲
	CsBinTreeNode<KeyT> *m_pLeft;		// 左孩子
	CsBinTreeNode<KeyT> *m_pRight;	// 右孩子

	CsBinTreeNode(
		const KeyT &key = KeyT(),
		CsBinTreeNode<KeyT> *parent = NULL,
		CsBinTreeNode<KeyT> *left = NULL,
		CsBinTreeNode<KeyT> *right = NULL);
	virtual ~CsBinTreeNode();
	virtual CsBinTreeNode<KeyT> *Copy() const;
};

/// 二叉树
template<typename KeyT, 
	typename NodeT = CsBinTreeNode<KeyT>>
class CsBinTree :public CsObject
{
public:
	typedef cs_void(*funtype)(const KeyT&);

public:
	CsBinTree(NodeT *pRoot = NULL);
	CsBinTree(const CsBinTree<KeyT, NodeT> &tTree);
	virtual ~CsBinTree();
	CsBinTree<KeyT, NodeT>& operator=(const CsBinTree<KeyT, NodeT> &tTree);
	cs_void CopyFrom(const CsBinTree<KeyT, NodeT> &tTree);
	cs_void Attach(NodeT *pNode);
	cs_void Destroy();

public:
	KeyT &GetNodeKey(NodeT *pNode);
	KeyT GetNodeKey(const NodeT *pNode) const;
	cs_void SetNodeKey(NodeT *pNode, const KeyT &tKey);
	NodeT *&GetRoot();
	NodeT *GetRoot() const;
	NodeT *&GetParent(NodeT *pNode);
	NodeT *GetParent(const NodeT *pNode) const;
	NodeT *&GetLeftChild(NodeT *pNode);
	NodeT *GetLeftChild(const NodeT *pNode) const;
	NodeT *&GetRightChild(NodeT *pNode);
	NodeT *GetRightChild(const NodeT *pNode) const;
	NodeT *&GetLeftSibling(NodeT *pNode);
	NodeT *GetLeftSiblig(const NodeT *pNode) const;
	NodeT *&GetRightSibling(NodeT *pNode);
	NodeT *GetRightSibling(const NodeT *pNode) const;
	cs_bool IsEmpty() const;

public:
	// 先（根）序遍历
	cs_void PreOrderTraverse(funtype fVisit) const;

	// 中（根）序遍历
	cs_void InOrderTraverse(funtype fVisit) const;

	// 后（根）序遍历
	cs_void PostOrderTraverse(funtype fVisit) const;
	cs_size_t GetNodeCount() const;
	cs_size_t GetLeafCount() const;
	cs_size_t GetDepth() const;

private:
	NodeT *m_pRoot;
	CsBTree_Private<KeyT, NodeT> m_tBTree_Private;
};

/// 二叉树功能实现类
template<typename KeyT, typename NodeT>
class CsBTree_Private
{
	friend class CsBinTree<KeyT, NodeT>;

private:
	typedef cs_void(*funtype)(const KeyT&);
	cs_void DestroySubTree(NodeT *pNode);
	cs_void PreOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	cs_void InOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	cs_void PostOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	cs_void GetNodeCount(const NodeT *pNode, cs_size_t *nCount) const;
	cs_void GetLeafCount(const NodeT *pNode, cs_size_t *nCount) const;
	cs_size_t GetDepth(const NodeT *pNode) const;
};

template<typename KeyT>
inline CsBinTreeNode<KeyT>::CsBinTreeNode(
	const KeyT &tKey,
	CsBinTreeNode<KeyT> *pParent, 
	CsBinTreeNode<KeyT> *pLeft, 
	CsBinTreeNode<KeyT> *pRight) 
	: m_tKey(tKey)
	, m_pParent(pParent)
	, m_pLeft(pLeft)
	, m_pRight(pRight) 
{

}

template<typename KeyT>
inline CsBinTreeNode<KeyT>::~CsBinTreeNode()
{
	if (m_pParent)
	{
		if (this == m_pParent->m_pLeft)
		{
			m_pParent->m_pLeft = NULL;
		}
		else
		{
			m_pParent->m_pRight = NULL;
		}
	}
	if (m_pLeft)
	{
		delete m_pLeft;
	}
	if (m_pRight)
	{
		delete m_pRight;
	}
}

template<typename KeyT>
CsBinTreeNode<KeyT> *CsBinTreeNode<KeyT>::Copy() const
{
	CsBinTreeNode<KeyT> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsBinTreeNode<KeyT>(m_tKey, m_pParent, NULL, NULL);
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

template<typename KeyT, typename NodeT>
inline CsBinTree<KeyT, NodeT>::CsBinTree(NodeT *pRoot)
: m_pRoot(pRoot)
{
	
}

template<typename KeyT, typename NodeT>
inline CsBinTree<KeyT, NodeT>::CsBinTree(const CsBinTree<KeyT, NodeT> &tTree) 
: m_pRoot(NULL)
{
	CopyFrom(tTree);
}

template<typename KeyT, typename NodeT>
inline CsBinTree<KeyT, NodeT>::~CsBinTree()
{
	Destroy();
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::Attach(NodeT *pNode)
{
	CS_ASSERT(pNode);
	if (m_pRoot != NULL)
	{
		Destroy();
	}
	m_pRoot = pNode;
}

template<typename KeyT, typename NodeT>
inline CsBinTree<KeyT, NodeT>& CsBinTree<KeyT, NodeT>::operator=(const CsBinTree<KeyT, NodeT> &tTree)
{
	CopyFrom(tTree);
	return *this;
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::CopyFrom(const CsBinTree<KeyT, NodeT> &tTree)
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
		m_pRoot = tTree.m_pRoot->Copy();
	}
	else
	{
		m_pRoot = NULL;
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::Destroy()
{
	m_tBTree_Private.DestroySubTree(m_pRoot);
	m_pRoot = NULL;
}

template<typename KeyT, typename NodeT>
inline NodeT *&CsBinTree<KeyT, NodeT>::GetLeftChild(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pLeft));
}

template<typename KeyT, typename NodeT>
inline NodeT *CsBinTree<KeyT, NodeT>::GetLeftChild(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pLeft;
}

template<typename KeyT, typename NodeT>
inline NodeT *&CsBinTree<KeyT, NodeT>::GetRightChild(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pRight));
}

template<typename KeyT, typename NodeT>
inline NodeT *CsBinTree<KeyT, NodeT>::GetRightChild(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pRight;
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBinTree<KeyT, NodeT>::GetLeftSibling(NodeT *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pLeft));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBinTree<KeyT, NodeT>::GetLeftSiblig(const NodeT *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pLeft;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBinTree<KeyT, NodeT>::GetRightSibling(NodeT *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pRight));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBinTree<KeyT, NodeT>::GetRightSibling(const NodeT *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pRight;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBinTree<KeyT, NodeT>::GetParent(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pParent));
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBinTree<KeyT, NodeT>::GetParent(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pParent;
}

template<typename KeyT, typename NodeT>
inline KeyT& CsBinTree<KeyT, NodeT>::GetNodeKey(NodeT *p)
{
	CS_ASSERT(p);
	return p->m_tKey;
}

template<typename KeyT, typename NodeT>
inline KeyT CsBinTree<KeyT, NodeT>::GetNodeKey(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_tKey;
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::SetNodeKey(NodeT *p, const KeyT &key)
{
	CS_ASSERT(p);
	p->m_tKey = key;
}

template<typename KeyT, typename NodeT>
inline cs_bool CsBinTree<KeyT, NodeT>::IsEmpty() const
{
	return NULL == m_pRoot;
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBinTree<KeyT, NodeT>::GetRoot()
{
	return *(&(m_pRoot));
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBinTree<KeyT, NodeT>::GetRoot() const
{
	return m_pRoot;
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::PreOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PreOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::InOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.InOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline cs_void CsBinTree<KeyT, NodeT>::PostOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PostOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBinTree<KeyT, NodeT>::GetNodeCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetNodeCount(m_pRoot, &unCount);
	return unCount;
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBinTree<KeyT, NodeT>::GetLeafCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetLeafCount(m_pRoot, &unCount);
	return unCount;
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBinTree<KeyT, NodeT>::GetDepth() const
{
	// Minus 1 here because I think the root node's depth should be 0.  
	// So, don't do it if u think the root node's depth should be 1.  
	return m_tBTree_Private.GetDepth(m_pRoot) - 1;
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::DestroySubTree(NodeT *p)
{
	if (p)
	{
		DestroySubTree(p->m_pLeft);
		DestroySubTree(p->m_pRight);
		delete p;
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::PreOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		fVisit(p->m_tKey);
		PreOrderTraverse(p->m_pLeft, fVisit);
		PreOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::InOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		InOrderTraverse(p->m_pLeft, fVisit);
		fVisit(p->m_tKey);
		InOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::PostOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		PostOrderTraverse(p->m_pLeft, fVisit);
		PostOrderTraverse(p->m_pRight, fVisit);
		fVisit(p->m_tKey);
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::GetNodeCount(
	const NodeT *p,
	cs_size_t *unCount
	) const
{
	CS_ASSERT(unCount);

	cs_size_t unLeftCount;
	cs_size_t unRightCount;

	if (NULL == p)
		*unCount = 0;
	else if ((NULL == p->m_pLeft) && (NULL == p->m_pRight))
		*unCount = 1;
	else
	{
		GetNodeCount(p->m_pLeft, &unLeftCount);
		GetNodeCount(p->m_pRight, &unRightCount);
		*unCount = 1 + unLeftCount + unRightCount;
	}
}

template<typename KeyT, typename NodeT>
inline cs_void CsBTree_Private<KeyT, NodeT>::GetLeafCount(
	const NodeT *p,
	cs_size_t *unCount
	) const
{
	CS_ASSERT(unCount);

	if (p)
	{
		// if the node's left & right children are both NULL, it must be a leaf  
		if ((NULL == p->m_pLeft) && (NULL == p->m_pRight))
			++(*unCount);
		GetLeafCount(p->m_pLeft, unCount);
		GetLeafCount(p->m_pRight, unCount);
	}
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBTree_Private<KeyT, NodeT>::GetDepth(const NodeT *p) const
{
	cs_size_t unDepthLeft;
	cs_size_t unDepthRight;

	if (p)
	{
		unDepthLeft = GetDepth(p->m_pLeft);
		unDepthRight = GetDepth(p->m_pRight);
		return 1 +  // if don't plus 1 here, the tree's depth will be always 0  
			(unDepthLeft > unDepthRight ? unDepthLeft : unDepthRight);
	}
	else
		return 0;
}

#endif // _CORE_BINARY_TREE_H_