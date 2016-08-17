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

template<typename T> class CsBTree;
template<typename T> class CsBTree_Private;

/// 二叉树节点
template<typename T>
struct CsBTreeNode :public CsObject
{
	T m_tData;					// 数据，需要由外部去析构，否则可能造成内存泄露
	CsBTreeNode<T> *m_pParent;	// 双亲
	CsBTreeNode<T> *m_pLeft;	// 左孩子
	CsBTreeNode<T> *m_pRight;	// 右孩子

	CsBTreeNode(
		const T &data = T(),
		CsBTreeNode<T> *parent = NULL,
		CsBTreeNode<T> *left = NULL,
		CsBTreeNode<T> *right = NULL);
	virtual ~CsBTreeNode();
	virtual CsBTreeNode<T> *Copy() const;
};

/// 二叉树
template<typename T>
class CsBTree :public CsObject
{
public:
	typedef CsBTreeNode<T> Node;
	typedef void(*funtype)(const T&);

public:
	CsBTree(Node *pRoot = NULL);
	CsBTree(const CsBTree<T> &tTree);
	virtual ~CsBTree();
	CsBTree<T>& operator=(const CsBTree<T> &tTree);
	void Clone(const CsBTree<T> &tTree);
	void Attach(Node *pNode);
	void Destroy();

public:
	T &GetNodeData(Node *pNode);
	T GetNodeData(const Node *pNode) const;
	void SetNodeData(Node *pNode, const T &tData);
	Node *&GetRoot();
	Node *GetRoot() const;
	Node *&GetParent(Node *pNode);
	Node *GetParent(const Node *pNode) const;
	Node *&GetLeftChild(Node *pNode);
	Node *GetLeftChild(const Node *pNode) const;
	Node *&GetRightChild(Node *pNode);
	Node *GetRightChild(const Node *pNode) const;
	Node *&GetLeftSibling(Node *pNode);
	Node *GetLeftSiblig(const Node *pNode) const;
	Node *&GetRightSibling(Node *pNode);
	Node *GetRightSibling(const Node *pNode) const;
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
	Node *m_pNodeRoot;
	CsBTree_Private<T> m_tBTree_Private;
};

/// 二叉树功能实现类
template<typename T>
class CsBTree_Private
{
	friend class CsBTree<T>;

private:
	typedef CsBTreeNode<T> Node;
	typedef void(*funtype)(const T&);
	void DestroySubTree(Node *pNode);
	void PreOrderTraverse(const Node *pNode, funtype fVisit) const;
	void InOrderTraverse(const Node *pNode, funtype fVisit) const;
	void PostOrderTraverse(const Node *pNode, funtype fVisit) const;
	void GetNodeCount(const Node *pNode, cs_size_t *nCount) const;
	void GetLeafCount(const Node *pNode, cs_size_t *nCount) const;
	cs_size_t GetDepth(const Node *pNode) const;
};

template<typename T>
inline CsBTreeNode<T>::CsBTreeNode(
	const T &tData, 
	CsBTreeNode<T> *pParent, 
	CsBTreeNode<T> *pLeft, 
	CsBTreeNode<T> *pRight) 
	: m_tData(tData)
	, m_pParent(pParent)
	, m_pLeft(pLeft)
	, m_pRight(pRight) 
{

}

template<typename T>
inline CsBTreeNode<T>::~CsBTreeNode()
{

}

template<typename T>
CsBTreeNode<T> *CsBTreeNode<T>::Copy() const
{
	CsBTreeNode<T> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsBTreeNode<T>(m_tData, m_pParent, NULL, NULL);
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

template<typename T>
inline CsBTree<T>::CsBTree(CsBTreeNode<T> *pRoot)
: m_pNodeRoot(pRoot)
{
	
}

template<typename T>
inline CsBTree<T>::CsBTree(const CsBTree<T> &tTree) 
: m_pNodeRoot(NULL)
{
	Clone(tTree);
}

template<typename T>
inline CsBTree<T>::~CsBTree()
{
	Destroy();
}

template<typename T>
inline void CsBTree<T>::Attach(CsBTreeNode<T> *pNode)
{
	CS_ASSERT(pNode);
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	m_pNodeRoot = pNode;
}

template<typename T>
inline CsBTree<T>& CsBTree<T>::operator=(const CsBTree<T> &tTree)
{
	Clone(tTree);
	return *this;
}

template<typename T>
inline void CsBTree<T>::Clone(const CsBTree<T> &tTree)
{
	if (this == &tTree)
	{
		return;
	}
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	if (NULL != tTree.m_pNodeRoot)
	{
		m_pNodeRoot = tTree.m_pNodeRoot->Copy();
	}
	else
	{
		m_pNodeRoot = NULL;
	}
}

template<typename T>
inline void CsBTree<T>::Destroy()
{
	m_tBTree_Private.DestroySubTree(m_pNodeRoot);
	m_pNodeRoot = NULL;
}

template<typename T>
inline CsBTreeNode<T> *&CsBTree<T>::GetLeftChild(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pLeft));
}

template<typename T>
inline CsBTreeNode<T> *CsBTree<T>::GetLeftChild(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);
	return p->m_pLeft;
}

template<typename T>
inline CsBTreeNode<T> *&CsBTree<T>::GetRightChild(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pRight));
}

template<typename T>
inline CsBTreeNode<T> *CsBTree<T>::GetRightChild(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);
	return p->m_pRight;
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetLeftSibling(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pLeft));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetLeftSiblig(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pLeft;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetRightSibling(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->m_pRight));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetRightSibling(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->m_pRight;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetParent(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);
	return *(&(p->m_pParent));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetParent(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);
	return p->m_pParent;
}

template<typename T>
inline T& CsBTree<T>::GetNodeData(CsBTreeNode<T> *p)
{
	CS_ASSERT(p);
	return p->m_tData;
}

template<typename T>
inline T CsBTree<T>::GetNodeData(const CsBTreeNode<T> *p) const
{
	CS_ASSERT(p);
	return p->m_tData;
}

template<typename T>
inline void CsBTree<T>::SetNodeData(CsBTreeNode<T> *p, const T &data)
{
	CS_ASSERT(p);
	p->m_tData = data;
}

template<typename T>
inline cs_bool CsBTree<T>::IsEmpty() const
{
	return NULL == m_pNodeRoot;
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetRoot()
{
	return *(&(m_pNodeRoot));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetRoot() const
{
	return m_pNodeRoot;
}

template<typename T>
inline void CsBTree<T>::PreOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PreOrderTraverse(m_pNodeRoot, fVisit);
}

template<typename T>
inline void CsBTree<T>::InOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.InOrderTraverse(m_pNodeRoot, fVisit);
}

template<typename T>
inline void CsBTree<T>::PostOrderTraverse(funtype fVisit) const
{
	m_tBTree_Private.PostOrderTraverse(m_pNodeRoot, fVisit);
}

template<typename T>
inline cs_size_t CsBTree<T>::GetNodeCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetNodeCount(m_pNodeRoot, &unCount);
	return unCount;
}

template<typename T>
inline cs_size_t CsBTree<T>::GetLeafCount() const
{
	cs_size_t unCount = 0;
	m_tBTree_Private.GetLeafCount(m_pNodeRoot, &unCount);
	return unCount;
}

template<typename T>
inline unsigned int CsBTree<T>::GetDepth() const
{
	// Minus 1 here because I think the root node's depth should be 0.  
	// So, don't do it if u think the root node's depth should be 1.  
	return m_tBTree_Private.GetDepth(m_pNodeRoot) - 1;
}

template<typename T>
inline void CsBTree_Private<T>::DestroySubTree(CsBTreeNode<T> *p)
{
	if (p)
	{
		DestroySubTree(p->m_pLeft);
		DestroySubTree(p->m_pRight);
		delete p;
	}
}

template<typename T>
inline void CsBTree_Private<T>::PreOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		fVisit(p->m_tData);
		PreOrderTraverse(p->m_pLeft, fVisit);
		PreOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename T>
inline void CsBTree_Private<T>::InOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		InOrderTraverse(p->m_pLeft, fVisit);
		fVisit(p->m_tData);
		InOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename T>
inline void CsBTree_Private<T>::PostOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		PostOrderTraverse(p->m_pLeft, fVisit);
		PostOrderTraverse(p->m_pRight, fVisit);
		fVisit(p->m_tData);
	}
}

template<typename T>
inline void CsBTree_Private<T>::GetNodeCount(
	const CsBTreeNode<T> *p,
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

template<typename T>
inline void CsBTree_Private<T>::GetLeafCount(
	const CsBTreeNode<T> *p,
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

template<typename T>
inline cs_size_t CsBTree_Private<T>::GetDepth(const CsBTreeNode<T> *p) const
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