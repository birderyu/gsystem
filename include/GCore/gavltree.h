// Adelson-Velskii-Landis Tree

#ifndef _CORE_AVL_TREE_H_
#define _CORE_AVL_TREE_H_

#include "gbstree.h"

namespace gsystem { // gsystem

template<typename KeyT, typename ValueT>
struct GAvlTreeNode
	: public GBinTreeNodeT<GAvlTreeNode<KeyT, ValueT>>
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
	: public GBSTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~GAvlTree();
	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual gvoid Delete(const KeyT &key);

private:
	// 单右旋
	gvoid SingleRotateRight(NodeT *node);
	// 单左旋
	gvoid SingleRotateLeft(NodeT *node);
	// 双右旋
	gvoid DoubleRotateRight(NodeT *node);
	// 双左旋
	gvoid DoubleRotateLeft(NodeT *node);
};

} // namespace gsystem

#endif // _CORE_AVL_TREE_H_