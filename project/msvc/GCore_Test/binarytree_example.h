#include <iostream>
#include "gbinarytree.h"
#include "gbinarysorttree.h"
#include "greadblacktree.h"

template<class T>
struct NoLessF
	: public gnova::GBinaryF<T, T, gbool>
{
	gnova::gbool operator()(const T &left, const T &right) const
	{
		gnova::GLessThanF<T> fCompare;
		return !fCompare(left, right);
	}
};

template<class T>
struct NoCompareF
	: public gnova::GBinaryF<T, T, gint>
{
	gnova::gint operator()(const T &left, const T &right) const
	{
		gnova::GCompareToF<T> fCompare;
		return 0 - fCompare(left, right);
	}
};

gnova::gsize read_node_count = 0;
gnova::gvoid Visit(const gnova::GReadBlackTreeNode<gnova::gint, gnova::gbyte> &node)
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

gnova::gvoid TestBSTree()
{
	gnova::GReadBlackTree<gnova::gint, gnova::gbyte> bstree;
	bstree.Insert(1, 0);
	bstree.Insert(2, 0);
	bstree.Insert(3, 0);
	bstree.Insert(4, 0);
	bstree.Insert(5, 0);

	gnova::GReadBlackTree<gnova::gint, gnova::gbyte>::FirstOf filter(4);
	gnova::GReadBlackTree<gnova::gint, gnova::gbyte>::Nodes nodes = bstree.Search(filter);

	for (gnova::GReadBlackTree<gnova::gint, gnova::gbyte>::Nodes::Iterator iter = nodes.Begin(); iter != nodes.End(); iter++)
	{
		gnova::GReadBlackTree<gnova::gint, gnova::gbyte>::Node *node = *iter;
		gnova::gint key = node->m_tKey;

		std::cout << key << std::endl;
	}
}
