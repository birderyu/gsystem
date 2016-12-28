/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsReadBlackTree.h
** @brief	该文件包含了红黑树的定义及实现
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-17
** @version	1.0
** @see		CsBinaryTreeNode
** @see		CsBinaryTree
** @see		CsBinarySortTree
** @see		CsBinarySortTreeNode
**
****************************************************************************/

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "CsBinarySortTree.h"

#define CS_RED_BLACK_TREE_NODE_RED		0
#define CS_RED_BLACK_TREE_NODE_BLACK	1

template<typename KeyT, typename ValueT>
struct CsReadBlackTreeNode 
	: public CsBinaryTreeNodeT<CsReadBlackTreeNode<KeyT, ValueT>>
	, public CsKeyValueNodeT<KeyT, ValueT>
	, public CsNewT<CsReadBlackTreeNode<KeyT, ValueT>>
{
	cs_small m_nColor;

	CsReadBlackTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsReadBlackTreeNode<KeyT, ValueT> *parent = NULL,
		CsReadBlackTreeNode<KeyT, ValueT> *left = NULL,
		CsReadBlackTreeNode<KeyT, ValueT> *right = NULL,
		cs_small color = CS_RED_BLACK_TREE_NODE_RED);
};

/****************************************************************************
**
** CsReadBlackTree.h
**
** @class		CsReadBlackTree
** @brief		红黑树
** @module		CsCore
**
** 满足以下五个性质的二叉排序树，被称为红黑树：
** 1）每个结点要么是红的，要么是黑的；
** 2）根结点是黑的；
** 3）空结点（NULL）是黑的；
** 4）如果一个结点是红的，那么它的俩个儿子都是黑的；
** 5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
**
** @see CsReadBlackTreeNode
** @see CsBinaryTreeNodeT<NodeT>
** @see CsKeyValueNodeT<KeyT, ValueT>
**
****************************************************************************/
template<typename KeyT, typename ValueT,
	typename CompareT = CsCompareToF<KeyT>,
	typename NodeT = CsReadBlackTreeNode<KeyT, ValueT> >
class CsReadBlackTree 
	: public CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~CsReadBlackTree();

	/// 插入一个数据
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, cs_bool *realInsert = NULL);

	/// 删除一个数据
	virtual cs_void Delete(const KeyT &key, cs_bool *realDelete = NULL);

protected:
	// 插入修复
	cs_void InsertFixUp(NodeT *);
	// 删除修复
	cs_void DeleteFixUp(NodeT *);
	// 左旋
	cs_void RotateLeft(NodeT *);
	// 右旋
	cs_void RotateRight(NodeT *);
};

#include "CsReadBlackTree.inl"

#undef CS_RED_BLACK_TREE_NODE_BLACK
#undef CS_RED_BLACK_TREE_NODE_RED

#endif // _CORE_RED_BLACK_TREE_H_