/****************************************************************************
**
** Supernova
**
** @file	CsBinaryTree.h
** @brief	该文件包含了二叉树节点的定义、二叉树的定义及实现
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	1.0
** @see		CsBinaryTreeNode
** @see		CsBinaryTree
**
****************************************************************************/
#ifndef _CORE_BINARY_TREE_H_
#define _CORE_BINARY_TREE_H_

#include "CsObject.h"
#include "CsNode.h"

/****************************************************************************
**
** CsBinaryTree.h
**
** @class		CsBinaryTreeNode
** @brief		一个默认的二叉树节点
** @module		CsCore
**
** 所有的二叉树节点节点都应该直接派生自CsBinaryTreeNodeT，这是一个
** 奇异递归模板（CRTP）。
**
** @see CsNode.h
** @see CsBinaryTreeNodeT<NodeT>
**
****************************************************************************/
struct CsBinaryTreeNode 
	: public CsBinaryTreeNodeT<CsBinaryTreeNode>
	, public CsNewT<CsBinaryTreeNode>
{
	/****************************************************************************
	**
	** CsBinaryTreeNode
	**
	** @name		CsBinaryTreeNode
	** @brief		构造函数（constructor）
	** @param[in]	parent:	双亲节点，默认为NULL
	** @param[in]	left:	左孩子节点，默认为NULL
	** @param[in]	right:	右孩子节点，默认为NULL
	**
	****************************************************************************/
	CsBinaryTreeNode(CsBinaryTreeNode *parent = NULL, 
		CsBinaryTreeNode *left = NULL, 
		CsBinaryTreeNode *right = NULL);
};

/****************************************************************************
**
** CsBinaryTree.h
**
** @class		CsBinaryTree
** @brief		二叉树
** @module		CsCore
**
** 为了增加二叉树的可扩展性，可以由外部指定其节点对象NodeT，但该
** NodeT必须派生自CsBinaryTreeNodeT，这是一个奇异递归模板（CRTP）。
** 默认情况下，使用CsBinaryTreeNode作为节点即可。
**
** @see CsBinaryTreeNode
** @see CsBinaryTreeNodeT<NodeT>
**
****************************************************************************/
template<typename NodeT = CsBinaryTreeNode>
class CsBinaryTree 
	: public CsObject
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_BINARY_TREE, };

public:
	typedef NodeT Node;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	funtype
	** @brief	访问节点的函数指针的定义
	**
	****************************************************************************/
	typedef cs_void(*funtype)(const Node&);

public:
	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		CsBinaryTree
	** @brief		构造函数（constructor）
	** @param[in]	root: 根节点，默认为NULL
	**
	** 默认情况下构造一棵空树
	**
	****************************************************************************/
	CsBinaryTree(NodeT *root = NULL);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		CsBinaryTree
	** @brief		拷贝构造函数（copy constructor）
	** @param[in]	tree: 另一棵二叉树的引用
	**
	** 深拷贝（deep copy）。
	**
	****************************************************************************/
	CsBinaryTree(const CsBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	~CsBinaryTree
	** @brief	析构函数（destructor）
	**
	** 析构函数被调用时，会释放所有节点的内存，若一个节点同时被两棵树共享，则会造成异常。
	** 由于CsBinaryTree需要作为所有二叉树的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~CsBinaryTree();

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		operator=
	** @brief		重载等号操作
	** @param[in]	tree: 另一棵二叉树的引用
	** @return		自己的引用
	**
	** 若自己已经包含了数据，则会先释放自己的资源，再做拷贝操作。
	** 深拷贝（deep copy）。
	**
	****************************************************************************/
	CsBinaryTree<NodeT>& operator=(const CsBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		CopyFrom
	** @brief		从另一棵树拷贝数据
	** @param[in]	tree: 另一棵二叉树的引用
	**
	** 若自己已经包含了数据，则会先释放自己的资源，再做拷贝操作。
	** 深拷贝（deep copy）。
	**
	****************************************************************************/
	cs_void CopyFrom(const CsBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		SetRoot
	** @brief		设置根节点
	** @param[in]	将作为根节点的节点指针
	**
	** 若自己已经有了根节点，则会先释放自己的资源，再设置根节点。
	**
	****************************************************************************/
	cs_void SetRoot(NodeT *);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		Destroy
	** @brief		销毁树
	**
	** 释放所有资源。
	**
	****************************************************************************/
	cs_void Destroy();

public:
	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	Root
	** @brief	获取根节点
	** @return	根节点指针的引用
	**
	****************************************************************************/
	NodeT *&Root();

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	Root
	** @brief	获取根节点
	** @return	根节点的指针
	**
	****************************************************************************/
	NodeT * Root() const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	IsEmpty
	** @brief	判断二叉树是否为空
	** @return	若为空则返回true，否则返回false
	**
	****************************************************************************/
	cs_bool IsEmpty() const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	NodeCount
	** @brief	返回节点的个数
	** @return	节点的个数
	**
	****************************************************************************/
	cs_size_t NodeCount() const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	LeafCount
	** @brief	返回叶子节点的个数
	** @return	叶子节点的个数
	**
	****************************************************************************/
	cs_size_t LeafCount() const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name	Depth
	** @brief	返回树的深度
	** @return	树的深度
	**
	** 认为根节点的深度为1，其余依次累加
	**
	****************************************************************************/
	cs_size_t Depth() const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		PreOrderTraverse
	** @brief		先（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	cs_void PreOrderTraverse(funtype) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		InOrderTraverse
	** @brief		中（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	cs_void InOrderTraverse(funtype) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		PostOrderTraverse
	** @brief		后（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	cs_void PostOrderTraverse(funtype) const;

public:
	//virtual CsObjectP Clone() const;
	//virtual const CsObject *Boxing() const;
	//virtual cs_bool Unboxing(const CsObject *);
	//virtual CsString ToString() const;
	//virtual cs_uint ClassCode() const;
	//virtual cs_uint HashCode() const;
	//virtual cs_bool Equals(const CsObject *) const;
	//virtual cs_bool Serialize(CsBytes &) const;
	//virtual cs_bool Deserialize(const CsBytes &);

protected:
	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		DestroySubTree
	** @brief		销毁一棵子树
	** @param[in]	子树的根节点
	**
	****************************************************************************/
	cs_void DestroySubTree(NodeT *);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		CopySubTree
	** @brief		拷贝一棵子树
	** @param[in]	子树的根节点
	** @return		拷贝生成的新树的根节点
	**
	****************************************************************************/
	NodeT *CopySubTree(NodeT *);

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		PreOrderTraverse
	** @brief		先（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	cs_void PreOrderTraverse(const NodeT *node, funtype fVisit) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		InOrderTraverse
	** @brief		中（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	cs_void InOrderTraverse(const NodeT *node, funtype fVisit) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		PostOrderTraverse
	** @brief		后（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	cs_void PostOrderTraverse(const NodeT *node, funtype fVisit) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		NodeCount
	** @brief		返回一棵子树中节点的个数
	** @param[in]	node:		子树的根节点
	** @param[out]	unCount:	子树中节点的个数
	**
	****************************************************************************/
	cs_void NodeCount(const NodeT *node, cs_size_t &unCount) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		LeafCount
	** @brief		返回一棵子树中叶子节点的个数
	** @param[in]	node:		子树的根节点
	** @param[out]	unCount:	子树中叶子节点的个数
	**
	****************************************************************************/
	cs_void LeafCount(const NodeT *node, cs_size_t &unCount) const;

	/****************************************************************************
	**
	** CsBinaryTree
	**
	** @name		Depth
	** @brief		返回一棵子树的深度
	** @param[in]	子树的根节点
	** @return		子树的深度
	**
	****************************************************************************/
	cs_size_t Depth(const NodeT *) const;

protected:
	NodeT *m_pRoot;
};

#include "CsBinaryTree.inl"

#endif // _CORE_BINARY_TREE_H_