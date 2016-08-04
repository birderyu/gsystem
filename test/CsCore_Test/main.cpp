#include "SortStack.h"

int main(int argc, char *argv[])
{
	// 测试数据
	double dArr[7] = { 1.2, 3.9, 0.3, 7.2, 4.9, 5.5, 10.2 };

	// 构建一个对象
	CSortStack<double> tStack;

	// 通过预分配空间增加插入的速度（可选）
	//tStack.reserve(10);

	// 插入数据的方法
	for (int i = 0; i < 7; i++)
	{
		tStack.insert(dArr[i]);
	}
	int nSize_1 = tStack.size();

	// 遍历数据的方法一：使用下标（只读）
	for (int i = 0; i < nSize_1; i++)
	{
		// 下标直接访问
		double v_1 = tStack[i];

		// 下标获取迭代器
		CSortStack<double>::const_iterator _citer = tStack.at(i);
		if (_citer != NULL)
		{
			double v_2 = *_citer;
		}
	}

	// 查找数据的方法
	int id = tStack.search(1.2);
	CSortStack<double>::const_iterator cfind = tStack.cfind(1.2);

	// 删除首尾数据的方法
	CSortStack<double>::const_iterator cfront = tStack.pop_front();
	if (cfront != NULL)
	{
		double dfront = *cfront;
	}
	CSortStack<double>::const_iterator cback = tStack.pop_back();
	if (cback != NULL)
	{
		double dback = *cback;
	}
	
	// 删除任意位置数据的方法
	tStack.remove(4.9);
	int nSize_2 = tStack.size();

	// 遍历数据的方法二：使用迭代器
	for (CSortStack<double>::const_iterator citer = tStack.cbegin();
		citer != tStack.cend(); citer++)
	{
		double v = *citer;
	}
}