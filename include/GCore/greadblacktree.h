/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	greadblacktree.h
** @brief	该文件包含了红黑树的定义及实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-17
** @version	1.0
** @see		GBinaryTreeNode
** @see		GBinaryTree
** @see		GBinarySortTree
** @see		GBinarySortTreeNode
**
****************************************************************************/

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "gbinarysorttree.h"

#define G_RED_BLACK_TREE_NODE_RED		0
#define G_RED_BLACK_TREE_NODE_BLACK		1

template<typename KeyT, typename ValueT>
struct GReadBlackTreeNode 
	: public GBinaryTreeNodeT<GReadBlackTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GReadBlackTreeNode<KeyT, ValueT>>
{
	gsmall m_nColor;

	GReadBlackTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GReadBlackTreeNode<KeyT, ValueT> *parent = GNULL,
		GReadBlackTreeNode<KeyT, ValueT> *left = GNULL,
		GReadBlackTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);

	GReadBlackTreeNode(
		const KeyT &key, ValueT &&value,
		GReadBlackTreeNode<KeyT, ValueT> *parent = GNULL,
		GReadBlackTreeNode<KeyT, ValueT> *left = GNULL,
		GReadBlackTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);
};

/****************************************************************************
**
** greadblacktree.h
**
** @class		GReadBlackTree
** @brief		红黑树
** @module		GCore
**
** 满足以下五个性质的二叉排序树，被称为红黑树：
** 1）每个结点要么是红的，要么是黑的；
** 2）根结点是黑的；
** 3）空结点（NULL）是黑的；
** 4）如果一个结点是红的，那么它的俩个儿子都是黑的；
** 5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
**
** @see GReadBlackTreeNode
** @see GBinaryTreeNodeT<NodeT>
** @see GKeyValueNodeT<KeyT, ValueT>
**
****************************************************************************/
template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT>,
	typename NodeT = GReadBlackTreeNode<KeyT, ValueT> >
class GReadBlackTree 
	: public GBinarySortTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~GReadBlackTree();

	/// 插入一个数据
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, gbool *realInsert = GNULL);
	virtual NodeT *Insert(const KeyT &key, ValueT &&value, gbool *realInsert = GNULL);

	/// 删除一个数据
	virtual gvoid Delete(const KeyT &key, gbool *realDelete = GNULL);
	virtual gvoid Delete(NodeT *node, gbool *realDelete = GNULL);

protected:
	// 插入修复
	gvoid InsertFixUp(NodeT *);
	// 删除修复
	gvoid DeleteFixUp(NodeT *);
	// 左旋
	gvoid RotateLeft(NodeT *);
	// 右旋
	gvoid RotateRight(NodeT *);
};

#include "greadblacktree.inl"

#undef G_RED_BLACK_TREE_NODE_BLACK
#undef G_RED_BLACK_TREE_NODE_RED

#endif // _CORE_RED_BLACK_TREE_H_