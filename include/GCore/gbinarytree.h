/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gbinarytree.h
** @brief	该文件包含了二叉树节点的定义、二叉树的定义及实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	1.0
** @see		GBinaryTreeNode
** @see		GBinaryTree
**
****************************************************************************/

#ifndef _CORE_BINARY_TREE_H_
#define _CORE_BINARY_TREE_H_

#include "gobject.h"
#include "gstructure.h"
#include "glist.h"

/****************************************************************************
**
** gbinarytree.h
**
** @class		GBinaryTreeNode
** @brief		一个默认的二叉树节点
** @module		GCore
**
** 所有的二叉树节点节点都应该直接派生自GBinaryTreeNodeT，这是一个
** 奇异递归模板（CRTP）。
**
** @see GBinaryTreeNodeT<NodeT>
**
****************************************************************************/
struct GBinaryTreeNode 
	: public GBinaryTreeNodeT<GBinaryTreeNode>
	, public GNewT<GBinaryTreeNode>
{
	/****************************************************************************
	**
	** GBinaryTreeNode
	**
	** @name		GBinaryTreeNode
	** @brief		构造函数（constructor）
	** @param[in]	parent:	双亲节点，默认为NULL
	** @param[in]	left:	左孩子节点，默认为NULL
	** @param[in]	right:	右孩子节点，默认为NULL
	**
	****************************************************************************/
	GBinaryTreeNode(GBinaryTreeNode *parent = GNULL, 
		GBinaryTreeNode *left = GNULL, 
		GBinaryTreeNode *right = GNULL);
};

/****************************************************************************
**
** gbinarytree.h
**
** @class		GBinaryTree
** @brief		二叉树
** @module		GCore
**
** 为了增加二叉树的可扩展性，可以由外部指定其节点对象NodeT，但该
** NodeT必须派生自GBinaryTreeNodeT，这是一个奇异递归模板（CRTP）。
** 默认情况下，使用GBinaryTreeNode作为节点即可。
**
** @see GBinaryTreeNode
** @see GBinaryTreeNodeT<NodeT>
**
****************************************************************************/
template<typename NodeT = GBinaryTreeNode>
class GBinaryTree 
	: public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_BINARY_TREE, };

public:
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	funtype
	** @brief	访问节点的函数指针的定义
	**
	****************************************************************************/
	typedef gvoid(*funtype)(const NodeT &node);

public:
	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		GBinaryTree
	** @brief		构造函数（constructor）
	** @param[in]	root: 根节点，默认为NULL
	**
	** 默认情况下构造一棵空树
	**
	****************************************************************************/
	GBinaryTree(NodeT *root = GNULL);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		GBinaryTree
	** @brief		拷贝构造函数（copy constructor）
	** @param[in]	tree {const GBinaryTree<NodeT> &tree} 另一棵二叉树的引用
	**
	****************************************************************************/
	GBinaryTree(const GBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		GBinaryTree
	** @brief		移动构造函数（move constructor）
	** @param[in]	tree {GBinaryTree<NodeT> &&} 另一棵二叉树的引用（右值引用）
	**
	****************************************************************************/
	GBinaryTree(GBinaryTree<NodeT> &&tree);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	~GBinaryTree
	** @brief	析构函数（destructor）
	**
	** 析构函数被调用时，会释放所有节点的内存，若一个节点同时被两棵树共享，则会造成异常。
	** 由于GBinaryTree需要作为所有二叉树的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~GBinaryTree();

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		CopyFrom
	** @brief		从另一棵树拷贝数据
	** @param[in]	tree: 另一棵二叉树的引用
	**
	** 若自己已经包含了数据，则会先释放自己的资源，再做拷贝操作。
	** 深拷贝（deep copy）。
	**
	****************************************************************************/
	gvoid CopyFrom(const GBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		SetRoot
	** @brief		设置根节点
	** @param[in]	将作为根节点的节点指针
	**
	** 若自己已经有了根节点，则会先释放自己的资源，再设置根节点。
	**
	****************************************************************************/
	gvoid SetRoot(NodeT *);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		Dispose
	** @brief		销毁树
	**
	** 释放所有资源。
	**
	****************************************************************************/
	gvoid Dispose();

public:
	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	Root
	** @brief	获取根节点
	** @return	根节点指针的引用
	**
	****************************************************************************/
	NodeT *&Root();

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	Root
	** @brief	获取根节点
	** @return	根节点的指针
	**
	****************************************************************************/
	NodeT *Root() const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	IsEmpty
	** @brief	判断二叉树是否为空
	** @return	若为空则返回true，否则返回false
	**
	****************************************************************************/
	gbool IsEmpty() const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	NodeCount
	** @brief	返回节点的个数
	** @return	节点的个数
	**
	****************************************************************************/
	gsize NodeCount() const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	LeafCount
	** @brief	返回叶子节点的个数
	** @return	叶子节点的个数
	**
	****************************************************************************/
	gsize LeafCount() const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name	Depth
	** @brief	返回树的深度
	** @return	树的深度
	**
	** 认为根节点的深度为1，其余依次累加
	**
	****************************************************************************/
	gsize Depth() const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		PreOrderTraverse
	** @brief		先（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PreOrderTraverse(VisitorT &visitor) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		InOrderTraverse
	** @brief		中（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid InOrderTraverse(VisitorT &visitor) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		PostOrderTraverse
	** @brief		后（根）序遍历
	** @param[in]	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PostOrderTraverse(VisitorT &visitor) const;

public:
	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		operator=
	** @brief		拷贝操作符
	** @param[in]	tree: 另一棵二叉树的引用
	** @return		自己的引用
	**
	****************************************************************************/
	GBinaryTree<NodeT> &operator=(const GBinaryTree<NodeT> &tree);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		operator=
	** @brief		移动操作符
	** @param[in]	tree: 另一棵二叉树的引用
	** @return		自己的引用
	**
	****************************************************************************/
	GBinaryTree<NodeT> &operator=(GBinaryTree<NodeT> &&tree);

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		operator==
	** @brief		等号运算符
	** @param[in]	tree: 另一棵二叉树的引用
	** @return		若两个树相等，则返回true，否则返回false
	**
	** 满足以下条件的两棵树完全相等：
	** 1）两棵树的分布完全一致，且相同位置上的节点都相等（Equals）；
	** 2）空树与空树相等。
	**
	****************************************************************************/
	gbool operator==(const GBinaryTree<NodeT> &tree) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		operator!=
	** @brief		不等号运算符
	** @param[in]	tree: 另一棵二叉树的引用
	** @return		若两个树不相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator!=(const GBinaryTree<NodeT> &tree) const;

protected:
	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		DestroySubTree
	** @brief		销毁一棵子树
	** @param[in]	子树的根节点
	**
	****************************************************************************/
	gvoid DestroySubTree(NodeT *);

	/****************************************************************************
	**
	** GBinaryTree
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
	** GBinaryTree
	**
	** @name		PreOrderTraverse
	** @brief		先（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PreOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		InOrderTraverse
	** @brief		中（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid InOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		PostOrderTraverse
	** @brief		后（根）序遍历一棵子树
	** @param[in]	node:	子树的根节点
	** @param[in]	fVisit:	访问节点的函数指针
	**
	****************************************************************************/
	template<typename VisitorT> gvoid PostOrderTraverse(const NodeT *node, VisitorT &visitor) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		NodeCount
	** @brief		返回一棵子树中节点的个数
	** @param[in]	node:		子树的根节点
	** @param[out]	unCount:	子树中节点的个数
	**
	****************************************************************************/
	gvoid NodeCount(const NodeT *node, gsize &unCount) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		LeafCount
	** @brief		返回一棵子树中叶子节点的个数
	** @param[in]	node:		子树的根节点
	** @param[out]	unCount:	子树中叶子节点的个数
	**
	****************************************************************************/
	gvoid LeafCount(const NodeT *node, gsize &unCount) const;

	/****************************************************************************
	**
	** GBinaryTree
	**
	** @name		Depth
	** @brief		返回一棵子树的深度
	** @param[in]	子树的根节点
	** @return		子树的深度
	**
	****************************************************************************/
	gsize Depth(const NodeT *) const;

	gbool TreeEquals(const NodeT *node1, const NodeT *node2) const;
	virtual gbool NodeEquals(const NodeT *node1, const NodeT *node2) const;

protected:
	NodeT *m_pRoot;
};

#include "gbinarytree.inl"

#endif // _CORE_BINARY_TREE_H_