#ifndef _CORE_NODE_H_
#define _CORE_NODE_H_

#include "CsGlobal.h"

/// 一维链表通用模式定义
template<typename ListT>
struct CsListT
{
	static const cs_size_t MAX_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_POS = CS_LIST_NULL_POS;
};

/// 单向链表节点
template<typename NodeT>
struct CsSingleLinkedListNodeT
{
	NodeT *m_pNext;

	CsSingleLinkedListNodeT(NodeT *);
};

/// 双向链表节点
template<typename NodeT>
struct CsDoubleLinkedListNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	CsDoubleLinkedListNodeT(NodeT *previous, NodeT *next);
};

/// 二叉树节点
template<typename NodeT>
struct CsBinaryTreeNodeT
{
	NodeT *m_pParent;	// 双亲
	NodeT *m_pLeft;		// 左孩子
	NodeT *m_pRight;	// 右孩子

	CsBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right);

	// 左兄弟
	const NodeT *LeftSibling() const;

	// 右兄弟
	const NodeT *RightSibling() const;

	// 中序遍历的前驱节点
	const NodeT *Next() const;

	// 中序遍历的后继节点
	const NodeT *Previous() const;

	// 中序遍历的首节点
	const NodeT *First() const;
	NodeT *First();

	// 中序遍历的尾节点
	const NodeT *Last() const;
	NodeT *Last();
};

/// 数据节点
template<typename DataT>
struct CsDataNodeT
{
	DataT m_tData;

	CsDataNodeT(const DataT &);
};

/// 键值对节点
template<typename KeyT, typename ValueT>
struct CsKeyValueNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	CsKeyValueNodeT(const KeyT &key, const ValueT &value);
};

#include "CsStructure.inl"

#endif // _CORE_NODE_H_