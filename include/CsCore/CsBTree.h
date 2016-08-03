/// binary tree

#ifndef _CSCORE_BINARY_TREE_H_
#define _CSCORE_BINARY_TREE_H_

#include <assert.h>  
#include <crtdbg.h>  

template<typename T>
class CsBTreeNode
{
public:
	T data;
	CsBTreeNode<T> *parent;
	CsBTreeNode<T> *left;
	CsBTreeNode<T> *right;
	CsBTreeNode(
		T data = T(),
		CsBTreeNode<T> *parent = NULL,
		CsBTreeNode<T> *left = NULL,
		CsBTreeNode<T> *right = NULL
		) : data(data), parent(parent), left(left), right(right) {}
};

template<typename T>
class CsBTree
{
	typedef CsBTreeNode<T> Node;

public:
	CsBTree(Node *root = NULL);
	CsBTree(const CsBTree<T> &other);
	virtual ~CsBTree();
	CsBTree<T>& operator=(const CsBTree<T>& other);
	void Clone(const CsBTree<T>& other);
	void Attach(CsBTreeNode<T> *p);
	void Destroy();

public:
	T &GetNodeData(Node *p);
	T GetNodeData(const Node *p) const;
	void SetNodeData(Node *p, const T &data);
	Node *&GetRoot();
	Node *GetRoot() const;
	Node *&GetParent(Node *p);
	Node *GetParent(const Node *p) const;
	Node *&GetLeftChild(Node *p);
	Node *GetLeftChild(const Node *p) const;
	Node *&GetRightChild(Node *p);
	Node *GetRightChild(const Node *p) const;
	Node *&GetLeftSibling(Node *p);
	Node *GetLeftSiblig(const Node *p) const;
	Node *&GetRightSibling(Node *p);
	Node *GetRightSibling(const Node *p) const;
	int IsEmpty() const;

public:
	typedef void(*funtype)(const T&);
	void PreOrderTraverse(funtype Visit) const;
	void InOrderTraverse(funtype Visit) const;
	void PostOrderTraverse(funtype Visit) const;
	unsigned int GetNodesCount() const;
	unsigned int GetLeafCount() const;
	unsigned int GetDepth() const;

private: 
	Node* CloneSubTree(Node *p);
	void DestroySubTree(Node *p);
	void PreOrderTraverse(const Node *p, funtype Visit) const;
	void InOrderTraverse(const Node *p, funtype Visit) const;
	void PostOrderTraverse(const Node *p, funtype Visit) const;
	void GetNodesCount(const Node *p, unsigned int *unCount) const;
	void GetLeafCount(const Node *p, unsigned int *unCount) const;
	unsigned int GetDepth(const Node *p) const;

protected:
	Node *m_pNodeRoot;
};

template<typename T>
inline CsBTree<T>::CsBTree(Node *root) : m_pNodeRoot(root)
{
}

template<typename T>
inline CsBTree<T>::CsBTree(const CsBTree<T>& other) : m_pNodeRoot(NULL)
{
	if (NULL != other.m_pNodeRoot)
		m_pNodeRoot = CloneSubTree(other.m_pNodeRoot);
}

template<typename T>
inline CsBTree<T>::~CsBTree()
{
	Destroy();
}

template<typename T>
inline void CsBTree<T>::Attach(Node *p)
{
	ASSERT(p);
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	m_pNodeRoot = p;
}

template<typename T>
inline CsBTree<T>& CsBTree<T>::operator=(const CsBTree<T> &p)
{
	if (this == &p)
	{
		return *this;
	}
	if (m_pNodeRoot != NULL)
	{
		Destroy();
	}
	if (NULL != p.m_pNodeRoot)
		m_pNodeRoot = CloneSubTree(p.m_pNodeRoot);
	else
		m_pNodeRoot = NULL;
	return *this;
}

template<typename T>
inline void CsBTree<T>::Clone(const CsBTree<T> &p)
{
	/*if(this==&p)
	{
	return;
	}
	if(m_pNodeRoot!=NULL)
	{
	Destroy();
	}
	if (NULL != p.m_pNodeRoot)
	m_pNodeRoot = CloneSubTree(p.m_pNodeRoot);
	else
	m_pNodeRoot = NULL;*/
	operator=(p);
}


template<typename T>
inline void CsBTree<T>::Destroy()
{
	DestroySubTree(m_pNodeRoot);
	m_pNodeRoot = NULL;
}
/*------------------------------------------------------------------
*utilizations,e.g, gets and sets
---------------------------------------------------------------------*/

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetLeftChild(Node *p)
{
	ASSERT(p);
	return *(&(p->left));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetLeftChild(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->left;
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetRightChild(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return *(&(p->right));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetRightChild(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->right;
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetLeftSibling(CsBTreeNode<T> *p)
{
	ASSERT(p);

	if (p->parent)
		return *(&(p->parent->left));
	else
		return *(&(p->parent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetLeftSiblig(const CsBTreeNode<T> *p) const
{
	ASSERT(p);

	if (p->parent)
		return p->parent->left;
	else
		return p->parent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetRightSibling(CsBTreeNode<T> *p)
{
	ASSERT(p);

	if (p->parent)
		return *(&(p->parent->right));
	else
		return *(&(p->parent)); // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetRightSibling(const CsBTreeNode<T> *p) const
{
	ASSERT(p);

	if (p->parent)
		return p->parent->right;
	else
		return p->parent;       // return NULL;  
}

template<typename T>
inline CsBTreeNode<T>*& CsBTree<T>::GetParent(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return *(&(p->parent));
}

template<typename T>
inline CsBTreeNode<T>* CsBTree<T>::GetParent(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->parent;
}

template<typename T>
inline T& CsBTree<T>::GetNodeData(CsBTreeNode<T> *p)
{
	ASSERT(p);
	return p->data;
}

template<typename T>
inline T CsBTree<T>::GetNodeData(const CsBTreeNode<T> *p) const
{
	ASSERT(p);
	return p->data;
}

template<typename T>
inline void CsBTree<T>::SetNodeData(CsBTreeNode<T> *p, const T &data)
{
	ASSERT(p);
	p->data = data;
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
inline void CsBTree<T>::PreOrderTraverse(funtype Visit) const
{
	PreOrderTraverse(m_pNodeRoot, Visit);
}



template<typename T>
inline void CsBTree<T>::InOrderTraverse(funtype Visit) const
{
	InOrderTraverse(m_pNodeRoot, Visit);
}



template<typename T>
inline void CsBTree<T>::PostOrderTraverse(funtype Visit) const
{
	PostOrderTraverse(m_pNodeRoot, Visit);
}



template<typename T>
inline unsigned int CsBTree<T>::GetNodesCount() const
{
	unsigned int unCount;
	GetNodesCount(m_pNodeRoot, &unCount);
	return unCount;
}



template<typename T>
inline unsigned int CsBTree<T>::GetLeafCount() const
{
	unsigned int unCount = 0;
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
		pNewNode->data = p->data;
		pNewNode->parent = p->parent;
		pNewNode->left = CloneSubTree(p->left);
		pNewNode->right = CloneSubTree(p->right);
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
		DestroySubTree(p->left);
		DestroySubTree(p->right);
		delete p;
	}
}

template<typename T>
inline void CsBTree<T>::PreOrderTraverse(const CsBTreeNode<T> *p, funtype Visit) const
{
	if (p)
	{
		Visit(p->data);
		PreOrderTraverse(p->left, Visit);
		PreOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline void CsBTree<T>::InOrderTraverse(const CsBTreeNode<T> *p, funtype Visit) const
{
	if (p)
	{
		InOrderTraverse(p->left, Visit);
		Visit(p->data);
		InOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline void CsBTree<T>::PostOrderTraverse(const CsBTreeNode<T> *p, funtype Visit) const
{
	if (p)
	{
		PostOrderTraverse(p->left, Visit);
		PostOrderTraverse(p->right, Visit);
		Visit(p->data);
	}
}


template<typename T>
inline void CsBTree<T>::GetNodesCount(
	const CsBTreeNode<T> *p,
	unsigned int *unCount
	) const
{
	ASSERT(unCount);

	unsigned int unLeftCount;
	unsigned int unRightCount;

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
	unsigned int *unCount
	) const
{
	ASSERT(unCount);

	if (p)
	{
		// if the node's left & right children are both NULL, it must be a leaf  
		if ((NULL == p->left) && (NULL == p->right))
			++(*unCount);
		GetLeafCount(p->left, unCount);
		GetLeafCount(p->right, unCount);
	}
}


template<typename T>
inline unsigned int CsBTree<T>::GetDepth(const CsBTreeNode<T> *p) const
{
	unsigned int unDepthLeft;
	unsigned int unDepthRight;

	if (p)
	{
		unDepthLeft = GetDepth(p->left);
		unDepthRight = GetDepth(p->right);
		return 1 +  // if don't plus 1 here, the tree's depth will be always 0  
			(unDepthLeft > unDepthRight ? unDepthLeft : unDepthRight);
	}
	else
		return 0;
}

#endif // _CSCORE_BINARY_TREE_H_