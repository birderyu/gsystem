/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file grbtree.h
** @brief 红黑树
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-08-17
** @version 1.0
**
** 红黑树是一种特殊的二叉排序树，它在二叉排序树的基础上，增加了以下几个假设项和规范条件：
** 1）每一个节点都有一种颜色，且要么是红色的，要么是黑色的；
** 2）根节点是黑色的；
** 3）空节点（NIL）为黑色的，即值为NULL的节点，如叶子节点的孩子；
** 4）如果一个节点是红色的，那么它的俩个孩子都是黑色的；
** 5）对每个节点，从该节点到其子孙结点的所有路径上包含相同数目的黑色节点。
**
****************************************************************************/

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "gbstree.h"

/****************************************************************************
**
** @name G_RED_BLACK_TREE_NODE_RED
** @brief 红色
**
****************************************************************************/
#define G_RED_BLACK_TREE_NODE_RED 0

/****************************************************************************
**
** @name G_RED_BLACK_TREE_NODE_BLACK
** @brief 黑色
**
****************************************************************************/
#define G_RED_BLACK_TREE_NODE_BLACK 1

namespace gsystem { // gsystem

template<typename KeyT, typename ValueT>
struct GRBTreeNode 
	: public GBinTreeNodeT<GRBTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GRBTreeNode<KeyT, ValueT>>
{
	gsmall m_nColor;

	GRBTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GRBTreeNode<KeyT, ValueT> *parent = GNULL,
		GRBTreeNode<KeyT, ValueT> *left = GNULL,
		GRBTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);

	GRBTreeNode(
		const KeyT &key, ValueT &&value,
		GRBTreeNode<KeyT, ValueT> *parent = GNULL,
		GRBTreeNode<KeyT, ValueT> *left = GNULL,
		GRBTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);
};

/****************************************************************************
**
** @brief 红黑树
**
****************************************************************************/
template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT>,
	typename NodeT = GRBTreeNode<KeyT, ValueT> >
class GRBTree 
	: public GBSTree<KeyT, ValueT, CompareT, NodeT>
{
public:
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

	/****************************************************************************
	**
	** @name RotateLeft
	** @brief 将节点作为轴左旋
	** @param [in] node {NodeT *} 轴节点
	**
	** 当树的部分子树开始向右侧倾斜时，需要将其以这棵子树的根为轴进行左旋。左旋不会改变树的排序性
	** 质，只会将一个倒向右侧的树重新像左侧扶正。左旋之后，子树的根节点将变为原本子树根节点的右节
	** 点，而子树原本的根节点将变为左旋之后子树根节点的左孩子。而原本子树根节点右孩子的左孩子，则
	** 将移动成为原本子树根节点的右孩子。
	**
	** 下图表示一次左旋过程，标记这棵子树为r，假设键的类型为整形，为了查看标记之后键的排序性，我
	** 们标记上假设的键值。
	** 首先是左旋之前的子树的状态，它原本的根节点为e，节点e的右孩子为x：
	**                e(5)
	**               /    \\
	**            le(3)   x(7)
	**                   /    \
	**                 ex(6)   rx(8)
	** 
	** 左旋之后，根变为原本的右孩子节点x，原本的根节点e则变为节点x的左孩子，而节点ex原本是节点x
	** 的左孩子，现在变成了节点e的右孩子：
	**                x(7)
	**              //    \
	**            e(5)    rx(8)
	**            /   \ 
	**        le(3)    ex(6)
	** 
	**
	****************************************************************************/
	gvoid RotateLeft(NodeT *node);
	
	/****************************************************************************
	**
	** @name RotateRight
	** @brief 将节点作为轴右旋
	** @param [in] node {NodeT *} 轴节点
	**
	** 右旋是左旋的逆过程，解决的问题是防止子树过度向左倾斜，右旋同样不会改变树的排序性质。
	**
	** 下图表示一次右旋过程，标记这棵子树为r，同样假设键的类型为整形并标记上假设的键值。
	** 首先是右旋之前的子树的状态，它原本的根节点为x，节点x的左孩子为e：
	**                x(7)
	**              //    \
	**            e(5)    rx(8)
	**            /   \
	**        le(3)    ex(6)
	**
	** 右旋之后，根变为原本的左孩子节点e，原本的根节点x则变为节点e的右孩子，而节点ex原本是节点e
	** 的右孩子，现在变成了节点x的左孩子：
	**                e(5)
	**               /    \\
	**            le(3)   x(7)
	**                   /    \
	**                 ex(6)   rx(8)
	**
	**
	****************************************************************************/
	gvoid RotateRight(NodeT *node);
};

} // namespace gsystem

#include "inline/grbtree.inl"

#undef G_RED_BLACK_TREE_NODE_BLACK
#undef G_RED_BLACK_TREE_NODE_RED

#endif // _CORE_RED_BLACK_TREE_H_