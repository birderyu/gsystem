#include "ghashtable.h"
#include "greadblacktree.h"
#include "RBTree.h"

#include <windows.h>

gvoid TimeTest_Hash(gsize len)
{
	GHashTable<gint, gbyte> hashtable(len);
	for (gsize i = 0; i < len; i++)
	{
		hashtable.Insert(i, 'a');
	}
	for (gsize i = 0; i < len; i++)
	{
		hashtable.Find(i);
	}
}

gvoid TimeTest_Tree(gsize len)
{
	GReadBlackTree<gint, gbyte> tree;
	//CsBinarySortTree<cs_int, cs_byte> tree;
	//RB_Tree<cs_int, cs_byte> tree;
	for (gsize i = 0; i < len; i++)
	{
		tree.Insert(i, 'a');
	}
	for (gsize i = 0; i < len; i++)
	{
		tree.Find(i);
		//tree.find(i);
	}
}

gvoid TestHashTable()
{
	gsize len = 10000000;

	gint ___nStartTime = GetTickCount(); // time
	TimeTest_Hash(len);
	gint ___nMidTime = GetTickCount(); // time
	TimeTest_Tree(len);
	gint ___nEndTime = GetTickCount(); // time
	gint ___nTime_hash = (___nMidTime - ___nStartTime); // time
	gint ___nTime_tree = (___nEndTime - ___nMidTime); // time

	int stop = 1;
	stop++;
}

