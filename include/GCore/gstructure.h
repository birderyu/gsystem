#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "gglobal.h"

/// 一维表通用模式定义
template<typename ListT>
struct GListT
{
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_POS = G_LIST_NULL_POS;
};

/// 二维表通用模式定义
template<typename TableT>
struct GTableT
{
	static const gsize MAX_ROW_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_ROW_POS = G_LIST_NULL_POS;
	static const gsize MAX_COLUMN_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_COLUMN_POS = G_LIST_NULL_POS;
};

/// 单向链表节点
template<typename NodeT>
struct GNextNodeT
{
	NodeT *m_pNext;

	GNextNodeT(NodeT *);
};

/// 双向链表节点
template<typename NodeT>
struct GPreviousNextNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	GPreviousNextNodeT(NodeT *previous, NodeT *next);
};

/// 二叉树节点
template<typename NodeT>
struct GBinaryTreeNodeT
{
	NodeT *m_pParent;	// 双亲
	NodeT *m_pLeft;		// 左孩子
	NodeT *m_pRight;	// 右孩子

	GBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right);

	// 左兄弟
	const NodeT *LeftSibling() const;

	// 右兄弟
	const NodeT *RightSibling() const;

	// 中序遍历的前驱节点
	const NodeT *Next() const;
	NodeT *Next();

	// 中序遍历的后继节点
	const NodeT *Previous() const;
	NodeT *Previous();

	// 中序遍历的首节点
	const NodeT *First() const;
	NodeT *First();

	// 中序遍历的尾节点
	const NodeT *Last() const;
	NodeT *Last();
};

/// 数据节点
template<typename DataT>
struct GDataNodeT
{
	DataT m_tData;

	GDataNodeT(const DataT &);
};

/// 单孩子节点
template<typename NodeT>
struct GChildNodeT
{
	NodeT *m_pChild;

	GChildNodeT(const NodeT *);
};

/// 键值对节点
template<typename KeyT, typename ValueT>
struct GPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	GPairNodeT(const KeyT &key, const ValueT &value);
	GPairNodeT(const KeyT &key, ValueT &&value);
};

// 哑节点
struct GDummyNodeT
{

};

#include "gstructure.inl"

#endif // _CORE_STRUCTURE_H_