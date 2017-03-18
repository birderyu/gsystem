#include "typedef_test.h"
using namespace gsystem;

#include <iostream>
using namespace std;

gint main(gint argc, gchar *argv[])
{
	
	static allocator<string> alloc;

	void *p_n = NULL;
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
}