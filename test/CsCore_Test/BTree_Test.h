#include <iostream>
#include "CsBTree.h"
#include "CsBSTree.h"
#include "CsRBTree.h"

template<typename T>
void Visit(const T &data)
{
	std::cout << data << std::endl;
}

void TestBTree()
{
	CsBTree<cs_int> btree(new CsBTreeNode<cs_int>(0));
	btree.GetRoot()->m_pLeft = new CsBTreeNode<cs_int>(-2);
	btree.GetRoot()->m_pRight = new CsBTreeNode<cs_int>(2);
	btree.GetLeftChild(btree.GetRoot())->m_pLeft = new CsBTreeNode<cs_int>(-3);
	btree.GetLeftChild(btree.GetRoot())->m_pRight = new CsBTreeNode<cs_int>(-1);
	btree.GetRightChild(btree.GetRoot())->m_pLeft = new CsBTreeNode<cs_int>(1);
	btree.GetRightChild(btree.GetRoot())->m_pRight = new CsBTreeNode<cs_int>(3);

	cs_size_t ncount = btree.GetNodeCount();

	CsBTree<cs_int> btree2;
	cs_bool b = btree2.IsEmpty();
	btree2.Clone(btree);
	cs_size_t ncount2 = btree2.GetNodeCount();
	cs_size_t lcount2 = btree2.GetLeafCount();
	cs_size_t dcount2 = btree2.GetDepth();

	//btree.PreOrderTraverse(Visit);
	btree2.InOrderTraverse(Visit);
	//btree.PostOrderTraverse(Visit);

	int stop = 1;
	stop++;
}

void TestBSTree()
{
	CsBSTree<cs_int> bstree;
	bstree.Insert(0);
	bstree.Insert(-1);
	bstree.Insert(5);
	bstree.Insert(2);
	bstree.Insert(-3);
	bstree.InOrderTraverse(Visit);

	CsBSTree<cs_int>::Node *node = bstree.Find(-3);
	CsBSTree<cs_int>::Node *root1 = bstree.GetRoot();
	CsBSTree<cs_int>::Node *root2 = bstree.Delete(2);

	int stop = 1;
	stop++;
}