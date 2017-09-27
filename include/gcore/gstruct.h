#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 一维链表
** @template T {type} 元素的类型
**
********************************************************************************/
template<typename T>
struct GListT
{
	/****************************************************************************
	**
	** 最大长度
	**
	****************************************************************************/
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** 空下标
	**
	****************************************************************************/
	static const gsize NULL_POS = G_LIST_NULL_POS;
};

/********************************************************************************
**
** @brief 二维表
** @template T {type} 元素的类型
**
********************************************************************************/
template<typename T>
struct GTableT
{
	/****************************************************************************
	**
	** 最大行数
	**
	****************************************************************************/
	static const gsize MAX_ROW_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** 空行标
	**
	****************************************************************************/
	static const gsize NULL_ROW_POS = G_LIST_NULL_POS;

	/****************************************************************************
	**
	** 最大列数
	**
	****************************************************************************/
	static const gsize MAX_COLUMN_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** 空列标
	**
	****************************************************************************/
	static const gsize NULL_COLUMN_POS = G_LIST_NULL_POS;
};

/// 单向链表节点
template<typename T>
struct GPreviousNodeT
{
	T *m_pPrevious;

	GPreviousNodeT(T *previous) GNOEXCEPT;
};

/// 单向链表节点
template<typename T>
struct GNextNodeT
{
	T *m_pNext;

	GNextNodeT(T *node) GNOEXCEPT;
};

/// 双向链表节点
template<typename T>
struct GPreviousNextNodeT
	: public GPreviousNodeT<T>, GNextNodeT<T>
{
	GPreviousNextNodeT(T *previous, T *next) GNOEXCEPT;
};

/// 二叉树节点
template<typename T>
struct GBinTreeNodeT
{
	T *m_pParent;	// 双亲
	T *m_pLeft;		// 左孩子
	T *m_pRight;	// 右孩子

	GBinTreeNodeT(T *parent, T *left, T *right) GNOEXCEPT;

	// 左兄弟
	const T *LeftSibling() const GNOEXCEPT;

	// 右兄弟
	const T *RightSibling() const GNOEXCEPT;

	// 中序遍历的前驱节点
	const T *Next() const GNOEXCEPT;
	T *Next() GNOEXCEPT;

	// 中序遍历的后继节点
	const T *Previous() const GNOEXCEPT;
	T *Previous() GNOEXCEPT;

	// 中序遍历的首节点
	const T *First() const GNOEXCEPT;
	T *First() GNOEXCEPT;

	// 中序遍历的尾节点
	const T *Last() const GNOEXCEPT;
	T *Last() GNOEXCEPT;
};

/// 数据节点
template<typename T>
struct GValueNodeT
{
	T m_tData;

	GValueNodeT(const T &value) GNOEXCEPT;
	GValueNodeT(T &&value) GNOEXCEPT;
};

/// 单孩子节点
template<typename T>
struct GChildNodeT
{
	T *m_pChild;

	GChildNodeT(const T *node) GNOEXCEPT;
};

/// 键值对节点
template<typename KeyT, typename ValueT>
struct GPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	GPairNodeT(const KeyT &key, const ValueT &value) GNOEXCEPT;
	GPairNodeT(const KeyT &key, ValueT &&value) GNOEXCEPT;
};

// 哑节点
struct GDummyNodeT
{

};

} // namespace gsystem

#include "inline/gstruct.inl"

#endif // _CORE_STRUCTURE_H_