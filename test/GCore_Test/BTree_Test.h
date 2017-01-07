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
	
	for (gsize i = 0; i < 10000000; i++)
	{
		bstree.Insert(10000000 - i, 'a');
	}

	for (gsize i = 0; i < 10000000; i++)
	{
		bstree.Delete(i);
	}


	//bstree2.PreOrderTraverse(Visit);
	
	//bstree2.PostOrderTraverse(Visit);

	gsize nc = bstree.NodeCount();
	gsize lc = bstree.LeafCount();
	gsize d = bstree.Depth();

	//bstree.InOrderTraverse(Visit);
	bstree.InOrderTraverse(Visit);
	
	gint stop = 1;
	stop++;
}
