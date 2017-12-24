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


gint main(gint argc, gchar *argv[])
{
	int val = 0;

	//auto const_val_lambda = [=]() { val = 1; }; // error

	//auto mutable_val_lambda = [=]() mutable { val = 1; }; // succeed

	//auto const_ref_lambda = [&]() { val = 1; }; // succeed

	const_ref_functor _const_ref_functor(val);
	_const_ref_functor();


	GFunction<gvoid(gint)> func = foo;
	if (func)
	{
		func(123);
	}
	GFunction<gvoid(gint)> func2;
	func2 = func;
	if (func2)
	{
		func2(123);
	}

	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();
	system("pause");
}