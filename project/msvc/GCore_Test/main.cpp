#include "typedef_test.h"
#include "gencoding.h"
#include "gstopwatch.h"
#include "gunordermap.h"

#include "ThreePrism.h"

using namespace gsystem;

#include <iostream>
using namespace std;
locale loc("chs");
gint main(gint argc, gchar *argv[])
{
	GStopWatch sw;
	sw.Start();
	for (gsize i = 0; i < 100000; i++)
	{
		double v = VolumeThreePrism(
			-1, 0, -1,
			1, 0, 0,
			0, 1, 0,
			-1, 0, 1,
			1, 0, 1,
			0, 1, 2);
	}
	cout << sw.Stop() << endl;

	//nl_langinfo();
	gcstring8 s_gbk = GGBK("字符");
	gcstring8 s_utf8 = GUTF8("字符");
	gcstring16 s_utf16 = GUTF16("字符");
	gcstring32 s_utf32 = GUTF32("字符");

	gchar8 s_gbk_from_utf8[100];

	//encoding.Utf8StringToGbkString(s_utf8, strlen(s_utf8), s_gbk_from_utf8);

	static allocator<string> alloc;

	gptr p_n = NULL;
	auto p_1 = alloc.allocate(5, p_n);

	auto p = alloc.allocate(5);
	auto head = p;
	string s;
	int i = 0;
	while (i < 5 && cin >> s)
	{
		alloc.construct(p++, s);
		++i;
	}
	cout << "go on" << endl;
	auto temp = alloc.allocate(10);
	auto t = uninitialized_copy(head, p, temp);
	auto h1 = temp;
	while (h1 != t)
	{
		cout << *h1 << " ";
		h1++;
	}
	i = 0;
	head = temp;
	while (i < 5 && cin >> s)
	{
		alloc.construct(t++, s);
		++i;
	}
	while (head != t)
	{
		cout << *head << " ";
		head++;
	}

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");

	return 0;
}