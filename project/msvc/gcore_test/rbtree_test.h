#pragma once
#include <gtest/gtest.h>
#include "gbintree.h"
#include "gbstree.h"
#include "grbtree.h"
#include "gstring.h"

#define GRED		0
#define GBLACK		1

template <typename NodeT>
struct GCheckRBTreeNode
{
	gsystem::gvoid operator()(const NodeT &node)
	{
		gsystem::gsmall color = node.m_nColor;

		// 1）每个结点要么是红的，要么是黑的；
		if (color != GRED && color != GBLACK)
		{
			//ASSERT_EQ(false) << "每个结点要么是红的，要么是黑的，但该节点的颜色是：" << color;
			std::cout << "每个结点要么是红的，要么是黑的，但该节点的颜色是：" << (gint)color << std::endl;
			return;
		}

		// 2）根结点必须是黑的
		if (!node.m_pParent)
		{
			//ASSERT_EQ(color, GBLACK) << "根结点必须是黑的，但该节点的颜色是：" << (gint)color;
			if (color != GBLACK)
			{
				std::cout << "根结点必须是黑的，但该节点的颜色是：" << (gint)color << std::endl;
				return;
			}
		}

		// 4）如果一个结点是红的，那么它的俩个儿子都是黑的；
		if (color == GRED)
		{
			if (node.m_pLeft)
			{
				/*
				ASSERT_EQ(node.m_pLeft->m_nColor, GBLACK)
					<< "如果一个结点是红的，那么它的左孩子是黑的，但该节点的左孩子颜色是："
					<< (gint)(node.m_pLeft->m_nColor);
					*/
				if (node.m_pLeft->m_nColor != GBLACK)
				{
					std::cout << "如果一个结点是红的，那么它的左孩子是黑的，但该节点的左孩子颜色是："
						<< (gint)(node.m_pLeft->m_nColor) << std::endl;
					return;
				}
			}
			if (node.m_pRight)
			{
				/*
				ASSERT_EQ(node.m_pRight->m_nColor, GBLACK)
					<< "如果一个结点是红的，那么它的右孩子是黑的，但该节点的右孩子颜色是："
					<< (gint)(node.m_pRight->m_nColor);
					*/
				if (node.m_pRight->m_nColor != GBLACK)
				{
					std::cout << "如果一个结点是红的，那么它的右孩子是黑的，但该节点的右孩子颜色是："
						<< (gint)(node.m_pRight->m_nColor) << std::endl;
					return;
				}
			}
		}

		// 5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
		gsystem::gint other = -1;
		if (!check5(&node, &node, other, 0))
		{
			return;
		}
	}

private:
	// root: 根节点
	// node: 当前节点
	// other: 到其他叶子节点路径上的黑色节点的数量，初始值为-1，表示当前路径是第一条
	// current：当前路径上黑色节点的数量
	gsystem::gbool check5(const NodeT *root, const NodeT *node, gsystem::gint &other, gsystem::gint current)
	{
		if (!node)
		{
			// 已经到了NIL节点
			current++;
			if (other == -1)
			{
				other = current;
				return true;
			}
			else
			{
				if (other != current)
				{
					std::cout << "当前路径中黑色节点的数目不满足条件5: " << root->m_tKey << std::endl;
					return false;
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			if (node->m_nColor == GBLACK)
			{
				current++;
			}
			return check5(root, node->m_pLeft, other, current)
				&& check5(root, node->m_pRight, other, current);
		}
	}
};


TEST(RedBlackTreeTest, HandleNoneZeroInput)
{
	using namespace gsystem;
	gsize size = 5;

	GRBTree<gint, gint> rbt;
	GCheckRBTreeNode<GRBTree<gint, gint>::Node> checker;
	std::cout << "插入数据：" << std::endl;
	for (gint i = 0; i < size; i++)
	{
		gint key = i * i * (i % 2 == 0 ? (-1) : 1);
		rbt.Insert(key, 0);
		rbt.PreOrderTraverse(checker); // 每插入一条数据，都做一次判断
	}
	std::cout << "删除数据：" << std::endl;
	for (gsize i = 0; i < size; i++)
	{
		GRBTree<gint, gint>::Node *root = rbt.Root();
		gint key = root->m_tKey;
		if (root->m_pLeft)
		{
			key = root->m_pLeft->m_tKey;
		}
		else if (root->m_pRight)
		{
			key = root->m_pRight->m_tKey;
		}
		rbt.Delete(key);
		rbt.PreOrderTraverse(checker); // 每删除一条数据，都做一次判断
	}
	
}

#undef GBLACK
#undef GRED
