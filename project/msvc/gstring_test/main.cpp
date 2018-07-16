//#include <gtest/gtest.h>
//#include "typedef_test.h"
//#include "series_test.h"
//#include "binaryheap_test.h"
//#include "stack_test.h"
//#include "queue_test.h"
//#include "hashtable_test.h"
//#include "rbtree_test.h"

#include <iostream>
#include "gstopwatch.h"
#include "gdynamicarray.h"
#include "gutility.h"
#include "gfunctional.h"

using namespace gsystem;

gvoid foo(gint a)
{
	std::cout << a << std::endl;
}

class _functor
{
private:
	int _x, _y;

public:
	_functor(int x, int y) : _x(x), _y(y) {}

	int operator()() const
	{
		return _x + _y;
	}
};

class const_val_functor
{
private:
	int &_val;

public:
	const_val_functor(int &val) : _val(val) {}

	void operator()() const
	{
		// 错误，在const函数中无法修改成员变量的值
		_val = 1; // error
	}
};

class const_ref_functor 
{
private:
	int &_val;

public:
	const_ref_functor(int &val) : _val(val) {}
	
	void operator()() const
	{
		// 正确，在const函数中可以修改引用成员变量指向的变量，并非改变引用本身
		_val = 1; // succeed
	}
};

struct S
{
	int a;
	int b;
};


gint main(gint argc, gchar *argv[])
{
	int i = 1;
	S *s = (S *)i;
	
	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();
	system("pause");
}