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

template<typename T> class CsRBTree;
template<typename T> class CsRBTree_Private;

/// 红黑树节点
template<typename T>
struct CsRBTreeNode :public CsBTreeNode<T>
{
	enum COLOR 
	{ 
		COLOR_RED = 0,
		COLOR_BLACK = 1
	};
	COLOR m_emColor; // 颜色

	CsRBTreeNode(
		const T &data = T(),
		CsBTreeNode<T> *parent = NULL,
		CsBTreeNode<T> *left = NULL,
		CsBTreeNode<T> *right = NULL,
		COLOR color = COLOR_BLACK);
	virtual ~CsRBTreeNode();
	virtual CsBTreeNode<T> *Copy() const;
};

/// 红黑树
template<typename T>
class CsRBTree : public CsBSTree<T>
{
public:
	virtual ~CsRBTree();

	/// 插入一个数据
	/// 如果改变了Node的结构，Insert方法需要重新实现
	virtual Node *Insert(const T &data);

	/// 删除一个数据
	virtual Node *Delete(const T &data);

private:
	CsRBTree_Private<T> m_tRBTree_Private;
};

/// 红黑树功能实现类
template<typename T> 
class CsRBTree_Private
{
	friend class CsRBTree<T>;
private:
	typedef CsBTreeNode<T> Node;
	Node *Insert(const T &data, Node *&p, Node *&root);
	Node *Delete(const T &data, Node *&p, Node *&root);
};

template<typename T>
inline CsRBTreeNode<T>::CsRBTreeNode(
	const T &data,
	CsBTreeNode<T> *parent,
	CsBTreeNode<T> *left,
	CsBTreeNode<T> *right,
	COLOR color)
	: CsBTreeNode(data, parent, left, right)
	, m_emColor(color)
{

}

template<typename T>
inline CsRBTreeNode<T>::~CsRBTreeNode()
{

}

template<typename T>
CsBTreeNode<T> *CsRBTreeNode<T>::Copy() const
{
	CsRBTreeNode<T> *pNode = NULL;
	try
	{
		// 创建一个RBTree的节点
		pNode = new CsRBTreeNode<T>(m_tData, m_pParent, NULL, NULL, m_emColor);
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
inline CsRBTree<T>::~CsRBTree()
{

}

template<typename T>
inline CsBTreeNode<T>* CsRBTree<T>::Insert(const T &data)
{
	return m_tRBTree_Private.Insert(data, GetRoot(), GetRoot());
}

template<typename T>
inline CsBTreeNode<T>* CsRBTree<T>::Delete(const T &data)
{
	return m_tRBTree_Private.Delete(data, GetRoot(), GetRoot());
}

template<typename T>
inline CsBTreeNode<T>* CsRBTree_Private<T>::Insert(const T &data, CsBTreeNode<T> *&p, CsBTreeNode<T> *&root)
{
	if (NULL == p)
	{
		try
		{
			// 新插入的节点为红色
			p = new CsRBTreeNode<T>(data, NULL, NULL, NULL, COLOR_RED);
		}
		catch (std::bad_alloc&)
		{
			return NULL;
		}
		if (NULL == root)
		{
			root = p;
		}
	}
	return p;
}

template<typename T>
inline CsBTreeNode<T>* CsRBTree_Private<T>::Delete(const T &data, CsBTreeNode<T> *&p, CsBTreeNode<T> *&root)
{
	return NULL;
}

#endif // _CORE_RED_BLACK_TREE_H_