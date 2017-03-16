#include "typedef_test.h"
using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}