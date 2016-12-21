// Adelson-Velskii-Landis Tree

#ifndef _CORE_AVL_TREE_H_
#define _CORE_AVL_TREE_H_

#include "CsBinarySortTree.h"

template<typename KeyT, typename ValueT>
struct CsAvlTreeNode
	: public CsBinaryTreeNodeT<CsAvlTreeNode<KeyT, ValueT>>
	, public CsKeyValueNodeT<KeyT, ValueT>
	, public CsNewT<CsAvlTreeNode<KeyT, ValueT>>
{
	CsAvlTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsAvlTreeNode<KeyT, ValueT> *parent = NULL,
		CsAvlTreeNode<KeyT, ValueT> *left = NULL,
		CsAvlTreeNode<KeyT, ValueT> *right = NULL);
};

template < typename KeyT, typename ValueT,
	typename CompareT = CsCompareToF<KeyT >,
	typename NodeT = CsAvlTreeNode < KeyT, ValueT >>
class CsAvlTree
	: public CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~CsAvlTree();
	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual cs_void Delete(const KeyT &key);

private:
	// µ¥ÓÒÐý
	cs_void SingleRotateRight(NodeT *);
	// µ¥×óÐý
	cs_void SingleRotateLeft(NodeT *);
	// Ë«ÓÒÐý
	cs_void DoubleRotateRight(NodeT *);
	// Ë«×óÐý
	cs_void DoubleRotateLeft(NodeT *);
};

#endif // _CORE_AVL_TREE_H_