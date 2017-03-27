#include "typedef_test.h"
#include "binaryheap_test.h"
#include "ghuffmantree.h"
#include "gmap.h"
#include "gstopwatch.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}