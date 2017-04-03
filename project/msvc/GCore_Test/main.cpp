#include "typedef_test.h"
#include "series_test.h"
#include "binaryheap_test.h"
#include "stack_test.h"
#include "queue_test.h"

#include "gfunctional.h"

using namespace gsystem;

gint foo(gint val)
{
	return val + 1;
}

gint main(gint argc, gchar *argv[])
{
	GFunction<gint(gint)> func(foo);
	//func = foo;
	gint val = func(10);

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}