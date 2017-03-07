// Adelson-Velskii-Landis Tree

#ifndef _CORE_AVL_TREE_H_
#define _CORE_AVL_TREE_H_

#include "gbinarysorttree.h"

template<typename KeyT, typename ValueT>
struct GAvlTreeNode
	: public GBinaryTreeNodeT<GAvlTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GAvlTreeNode<KeyT, ValueT>>
{
	GAvlTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GAvlTreeNode<KeyT, ValueT> *parent = GNULL,
		GAvlTreeNode<KeyT, ValueT> *left = GNULL,
		GAvlTreeNode<KeyT, ValueT> *right = GNULL);
};

template < typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT >,
	typename NodeT = GAvlTreeNode < KeyT, ValueT >>
class GAvlTree
	: public GBinarySortTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~GAvlTree();
	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual gvoid Delete(const KeyT &key);

private:
	// µ¥ÓÒÐý
	gvoid SingleRotateRight(NodeT *);
	// µ¥×óÐý
	gvoid SingleRotateLeft(NodeT *);
	// Ë«ÓÒÐý
	gvoid DoubleRotateRight(NodeT *);
	// Ë«×óÐý
	gvoid DoubleRotateLeft(NodeT *);
};

#endif // _CORE_AVL_TREE_H_