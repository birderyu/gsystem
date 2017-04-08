#pragma once
#include <gtest/gtest.h>
#include <windows.h>
#include "gbinheap.h"
#include "gdynamicarray.h"

/// 产生随机数
gsystem::gint random(gsystem::gint start, gsystem::gint end)
{
	return start + (end - start)*rand() / 0x7fff;
}

gsystem::gvoid testBinaryHeap()
{
	using namespace gsystem;

	// 产生一个长度随机、范围随机的随机数组
	gsize arr_size = random(10000, 30000);
	gint a = random(0, 30000);
	gint b = random(0, 30000);
	gint max_value = a > b ? a : b;
	gint min_value = a < b ? a : b;

	std::cout
		<< "共有"
		<< arr_size
		<< "随机数，"
		<< "其中最小值为："
		<< min_value
		<< "，最小值为："
		<< max_value
		<< std::endl;
	GDynamicArray<gint> arr(arr_size);

	std::cout << "正在构建随机数..." << std::endl;
	for (gsize i = 0; i < arr_size; i++)
	{
		arr[i] = random(min_value, max_value);
	}
	std::cout << "随机数构建成功。" << std::endl;

	// 构建一个最小堆和最大堆
	GMinHeap<gint> minHeap;
	GMaxHeap<gint> maxHeap;
	minHeap.Append(arr);
	maxHeap.Append(arr);

	// 检查数组与二叉堆中的元素是否一一对应
	ASSERT_EQ(minHeap.Size(), arr_size) << "最小堆的数量应该和输入元素保持一致。";
	ASSERT_EQ(maxHeap.Size(), arr_size) << "最大堆的数量应该和输入元素保持一致。";

	// 检查二叉堆的数据是否满足排序要求
	gint last_one = min_value - 1;
	gint this_one = min_value;
	for (gsize i = 0; i < arr_size; i++)
	{
		minHeap.Pop(&this_one);
		ASSERT_LE(last_one, this_one)
			<< "最小堆排序出错，第"
			<< i - 1
			<< "个元素为"
			<< last_one
			<< "而第"
			<< i
			<< "个元素为"
			<< this_one;
		last_one = this_one;
	}

	last_one = max_value + 1;
	this_one = max_value;
	for (gsize i = 0; i < 1000; i++)
	{
		maxHeap.Pop(&this_one);
		ASSERT_GE(last_one, this_one)
			<< "最大堆排序出错，第"
			<< i - 1
			<< "个元素为"
			<< last_one
			<< "而第"
			<< i
			<< "个元素为"
			<< this_one;
		last_one = this_one;
	}
}

TEST(BinaryHeapTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	// 测试10组随机数据
	std::cout << "构建10组测试数据" << std::endl;
	for (gsize i = 0; i < 10; i++)
	{
		std::cout << "第" << i + 1 << "次测试：" << std::endl;
		testBinaryHeap();
		std::cout << "第" << i + 1 << "次测试通过。" << std::endl;
	}
}