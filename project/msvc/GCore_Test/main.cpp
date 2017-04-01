﻿#include "typedef_test.h"
#include "series_test.h"
#include "binaryheap_test.h"
#include "stack_test.h"
#include "queue_test.h"

#include "gfunctional.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}