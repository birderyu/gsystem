/****************************************************************************
**
** Supernova
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
	typename CompareT = CsCompareF<KeyT >,
	typename NodeT = CsBinarySortTreeNode<KeyT, ValueT>>
class CsBinarySortTree 
	: public CsBinaryTree<NodeT>
{
public:
	virtual ~CsBinarySortTree();
	NodeT *Find(const KeyT &key) const;
	NodeT *FirstNode() const;
	NodeT *LastNode() const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual cs_void Delete(const KeyT &key);

protected:
	// 非递归实现
	NodeT *Find(const KeyT &key, NodeT *node) const;
	cs_void Insert(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins);
	cs_void Delete(const KeyT &key, NodeT *node);

	// 递归实现（不推荐使用）
	// 对于Insert和Delete操作，其返回值只是作为递归传递参数，并非实际需要的返回值
	NodeT *Find_Recursive(const KeyT &key, NodeT *node) const;
	NodeT *Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins);
	NodeT *Delete_Recursive(const KeyT &key, NodeT *node);

	cs_bool SwitchNode(NodeT *node1, NodeT *node2);

protected:
	// 比较函数
	CompareT m_fCompare;
};

#include "CsBinarySortTree.inl"

#endif // _CORE_BINARY_SORT_TREE_H_