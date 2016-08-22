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
struct CsBTreeNode :public CsObject
{
	KeyT m_tKey;					// 数据，需要由外部去析构，否则可能造成内存泄露
	CsBTreeNode<KeyT> *m_pParent;	// 双亲
	CsBTreeNode<KeyT> *m_pLeft;		// 左孩子
	CsBTreeNode<KeyT> *m_pRight;	// 右孩子

	CsBTreeNode(
		const KeyT &key = KeyT(),
		CsBTreeNode<KeyT> *parent = NULL,
		CsBTreeNode<KeyT> *left = NULL,
		CsBTreeNode<KeyT> *right = NULL);
	virtual ~CsBTreeNode();
	virtual CsBTreeNode<KeyT> *Copy() const;
};

/// 二叉树
template<typename KeyT, 
	typename NodeT = CsBTreeNode<KeyT>>
class CsBTree :public CsObject
{
public:
	typedef void(*funtype)(const KeyT&);

public:
	CsBTree(NodeT *pRoot = NULL);
	CsBTree(const CsBTree<KeyT, NodeT> &tTree);
	virtual ~CsBTree();
	CsBTree<KeyT, NodeT>& operator=(const CsBTree<KeyT, NodeT> &tTree);
	void Clone(const CsBTree<KeyT, NodeT> &tTree);
	void Attach(NodeT *pNode);
	void Destroy();

public:
	KeyT &GetNodeKey(NodeT *pNode);
	KeyT GetNodeKey(const NodeT *pNode) const;
	void SetNodeKey(NodeT *pNode, const KeyT &tKey);
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
	void PreOrderTraverse(funtype fVisit) const;

	// 中（根）序遍历
	void InOrderTraverse(funtype fVisit) const;

	// 后（根）序遍历
	void PostOrderTraverse(funtype fVisit) const;
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
	friend class CsBTree<KeyT, NodeT>;

private:
	typedef void(*funtype)(const KeyT&);
	void DestroySubTree(NodeT *pNode);
	void PreOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	void InOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	void PostOrderTraverse(const NodeT *pNode, funtype fVisit) const;
	void GetNodeCount(const NodeT *pNode, cs_size_t *nCount) const;
	void GetLeafCount(const NodeT *pNode, cs_size_t *nCount) const;
	cs_size_t GetDepth(const NodeT *pNode) const;
};

template<typename KeyT>
inline CsBTreeNode<KeyT>::CsBTreeNode(
	const KeyT &tKey,
	CsBTreeNode<KeyT> *pParent, 
	CsBTreeNode<KeyT> *pLeft, 
	CsBTreeNode<KeyT> *pRight) 
	: m_tKey(tKey)
	, m_pParent(pParent)
	, m_pLeft(pLeft)
	, m_pRight(pRight) 
{

}

template<typename KeyT>
inline CsBTreeNode<KeyT>::~CsBTreeNode()
{

}

template<typename KeyT>
CsBTreeNode<KeyT> *CsBTreeNode<KeyT>::Copy() const
{
	CsBTreeNode<KeyT> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsBTreeNode<KeyT>(m_tKey, m_pParent, NULL, NULL);
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
inline CsBTree<KeyT, NodeT>::CsBTree(NodeT *pRoot)
: m_pRoot(pRoot)
{
	
}

template<typename KeyT, typename NodeT>
inline CsBTree<KeyT, NodeT>::CsBTree(const CsBTree<KeyT, NodeT> &tTree) 
: m_pRoot(NULL)
{
	Clone(tTree);
}

template<typename KeyT, typename NodeT>
inline CsBTree<KeyT, NodeT>::~CsBTree()
{
	Destroy();
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::Attach(NodeT *pNode)
{
	CS_ASSERT(pNode);
	if (m_pRoot != NULL)
	{
		Destroy();
	}
	m_pRoot = pNode;
}

template<typename KeyT, typename NodeT>
inline CsBTree<KeyT, NodeT>& CsBTree<KeyT, NodeT>::operator=(const CsBTree<KeyT, NodeT> &tTree)
{
	Clone(tTree);
	return *this;
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::Clone(const CsBTree<KeyT, NodeT> &tTree)
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
inline void CsBTree<KeyT, NodeT>::Destroy()
{
	m_tBTree_Private.DestroySubTree(m_pRoot);
	m_pRoot = NULL;
}

template<typename KeyT, typename NodeT>
inline NodeT *&CsBTree<KeyT, NodeT>::GetLeftChild(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pLeft));
}

template<typename KeyT, typename NodeT>
inline NodeT *CsBTree<KeyT, NodeT>::GetLeftChild(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pLeft;
}

template<typename KeyT, typename NodeT>
inline NodeT *&CsBTree<KeyT, NodeT>::GetRightChild(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pRight));
}

template<typename KeyT, typename NodeT>
inline NodeT *CsBTree<KeyT, NodeT>::GetRightChild(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pRight;
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBTree<KeyT, NodeT>::GetLeftSibling(NodeT *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pLeft));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBTree<KeyT, NodeT>::GetLeftSiblig(const NodeT *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pLeft;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBTree<KeyT, NodeT>::GetRightSibling(NodeT *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pRight));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBTree<KeyT, NodeT>::GetRightSibling(const NodeT *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pRight;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBTree<KeyT, NodeT>::GetParent(NodeT *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pParent));
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBTree<KeyT, NodeT>::GetParent(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_pParent;
}

template<typename KeyT, typename NodeT>
inline KeyT& CsBTree<KeyT, NodeT>::GetNodeKey(NodeT *p)
{
	CS_ASSERT(p);
	return p->m_tKey;
}

template<typename KeyT, typename NodeT>
inline KeyT CsBTree<KeyT, NodeT>::GetNodeKey(const NodeT *p) const
{
	CS_ASSERT(p);
	return p->m_tKey;
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::SetNodeKey(NodeT *p, const KeyT &key)
{
	CS_ASSERT(p);
	p->m_tKey = key;
}

template<typename KeyT, typename NodeT>
inline cs_bool CsBTree<KeyT, NodeT>::IsEmpty() const
{
	return NULL == m_pRoot;
}

template<typename KeyT, typename NodeT>
inline NodeT*& CsBTree<KeyT, NodeT>::GetRoot()
{
	return *(&(m_pRoot));
}

template<typename KeyT, typename NodeT>
inline NodeT* CsBTree<KeyT, NodeT>::GetRoot() const
{
	return m_pRoot;
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::PreOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PreOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::InOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.InOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline void CsBTree<KeyT, NodeT>::PostOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PostOrderTraverse(m_pRoot, fVisit);
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBTree<KeyT, NodeT>::GetNodeCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetNodeCount(m_pRoot, &unCount);
	return unCount;
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBTree<KeyT, NodeT>::GetLeafCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetLeafCount(m_pRoot, &unCount);
	return unCount;
}

template<typename KeyT, typename NodeT>
inline cs_size_t CsBTree<KeyT, NodeT>::GetDepth() const
{
	// Minus 1 here because I think the root node's depth should be 0.  
	// So, don't do it if u think the root node's depth should be 1.  
	return m_tBTree_Private.GetDepth(m_pRoot) - 1;
}

template<typename KeyT, typename NodeT>
inline void CsBTree_Private<KeyT, NodeT>::DestroySubTree(NodeT *p)
{
	if (p)
	{
		DestroySubTree(p->m_pLeft);
		DestroySubTree(p->m_pRight);
		delete p;
	}
}

template<typename KeyT, typename NodeT>
inline void CsBTree_Private<KeyT, NodeT>::PreOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		fVisit(p->m_tKey);
		PreOrderTraverse(p->m_pLeft, fVisit);
		PreOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename KeyT, typename NodeT>
inline void CsBTree_Private<KeyT, NodeT>::InOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		InOrderTraverse(p->m_pLeft, fVisit);
		fVisit(p->m_tKey);
		InOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename KeyT, typename NodeT>
inline void CsBTree_Private<KeyT, NodeT>::PostOrderTraverse(const NodeT *p, funtype fVisit) const
{
	if (p)
	{
		PostOrderTraverse(p->m_pLeft, fVisit);
		PostOrderTraverse(p->m_pRight, fVisit);
		fVisit(p->m_tKey);
	}
}

template<typename KeyT, typename NodeT>
inline void CsBTree_Private<KeyT, NodeT>::GetNodeCount(
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
inline void CsBTree_Private<KeyT, NodeT>::GetLeafCount(
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