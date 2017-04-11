#include <gtest/gtest.h>
#include "typedef_test.h"
#include "series_test.h"
#include "binaryheap_test.h"
#include "stack_test.h"
#include "queue_test.h"

#include "gstring.h"
#include "gcstring.h"
#include "gstringlist.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	GString s1(" abcd eFg Dh ijd");
	GString s2("d");

	GStringList ii = s1.Split(s2, false, false);
	for (gsize i = 0; i < ii.Size(); i++)
	{
		if (i == 3)
		{
			GString &sss = ii.GetAt(i);
			gint stop = 1;
			stop++;
		}
		std::cout << i << ": " << ii.GetAt(i).CString() << std::endl;
	}
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}