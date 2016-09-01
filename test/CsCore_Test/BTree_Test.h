#include <iostream>
#include "CsBinTree.h"
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
	CsBinTreeNode<cs_int> *node_3 = new CsBinTreeNode<cs_int>(-3);
	CsBinTreeNode<cs_int> *node_2 = new CsBinTreeNode<cs_int>(-2);
	CsBinTreeNode<cs_int> *node_1 = new CsBinTreeNode<cs_int>(-1);
	CsBinTreeNode<cs_int> *node0 = new CsBinTreeNode<cs_int>(0);
	CsBinTreeNode<cs_int> *node1 = new CsBinTreeNode<cs_int>(1);
	CsBinTreeNode<cs_int> *node2 = new CsBinTreeNode<cs_int>(2);
	CsBinTreeNode<cs_int> *node3 = new CsBinTreeNode<cs_int>(3);

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

	CsBinTree<cs_int> btree(node0);
	cs_size_t ncount = btree.GetNodeCount();

	CsBinTree<cs_int> btree2;
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
	CsBSTree<cs_int, CsCompareF<cs_int>, CsRBTreeNode<cs_int>> bstree;
	auto n1 = bstree.InsertByKey(0);
	auto n2 = bstree.InsertByKey(-2);
	auto n3 = bstree.InsertByKey(5);
	auto n4 = bstree.InsertByKey(2);
	auto n5 = bstree.InsertByKey(-3);
	auto n6 = bstree.InsertByKey(-1);
	auto n6_1 = bstree.InsertByKey(-1);
	bstree.InOrderTraverse(Visit);

	//auto *node = bstree.Find(-3);
	//auto *root1 = bstree.GetRoot();
	//auto *del = bstree.Delete(0);
	//auto *root2 = bstree.GetRoot();
	//bstree.InOrderTraverse(Visit);

	auto n = bstree.FirstNode();
	n = bstree.NextNode(n);
	n = bstree.PreviousNode(n);
	n = bstree.LastNode();

	int stop = 1;
	stop++;
}

void TestRBTree()
{
	CsRBTree<cs_int> bstree;
	bstree.InsertByKey(0);
	bstree.InsertByKey(1);
	bstree.InsertByKey(2);
	bstree.InsertByKey(3);
	bstree.InsertByKey(4);
	bstree.InsertByKey(5);
	bstree.InsertByKey(6);
	bstree.InsertByKey(7);
	bstree.InsertByKey(8);
	bstree.InsertByKey(9);
	bstree.InsertByKey(10);
	bstree.InsertByKey(11);
	bstree.InsertByKey(12);
	bstree.InsertByKey(13);
	bstree.InsertByKey(14);
	bstree.InsertByKey(15);
	bstree.InsertByKey(16);
	bstree.InsertByKey(17);
	bstree.InsertByKey(18);
	bstree.InsertByKey(19);
	bstree.InsertByKey(20);
	for (int i = 0; i < 10000; i++)
	{
		bstree.InsertByKey(i + 1000);
	}

	cs_size_t d = bstree.GetDepth();


	auto n = bstree.GetRoot();

	bstree.InOrderTraverse(Visit);

	int stop = 1;
	stop++;
}