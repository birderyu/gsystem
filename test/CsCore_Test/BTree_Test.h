#include <iostream>
#include "CsBinaryTree.h"
#include "CsBinarySortTree.h"
#include "CsReadBlackTree.h"

template<class T>
struct NoLessF
	: public CsBinaryF<T, T, cs_bool>
{
	cs_bool operator()(const T &left, const T &right) const
	{
		CsLessThanF<T> fCompare;
		return !fCompare(left, right);
	}
};

template<class T>
struct NoCompareF
	: public CsBinaryF<T, T, cs_int>
{
	cs_int operator()(const T &left, const T &right) const
	{
		CsCompareToF<T> fCompare;
		return 0 - fCompare(left, right);
	}
};

cs_size_t read_node_count = 0;
cs_void Visit(const CsReadBlackTreeNode<cs_int, cs_byte> &node)
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

cs_void TestBSTree()
{
	CsReadBlackTree<cs_int, cs_byte> bstree;
	
	for (cs_size_t i = 0; i < 10000000; i++)
	{
		bstree.Insert(10000000 - i, 'a');
	}

	for (cs_size_t i = 0; i < 10000000; i++)
	{
		bstree.Delete(i);
	}


	//bstree2.PreOrderTraverse(Visit);
	
	//bstree2.PostOrderTraverse(Visit);

	cs_size_t nc = bstree.NodeCount();
	cs_size_t lc = bstree.LeafCount();
	cs_size_t d = bstree.Depth();

	//bstree.InOrderTraverse(Visit);
	bstree.InOrderTraverse(Visit);
	
	cs_int stop = 1;
	stop++;
}
