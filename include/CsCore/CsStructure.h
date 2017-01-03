#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "CsGlobal.h"

/// 一维表通用模式定义
template<typename ListT>
struct CsListT
{
	static const cs_size_t MAX_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_POS = CS_LIST_NULL_POS;
};

/// 二维表通用模式定义
template<typename TableT>
struct CsTableT
{
	static const cs_size_t MAX_ROW_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_ROW_POS = CS_LIST_NULL_POS;
	static const cs_size_t MAX_COLUMN_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_COLUMN_POS = CS_LIST_NULL_POS;
};

/// 单向链表节点
template<typename NodeT>
struct CsNextNodeT
{
	NodeT *m_pNext;

	CsNextNodeT(NodeT *);
};

/// 双向链表节点
template<typename NodeT>
struct CsPreviousNextNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	CsPreviousNextNodeT(NodeT *previous, NodeT *next);
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

/// 单孩子节点
template<typename NodeT>
struct CsChildNodeT
{
	NodeT *m_pChild;

	CsChildNodeT(const NodeT *);
};

/// 键值对节点
template<typename KeyT, typename ValueT>
struct CsPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	CsPairNodeT(const KeyT &key, const ValueT &value);
};

// 哑节点
struct CsDummyNodeT
{

};

#include "CsStructure.inl"

#endif // _CORE_STRUCTURE_H_