/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsBinarySortTree.h
** @brief	该文件包含了二叉排序树的定义及实现
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	1.0
** @see		CsBinaryTreeNode
** @see		CsBinaryTree
** @see		CsBinarySortTree
**
****************************************************************************/

#ifndef _CORE_BINARY_SORT_TREE_H_
#define _CORE_BINARY_SORT_TREE_H_

#include "CsBinaryTree.h"

template<typename KeyT, typename ValueT>
struct CsBinarySortTreeNode 
	: public CsBinaryTreeNodeT<CsBinarySortTreeNode<KeyT, ValueT>>
	, public CsKeyValueNodeT<KeyT, ValueT>
	, public CsNewT<CsBinarySortTreeNode<KeyT, ValueT>>
{
	CsBinarySortTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsBinarySortTreeNode<KeyT, ValueT> *parent = NULL,
		CsBinarySortTreeNode<KeyT, ValueT> *left = NULL,
		CsBinarySortTreeNode<KeyT, ValueT> *right = NULL);
};

template<typename KeyT, typename ValueT,
	typename CompareT = CsCompareToF<KeyT >,
	typename NodeT = CsBinarySortTreeNode<KeyT, ValueT>>
class CsBinarySortTree 
	: public CsBinaryTree<NodeT>
{
public:
	virtual ~CsBinarySortTree();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *LastNode();
	const NodeT *LastNode() const;

	cs_bool Contains(const KeyT &key) const;
	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, cs_bool *realInsert = NULL);
	virtual cs_void Delete(const KeyT &key, cs_bool *realDelete = NULL);

protected:
	// 非递归实现
	cs_bool Contains_Unrecursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Unrecursive(const KeyT &key, NodeT *node);
	const NodeT *Find_Unrecursive(const KeyT &key, const NodeT *node) const;
	cs_void Insert_Unrecursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, cs_bool &realInsert);
	cs_void Delete_Unrecursive(const KeyT &key, NodeT *node, cs_bool &realDelete);

	// 递归实现（不推荐使用）
	// 对于Insert和Delete操作，其返回值只是作为递归传递参数，并非实际需要的返回值
	cs_bool Contains_Recursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Recursive(const KeyT &key, NodeT *node) const;
	NodeT *Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, cs_bool &realInsert);
	NodeT *Delete_Recursive(const KeyT &key, NodeT *node, cs_bool &realDelete);

	// 交换两个节点
	cs_bool SwitchNode(NodeT *node1, NodeT *node2);

protected:
	// 比较函数
	CompareT m_fCompare;
};

#include "CsBinarySortTree.inl"

#endif // _CORE_BINARY_SORT_TREE_H_