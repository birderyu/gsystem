/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gbinarysorttree.h
** @brief	该文件包含了二叉排序树的定义及实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-07
** @version	1.0
** @see		GBinaryTreeNode
** @see		GBinaryTree
** @see		GBinarySortTree
**
****************************************************************************/

#ifndef _CORE_BINARY_SORT_TREE_H_
#define _CORE_BINARY_SORT_TREE_H_

#include "gbinarytree.h"

template<typename KeyT, typename ValueT>
struct GBinarySortTreeNode 
	: public GBinaryTreeNodeT<GBinarySortTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GBinarySortTreeNode<KeyT, ValueT>>
{
	GBinarySortTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GBinarySortTreeNode<KeyT, ValueT> *parent = GNULL,
		GBinarySortTreeNode<KeyT, ValueT> *left = GNULL,
		GBinarySortTreeNode<KeyT, ValueT> *right = GNULL);

	GBinarySortTreeNode(
		const KeyT &key, ValueT &&value,
		GBinarySortTreeNode<KeyT, ValueT> *parent = GNULL,
		GBinarySortTreeNode<KeyT, ValueT> *left = GNULL,
		GBinarySortTreeNode<KeyT, ValueT> *right = GNULL);
};

template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT >,
	typename NodeT = GBinarySortTreeNode<KeyT, ValueT>>
class GBinarySortTree 
	: public GBinaryTree<NodeT>
{
public:
	typedef GBinarySortTree<KeyT, ValueT, CompareT, NodeT> Tree;
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

private:
	static const Tree m_gTree;

public:
	/****************************************************************************
	**
	** gbinarysorttree.h
	**
	** @class		Filter
	** @brief		二叉排序树过滤器的基类
	** @module		GCore
	**
	** 二叉排序树的过滤器应该是一个仿函数（functor），它的参数传入当前二叉排序树的一个key，
	** 表示当前比较节点的key值。它的返回值除了判断出当前的key值是否满足条件以外，还应该指示出
	** 下一步递归的方向，因此，将返回值定义为一个整数类型（gint）。由于二叉排序树具有排序的特
	** 性，因此过滤器的返回值，除了指示出当前值是否满足规则以外，还应该指示出下一步追踪的方向，
	** 为此，返回值应该是以下值中的一个：
	** 1）FIT_AND_TURN_LEFT，表示满足条件，并向左侧追踪；
	** 2）FIT_AND_TURN_RIGHT，表示满足条件，并向右侧追踪；
	** 3）FIT_AND_TURN_BOTH_SIDE，表示满足条件，并向两个方向追踪；
	** 4）FIT_AND_STOP，表示满足条件，并停止追踪；
	** 5）NO_FIT_AND_TURN_LEFT，表示不满足条件，并向左侧追踪；
	** 6）NO_FIT_AND_TURN_RIGHT，表示不满足条件，并向右侧追踪；
	** 7）NO_FIT_AND_TURN_BOTH_SIDE，表示不满足条件，并向两个方向追踪；
	** 8）NO_FIT_AND_STOP，表示不满足条件，并停止追踪；
	** 注意：规则里的“左”和“右”是指针对二叉排序树的排序规则CompareT而言的左右，即当CompareT
	** 的返回值小于0为左，返回值大于0为右，返回值为0表示等于当前值。
	** 提供以下几个过滤器：
	** EqualTo：表示等于某个值；
	** UnequalTo：表示不等于某个值；
	** FirstOf：表示等于某个值的第一个值；
	** LeftOf：表示在某个值的左边（不包括当前值）；
	** LeftMiddleOf：表示在某个值的左边（包括当前值）；
	** RightOf：表示在某个值的右边（不包括当前值）；
	** RightMiddleOf：表示在某个值的右边（包括当前值）；
	** LeftOpenRightOpenOf：返回满足一个左开右开区间的所有值；
	** LeftClosedRightClosedOf：返回满足一个左闭右闭区间的所有值；
	** LeftOpenRightClosedOf：返回满足一个左开右闭区间的所有值；
	** LeftClosedRightOpenOf：返回满足一个左闭右开区间的所有值。
	**
	****************************************************************************/
	class Filter
	{
	public:
		static const gbyte NO_FIT = 0;						// 不满足条件（000）
		static const gbyte FIT = 1;							// 满足条件（001）
		static const gbyte TURN_LEFT = 2;					// 向左追踪（010）
		static const gbyte TURN_RIGHT = 4;					// 向右追踪（100）
		static const gbyte FIT_AND_TURN_LEFT = 3;			// 满足条件，并向左侧追踪（011）
		static const gbyte FIT_AND_TURN_RIGHT = 5;			// 满足条件，并向右侧追踪（101）
		static const gbyte FIT_AND_TURN_BOTH_SIDE = 7;		// 满足条件，并向两个方向追踪（111）
		static const gbyte FIT_AND_STOP = 1;				// 满足条件，并停止追踪（001）
		static const gbyte NO_FIT_AND_TURN_LEFT = 2;		// 不满足条件，并向左侧追踪（010）
		static const gbyte NO_FIT_AND_TURN_RIGHT = 4;		// 不满足条件，并向右侧追踪（100）
		static const gbyte NO_FIT_AND_TURN_BOTH_SIDE = 6;	// 不满足条件，并向两个方向追踪（110）
		static const gbyte NO_FIT_AND_STOP = 0;				// 不满足条件，并停止追踪（000）

	public:
		Filter() :m_rCompare(m_gTree.m_fCompare) {}
		Filter(const Filter &filter) :m_rCompare(filter.m_rCompare) {}

	protected:
		const CompareT &m_rCompare;
	};
	friend class Filter;

	class EqualTo : public Filter , public GUnaryF<KeyT, gint>
	{
	public:
		EqualTo(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			gint ret = m_rCompare(key, m_tKey);
			if (ret < 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			else if (ret > 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tKey;
	};
	class UnequalTo : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		UnequalTo(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tKey) == 0)
			{
				return NO_FIT_AND_TURN_BOTH_SIDE;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tKey;
	};
	class FirstOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		FirstOf(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			gint ret = m_rCompare(key, m_tKey);
			if (ret < 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			else if (ret > 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_STOP;
		}

	private:
		KeyT m_tKey;
	};
	class LeftOf : public Filter , public GUnaryF<KeyT, gint>
	{
	public:
		LeftOf(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tKey) < 0)
			{
				return FIT_AND_TURN_BOTH_SIDE;
			}
			return NO_FIT_AND_TURN_LEFT;
		}

	private:
		KeyT m_tKey;
	};
	class LeftMiddleOf : public Filter , public GUnaryF<KeyT, gint>
	{
	public:
		LeftMiddleOf(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tKey) <= 0)
			{
				return FIT_AND_TURN_BOTH_SIDE;
			}
			return NO_FIT_AND_TURN_LEFT;
		}

	private:
		KeyT m_tKey;
	};
	class RightOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		RightOf(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tKey) > 0)
			{
				return FIT_AND_TURN_BOTH_SIDE;
			}
			return NO_FIT_AND_TURN_RIGHT;
		}

	private:
		KeyT m_tKey;
	};
	class RightMiddleOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		RightMiddleOf(const KeyT &key) : m_tKey(key) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tKey) >= 0)
			{
				return FIT_AND_TURN_BOTH_SIDE;
			}
			return NO_FIT_AND_TURN_RIGHT;
		}

	private:
		KeyT m_tKey;
	};
	class LeftOpenRightOpenOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		LeftOpenRightOpenOf(const KeyT &left, const KeyT &right)
			:m_tLeft(left), m_tRight(right) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tLeft) <= 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			if (m_rCompare(key, m_tRight) >= 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tLeft, m_tRight;
	};
	class LeftClosedRightClosedOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		LeftClosedRightClosedOf(const KeyT &left, const KeyT &right)
			:m_tLeft(left), m_tRight(right) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tLeft) < 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			if (m_rCompare(key, m_tRight) > 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tLeft, m_tRight;
	};
	class LeftOpenRightClosedOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		LeftOpenRightClosedOf(const KeyT &left, const KeyT &right)
			:m_tLeft(left), m_tRight(right) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tLeft) <= 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			if (m_rCompare(key, m_tRight) > 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tLeft, m_tRight;
	};
	class LeftClosedRightOpenOf : public Filter, public GUnaryF<KeyT, gint>
	{
	public:
		LeftClosedRightOpenOf(const KeyT &left, const KeyT &right)
			:m_tLeft(left), m_tRight(right) {}
		gint operator()(const KeyT &key) const
		{
			if (m_rCompare(key, m_tLeft) < 0)
			{
				return NO_FIT_AND_TURN_RIGHT;
			}
			if (m_rCompare(key, m_tRight) >= 0)
			{
				return NO_FIT_AND_TURN_LEFT;
			}
			return FIT_AND_TURN_BOTH_SIDE;
		}

	private:
		KeyT m_tLeft, m_tRight;
	};
	
public:
	virtual ~GBinarySortTree();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *LastNode();
	const NodeT *LastNode() const;

	gbool Contains(const KeyT &key) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;

	template<typename FilterT> Nodes Search(FilterT &filter);
	template<typename FilterT> ConstNodes Search(FilterT &filter) const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value, gbool *realInsert = GNULL);
	virtual NodeT *Insert(const KeyT &key, ValueT &&value, gbool *realInsert = GNULL);
	virtual gvoid Delete(const KeyT &key, gbool *realDelete = GNULL);
	virtual gvoid Delete(NodeT *node, gbool *realDelete = GNULL);

protected:
	virtual gbool NodeEquals(const NodeT *node1, const NodeT *node2) const;

protected:
	// 非递归实现
	gbool Contains_Unrecursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Unrecursive(const KeyT &key, NodeT *node);
	const NodeT *Find_Unrecursive(const KeyT &key, const NodeT *node) const;
	gvoid Insert_Unrecursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	gvoid Insert_Unrecursive(const KeyT &key, ValueT &&value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	gvoid Delete_Unrecursive(const KeyT &key, NodeT *node, gbool &realDelete);

	// 递归实现（不推荐使用）
	// 对于Insert和Delete操作，其返回值只是作为递归传递参数，并非实际需要的返回值
	gbool Contains_Recursive(const KeyT &key, NodeT *node) const;
	NodeT *Find_Recursive(const KeyT &key, NodeT *node);
	const NodeT *Find_Recursive(const KeyT &key, const NodeT *node) const;
	template<typename FilterT> gvoid Search_Recursive(NodeT *node, FilterT &filter, Nodes &nodes);
	template<typename FilterT> gvoid Search_Recursive(const NodeT *node, FilterT &filter, ConstNodes &nodes) const;
	NodeT *Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	NodeT *Insert_Recursive(const KeyT &key, ValueT &&value, NodeT *node, NodeT *&node_ins, gbool &realInsert);
	NodeT *Delete_Recursive(const KeyT &key, NodeT *node, gbool &realDelete);

	// 交换两个节点
	gbool SwitchNode(NodeT *node1, NodeT *node2);

protected:
	// 比较函数
	static const CompareT m_fCompare;
};

#include "gbinarysorttree.inl"

#endif // _CORE_BINARY_SORT_TREE_H_