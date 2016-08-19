#include <iostream>
#include "CsBTree.h"
#include "CsBSTree.h"
#include "CsRBTree.h"

template<class T>
struct NoLessF
	: public CsBinaryF<T, T, cs_bool>
{
	cs_bool operator()(const T &left, const T &right) const
	{
		CsLessF<T> fCompare;
		return !fCompare(left, right);
	}
};

template<class T>
struct NoCompareF
	: public CsBinaryF<T, T, cs_int>
{
	cs_int operator()(const T &left, const T &right) const
	{
		CsCompareF<T> fCompare;
		return 0 - fCompare(left, right);
	}
};

template<typename T>
void Visit(const T &data)
{
	std::cout << data << std::endl;
}

template<typename T = double>
class CTestT
{
public:
	template<typename K = int>
	void test()
	{
		T t = 1.1;
		K i = 2;
		int stop = 1;
	}
};


void TestBTree()
{
	CsBTreeNode<cs_int> *node_3 = new CsBTreeNode<cs_int>(-3);
	CsBTreeNode<cs_int> *node_2 = new CsBTreeNode<cs_int>(-2);
	CsBTreeNode<cs_int> *node_1 = new CsBTreeNode<cs_int>(-1);
	CsBTreeNode<cs_int> *node0 = new CsBTreeNode<cs_int>(0);
	CsBTreeNode<cs_int> *node1 = new CsBTreeNode<cs_int>(1);
	CsBTreeNode<cs_int> *node2 = new CsBTreeNode<cs_int>(2);
	CsBTreeNode<cs_int> *node3 = new CsBTreeNode<cs_int>(3);

	node0->m_pParent = NULL;
	node0->m_pLeft = node_2;
	node0->m_pRight = node2;

	node_2->m_pParent = node2->m_pParent = node0;
	node_2->m_pLeft = node_3;
	node_2->m_pRight = node_1;

	node_3->m_pParent = node_1->m_pParent = node_2;
	node2->m_pLeft = node1;
	node2->m_pRight = node3;
	node3->m_pParent = node1->m_pParent = node2;

	CsBTree<cs_int> btree(node0);
	cs_size_t ncount = btree.GetNodeCount();

	CsBTree<cs_int> btree2;
	cs_bool b = btree2.IsEmpty();
	btree2.Clone(btree);
	cs_size_t ncount2 = btree2.GetNodeCount();
	cs_size_t lcount2 = btree2.GetLeafCount();
	cs_size_t dcount2 = btree2.GetDepth();

	//btree.PreOrderTraverse(Visit);
	btree.InOrderTraverse(Visit);
	//btree.PostOrderTraverse(Visit);

	int stop = 1;
	stop++;
}

void TestBSTree()
{
	CsBSTree<cs_int, NoCompareF<cs_int>> bstree;
	bstree.Insert(0);
	bstree.Insert(-2);
	bstree.Insert(5);
	bstree.Insert(2);
	bstree.Insert(-3);
	bstree.Insert(-1);
	bstree.InOrderTraverse(Visit);

	auto *node = bstree.Find(-3);
	auto *root1 = bstree.GetRoot();
	auto *del = bstree.Delete(0);
	auto *root2 = bstree.GetRoot();

	bstree.InOrderTraverse(Visit);
	int stop = 1;
	stop++;
}

void TestRBTree()
{
	CsRBTree<cs_int> bstree;
	bstree.Insert(0);
	bstree.Insert(0);
	bstree.Insert(-2);
	bstree.Insert(5);
	bstree.Insert(2);
	bstree.Insert(-3);
	bstree.Insert(-1);
	bstree.InOrderTraverse(Visit);

	int stop = 1;
	stop++;
}