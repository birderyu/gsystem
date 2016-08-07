/////////////////////////////////////////////////////////////////////////////////
/// @brief 二叉树（binary tree）
/// 
///  二叉树的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CSCORE_BINARY_TREE_H_
#define _CSCORE_BINARY_TREE_H_

#include "CsObject.h"

template<typename T>
class CsBTree;

template<typename T>
class CsBTreeNode :public CsObject
{
	friend class CsBTree<T>;

public:
	CsBTreeNode(
		T &data = T(),
		CsBTreeNode<T> *parent = NULL,
		CsBTreeNode<T> *left = NULL,
		CsBTreeNode<T> *right = NULL);
	T &GetData();
	T GetData() const;
	CsBTreeNode<T> *GetParent();
	CsBTreeNode<T> *GetParent() const;
	CsBTreeNode<T> *GetLeft();
	CsBTreeNode<T> *GetLeft() const;
	CsBTreeNode<T> *GetRight();
	CsBTreeNode<T> *GetRight() const;

private:
	T m_tData;
	CsBTreeNode<T> *m_pParent;
	CsBTreeNode<T> *m_pLeft;
	CsBTreeNode<T> *m_pRight;
};

template<typename T>
class CsBTree :public CsObject
{
	typedef CsBTreeNode<T> Node;

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
	int IsEmpty() const;

public:
	typedef void(*funtype)(const T&);
	void PreOrderTraverse(funtype fVisit) const;
	void InOrderTraverse(funtype fVisit) const;
	void PostOrderTraverse(funtype fVisit) const;
	cs_size_t GetNodesCount() const;
	cs_size_t GetLeafCount() const;
	cs_size_t GetDepth() const;

private: 
	Node* CloneSubTree(Node *pNode);
	void DestroySubTree(Node *pNode);
	void PreOrderTraverse(const Node *pNode, funtype fVisit) const;
	void InOrderTraverse(const Node *pNode, funtype fVisit) const;
	void PostOrderTraverse(const Node *pNode, funtype fVisit) const;
	void GetNodesCount(const Node *pNode, cs_size_t *nCount) const;
	void GetLeafCount(const Node *pNode, cs_size_t *nCount) const;
	unsigned int GetDepth(const Node *pNode) const;

protected:
	Node *m_pNodeRoot;
};

template<typename T>
inline CsBTreeNode<T>::CsBTreeNode(T &tData, CsBTreeNode<T> *pParent, CsBTreeNode<T> *pLeft, CsBTreeNode<T> *pRight) 
: tData(tData), pParent(pParent), pLeft(pLeft), pRight(pRight) 
{

}

template<typename T>
inline T &CsBTreeNode<T>::GetData()
{
	return m_tData;
}

template<typename T>
inline T CsBTreeNode<T>::GetData() const
{
	return m_tData;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetParent()
{
	return m_pParent;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetParent() const
{
	return m_pParent;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetLeft()
{
	return m_pLeft;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetLeft() const
{
	return m_pLeft;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetRight()
{
	return m_pRight;
}

template<typename T>
inline CsBTreeNode<T> *CsBTreeNode<T>::GetRight() const
{
	return m_pRight;
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
	if (NULL != tTree.m_pNodeRoot)
	{
		m_pNodeRoot = CloneSubTree(tTree.m_pNodeRoot);
	}
}

template<typename T>
inline CsBTree<T>::~CsBTree()
{
	Destroy();
}

template<typename T>
inline void CsBTree<T>::Attach(CsBTreeNode<T> *pNode)
{
	ASSERT(pNode);
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	m_pNodeRoot = pNode;
}

template<typename T>
inline CsBTree<T>& CsBTree<T>::operator=(const CsBTree<T> &tTree)
{
	if (this == &tTree)
	{
		return *this;
	}
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	if (NULL != tTree.m_pNodeRoot)
	{
		m_pNodeRoot = CloneSubTree(tTree.m_pNodeRoot);
	}
	else
	{
		m_pNodeRoot = NULL;
	}
	return *this;
}

template<typename T>
inline void CsBTree<T>::Clone(const CsBTree<T> &tTree)
{
	operator=(tTree);
}

template<typename T>
inline void CsBTree<T>::Destroy()
{
	DestroySubTree(m_pNodeRoot);
	m_pNodeRoot = NULL;
}

template<typename T>
inline CsBTreeNode<T> *&CsBTree<T>::GetLeftChild(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return *(&(p->left));
}

template<typename T>
inline CsBTreeNode<T> *CsBTree<T>::GetLeftChild(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->m_pLeft;
}

template<typename T>
inline CsBTreeNode<T> *&CsBTree<T>::GetRightChild(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return *(&(p->m_pRight));
}

template<typename T>
inline CsBTreeNode<T> *CsBTree<T>::GetRightChild(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->m_pRight;
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetLeftSibling(CsBTreeNode<T> *p)
{
	ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->left));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetLeftSiblig(const CsBTreeNode<T> *p) const
{
	ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->left;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetRightSibling(CsBTreeNode<T> *p)
{
	ASSERT(p);

	if (p->m_pParent)
		return *(&(p->m_pParent->right));
	else
		return *(&(p->m_pParent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetRightSibling(const CsBTreeNode<T> *p) const
{
	ASSERT(p);

	if (p->m_pParent)
		return p->m_pParent->right;
	else
		return p->m_pParent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetParent(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return *(&(p->m_pParent));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetParent(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->m_pParent;
}

template<typename T>
inline T& CsBTree<T>::GetNodeData(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return p->m_tData;
}

template<typename T>
inline T CsBTree<T>::GetNodeData(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->m_tData;
}

template<typename T>
inline void CsBTree<T>::SetNodeData(CsBTreeNode<T> *p, const T &data)
{
	ASSERT(p);
	p->m_tData = data;
}

template<typename T>
inline int CsBTree<T>::IsEmpty() const
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


/*---------------------------------------------------------------------
*public interfaces for core operations
------------------------------------------------------------------------*/

template<typename T>
inline void CsBTree<T>::PreOrderTraverse(funtype fVisit) const
{
	PreOrderTraverse(m_pNodeRoot, fVisit);
}



template<typename T>
inline void CsBTree<T>::InOrderTraverse(funtype fVisit) const
{
	InOrderTraverse(m_pNodeRoot, fVisit);
}



template<typename T>
inline void CsBTree<T>::PostOrderTraverse(funtype fVisit) const
{
	PostOrderTraverse(m_pNodeRoot, fVisit);
}



template<typename T>
inline cs_size_t CsBTree<T>::GetNodesCount() const
{
	cs_size_t unCount = 0;
	GetNodesCount(m_pNodeRoot, &unCount);
	return unCount;
}



template<typename T>
inline cs_size_t CsBTree<T>::GetLeafCount() const
{
	cs_size_t unCount = 0;
	GetLeafCount(m_pNodeRoot, &unCount);
	return unCount;
}



template<typename T>
inline unsigned int CsBTree<T>::GetDepth() const
{
	// Minus 1 here because I think the root node's depth should be 0.  
	// So, don't do it if u think the root node's depth should be 1.  
	return GetDepth(m_pNodeRoot) - 1;
}



/*------------------------------------------------------------------------------
*private functions: implementing recursion operations, tranversion operations and others.
---------------------------------------------------------------------------------*/

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::CloneSubTree(CsBTreeNode<T> *p)
{
	if (p)
	{
		CsBTreeNode<T> *pNewNode;
		try
		{
			pNewNode = new CsBTreeNode<T>;
		}
		catch (std::bad_alloc&)
		{
			return NULL;
		}
		pNewNode->m_tData = p->m_tData;
		pNewNode->m_pParent = p->m_pParent;
		pNewNode->m_pLeft = CloneSubTree(p->m_pLeft);
		pNewNode->m_pRight = CloneSubTree(p->m_pRight);
		return pNewNode;
	}
	else
		return NULL;
}

template<typename T>
inline void CsBTree<T>::DestroySubTree(CsBTreeNode<T> *p)
{
	if (p)
	{
		DestroySubTree(p->m_pLeft);
		DestroySubTree(p->m_pRight);
		delete p;
	}
}

template<typename T>
inline void CsBTree<T>::PreOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		fVisit(p->m_tData);
		PreOrderTraverse(p->m_pLeft, fVisit);
		PreOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename T>
inline void CsBTree<T>::InOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		InOrderTraverse(p->m_pLeft, fVisit);
		fVisit(p->m_tData);
		InOrderTraverse(p->m_pRight, fVisit);
	}
}

template<typename T>
inline void CsBTree<T>::PostOrderTraverse(const CsBTreeNode<T> *p, funtype fVisit) const
{
	if (p)
	{
		PostOrderTraverse(p->m_pLeft, fVisit);
		PostOrderTraverse(p->m_pRight, fVisit);
		fVisit(p->m_tData);
	}
}


template<typename T>
inline void CsBTree<T>::GetNodesCount(
	const CsBTreeNode<T> *p,
	cs_size_t *unCount
	) const
{
	ASSERT(unCount);

	cs_size_t unLeftCount;
	cs_size_t unRightCount;

	if (NULL == p)
		*unCount = 0;
	else if ((NULL == p->left) && (NULL == p->right))
		*unCount = 1;
	else
	{
		GetNodesCount(p->left, &unLeftCount);
		GetNodesCount(p->right, &unRightCount);
		*unCount = 1 + unLeftCount + unRightCount;
	}
}

template<typename T>
inline void CsBTree<T>::GetLeafCount(
	const CsBTreeNode<T> *p,
	cs_size_t *unCount
	) const
{
	ASSERT(unCount);

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
inline cs_size_t CsBTree<T>::GetDepth(const CsBTreeNode<T> *p) const
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

#endif // _CSCORE_BINARY_TREE_H_