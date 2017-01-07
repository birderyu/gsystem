/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gbinarysorttree.h
** @brief	该文件包含了二叉排序树的定义及实现
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	1.0
** @see		GBinaryTreeNode
** @see		GBinaryTree
** @see		GBinarySortTree
**
****************************************************************************/

#ifndef _CORE_BINARY_SORT_TREE_H_
#define _CORE_BINARY_SORT_TREE_H_

#include "gbinarytree.h"

template<typename KeyT, typename ValueT>
struct GBinarySortTreeNode 
	: public GBinaryTreeNodeT<GBinarySortTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GBinarySortTreeNode<KeyT, ValueT>>
{
	GBinarySortTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GBinarySortTreeNode<KeyT, ValueT> *parent = NULL,
		GBinarySortTreeNode<KeyT, ValueT> *left = NULL,
		GBinarySortTreeNode<KeyT, ValueT> *right = NULL);
};

template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT >,
	typename NodeT = GBinarySortTreeNode<KeyT, ValueT>>
class GBinarySortTree 
	: public GBinaryTree<NodeT>
{
public:
	virtual ~GBinarySortTree();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *LastNode();
	const NodeT *LastNode() const;

	gbool Contains(const KeyT &key) const;
	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, gbool *realInsert = NULL);
	virtual gvoid Delete(const KeyT &key, gbool *realDelete = NULL);

protected:
	// 非递归实现
	gbool Contains_Unrecursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Unrecursive(const KeyT &key, NodeT *node);
	const NodeT *Find_Unrecursive(const KeyT &key, const NodeT *node) const;
	gvoid Insert_Unrecursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	gvoid Delete_Unrecursive(const KeyT &key, NodeT *node, gbool &realDelete);

	// 递归实现（不推荐使用）
	// 对于Insert和Delete操作，其返回值只是作为递归传递参数，并非实际需要的返回值
	gbool Contains_Recursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Recursive(const KeyT &key, NodeT *node);
	const NodeT *Find_Recursive(const KeyT &key, const NodeT *node) const;
	NodeT *Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	NodeT *Delete_Recursive(const KeyT &key, NodeT *node, gbool &realDelete);

	// 交换两个节点
	gbool SwitchNode(NodeT *node1, NodeT *node2);

protected:
	// 比较函数
	CompareT m_fCompare;
};

#include "gbinarysorttree.inl"

#endif // _CORE_BINARY_SORT_TREE_H_