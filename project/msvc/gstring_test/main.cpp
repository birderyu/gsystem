#include <gtest/gtest.h>
//#include "typedef_test.h"
//#include "series_test.h"
//#include "binaryheap_test.h"
//#include "stack_test.h"
//#include "queue_test.h"
//#include "hashtable_test.h"
//#include "rbtree_test.h"

#include "gstopwatch.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	/*
	//GRBTree<gint, gint> mmap;
	//GHashTable<gint, gint> mmap(10000000);
	GStopWatch sw;
	for (int i = 0; i < 10000000; i++)
	{
		mmap.Insert(i, 0);
	}
	gulong t1 = sw.Stop();

	sw.Start();
	for (int i = 0; i < 10000000; i++)
	{
		mmap.Find(i);
	}
	gulong t2 = sw.Stop();

	std::cout << "构建用时: " << t1 << "ms, "
		<< "查询用时: " << t2 << "ms" 
		//<< ", 树深度: " << mmap.Depth() 
		<< std::endl; // for test
	*/

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}