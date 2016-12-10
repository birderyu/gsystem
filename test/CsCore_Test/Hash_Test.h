#include "CsHashTable.h"
#include "CsReadBlackTree.h"
#include "RBTree.h"

#include <windows.h>

cs_void TimeTest_Hash(cs_size_t len)
{
	CsHashTable<cs_int, cs_byte> hashtable(len);
	for (cs_size_t i = 0; i < len; i++)
	{
		hashtable.Insert(i, 'a');
	}
	for (cs_size_t i = 0; i < len; i++)
	{
		hashtable.Find(i);
	}
}

cs_void TimeTest_Tree(cs_size_t len)
{
	CsReadBlackTree<cs_int, cs_byte> tree;
	//CsBinarySortTree<cs_int, cs_byte> tree;
	//RB_Tree<cs_int, cs_byte> tree;
	for (cs_size_t i = 0; i < len; i++)
	{
		tree.Insert(i, 'a');
	}
	for (cs_size_t i = 0; i < len; i++)
	{
		tree.Find(i);
		//tree.find(i);
	}
}

cs_void TestHashTable()
{
	cs_size_t len = 10000000;

	cs_int ___nStartTime = GetTickCount(); // time
	TimeTest_Hash(len);
	cs_int ___nMidTime = GetTickCount(); // time
	TimeTest_Tree(len);
	cs_int ___nEndTime = GetTickCount(); // time
	cs_int ___nTime_hash = (___nMidTime - ___nStartTime); // time
	cs_int ___nTime_tree = (___nEndTime - ___nMidTime); // time

	int stop = 1;
	stop++;
}

