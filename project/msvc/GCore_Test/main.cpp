#include <gtest/gtest.h>
//#include "typedef_test.h"
//#include "series_test.h"
//#include "binaryheap_test.h"
//#include "stack_test.h"
//#include "queue_test.h"
//#include "gfunctional.h"
#include "gvector.h"
#include "gstring.h"

using namespace gsystem;

gint foo(gint val)
{
	return val + 1;
}

gint main(gint argc, gchar *argv[])
{
	GVector<GString> strs;
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}