#include <gtest/gtest.h>
//#include "typedef_test.h"
//#include "series_test.h"
//#include "binaryheap_test.h"
//#include "stack_test.h"
//#include "queue_test.h"
//#include "hashtable_test.h"
//#include "rbtree_test.h"

#include "gstopwatch.h"
#include "gdynamicarray.h"
#include "gutility.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	for (gsize i = 0; i < 1000000000; i++)
	{
		// 分配
		gint *ptr = GAllocate<gint>(10);
		// 释放
		GDeallocate<gint>(ptr);
	}

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}