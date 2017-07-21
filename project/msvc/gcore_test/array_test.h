#pragma once
#include <gtest/gtest.h>
#include "gdynamicarray.h"

TEST(DynamicArrayTest, HandleNoneZeroInput)
{
	using namespace gsystem;
	GDynamicArray<gint> int_arr;
	gsize int_arr_size = 100000000; // 1вк
	int_arr.Resize(int_arr_size);
	for (gsize i = 0; i < int_arr_size; i++)
	{

	}
}