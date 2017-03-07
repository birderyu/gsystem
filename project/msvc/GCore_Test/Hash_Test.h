#include "ghashtable.h"
#include "greadblacktree.h"
#include "RBTree.h"

#include <windows.h>

gint TimeTest_Hash(gsize len)
{
	GHashTable<gint, gbyte> hashtable(len * 2);
	GHashTable<gint, gbyte> hashtable2(hashtable);
	for (gsize i = 0; i < len; i++)
	{
		hashtable.Insert(i, 'a');
	}

	gint nStartTime = GetTickCount(); // time
	for (gsize i = 0; i < len; i++)
	{
		hashtable.Find(i);
	}
	gint nEndTime = GetTickCount(); // time
	return nEndTime - nStartTime;
}

gint TimeTest_Tree(gsize len)
{
	GReadBlackTree<gint, gbyte> tree;
	for (gsize i = 0; i < len; i++)
	{
		tree.Insert(i, 'a');
	}
	gint nStartTime = GetTickCount(); // time
	for (gsize i = 0; i < len; i++)
	{
		tree.Find(i);
	}
	gint nEndTime = GetTickCount(); // time
	return nEndTime - nStartTime;
}

gvoid TestHashTable()
{
	gsize len = 10000000;

	gint ___nStartTime = GetTickCount(); // time
	gint findTime_Hash = TimeTest_Hash(len);
	gint ___nMidTime = GetTickCount(); // time
	gint findTime_Tree = TimeTest_Tree(len);
	gint ___nEndTime = GetTickCount(); // time
	gint ___nTime_hash = (___nMidTime - ___nStartTime); // time
	gint ___nTime_tree = (___nEndTime - ___nMidTime); // time

	gint stop = 1;
	stop++;
}

