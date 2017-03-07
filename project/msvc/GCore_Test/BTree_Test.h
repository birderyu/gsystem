#include <iostream>
#include "gbinarytree.h"
#include "gbinarysorttree.h"
#include "greadblacktree.h"

template<class T>
struct NoLessF
	: public GBinaryF<T, T, gbool>
{
	gbool operator()(const T &left, const T &right) const
	{
		GLessThanF<T> fCompare;
		return !fCompare(left, right);
	}
};

template<class T>
struct NoCompareF
	: public GBinaryF<T, T, gint>
{
	gint operator()(const T &left, const T &right) const
	{
		GCompareToF<T> fCompare;
		return 0 - fCompare(left, right);
	}
};

gsize read_node_count = 0;
gvoid Visit(const GReadBlackTreeNode<gint, gbyte> &node)
{
	if (node.m_nColor == 0)
	{
		read_node_count++;
		std::cout << "k(" << node.m_tKey << "), v("
			<< node.m_tValue << "), c(ºì)"
			<< std::endl;
	}
	else
	{
		//std::cout << "k(" << node.m_tKey << "), v("
		//	<< node.m_tValue << "), c(ºÚ)"
		//	<< std::endl;

	}
	
}

gvoid TestBSTree()
{
	GReadBlackTree<gint, gbyte> bstree;
	bstree.Insert(1, 0);
	bstree.Insert(2, 0);
	bstree.Insert(3, 0);
	bstree.Insert(4, 0);
	bstree.Insert(5, 0);

	GReadBlackTree<gint, gbyte>::FirstOf filter(4);
	GReadBlackTree<gint, gbyte>::Nodes nodes = bstree.Search(filter);

	for (GReadBlackTree<gint, gbyte>::Nodes::Iterator iter = nodes.Begin(); iter != nodes.End(); iter++)
	{
		GReadBlackTree<gint, gbyte>::Node *node = *iter;
		gint key = node->m_tKey;

		std::cout << key << std::endl;
	}
	
	
	gint stop = 1;
	stop++;
}
