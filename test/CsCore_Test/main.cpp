#include <iostream>
#include <windows.h>
#include "SortStack.h"

#ifndef RAND_MAX
#	define RAND_MAX 0x7fff
#endif

//#define PRINT_TEST_DATA				// 将测试用的数据打印出来
#define TEST_DATA_COUNT 1000000			// 用于测试的随机数的总数量
#define TEST_FUN_COUNT 50000			// 用于做搜索、移除测试数据的数量
#define PRE_ALLOC_MEM				// 预分配空间

using namespace std;

/// 产生随机数
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

int testUseSortStack(double *dArr, double *dFunArr)
{
	cout << endl << "使用SortStack"; // print
	cout << endl << "测试开始："; // print
	cout << endl << "用于测试的随机数数量：" << TEST_DATA_COUNT; // print
	cout << endl << "其中" << TEST_FUN_COUNT * 3 << "个数字用于测试搜索和移除等方法"; // print
	cout << endl << "打印测试数据："; // print
#ifdef PRINT_TEST_DATA
	cout << "是"; // print
#else
	cout << "否"; // print
#endif
	cout << endl << "预分配空间："; // print
#ifdef PRE_ALLOC_MEM
	cout << "是"; // print
#else
	cout << "否"; // print
#endif
	cout << endl;
	if (TEST_DATA_COUNT < TEST_FUN_COUNT * 3)
	{
		cout << endl << "用于测试方法的数据量（" << TEST_FUN_COUNT * 2 << "）"
			<< "不得小于随机数总量(" << TEST_DATA_COUNT << ")，"
			<< "请检查宏，并重新生成程序。" << endl << endl; // print
		system("pause");
		return -1;
	}

	int _nTime = 0;
	int _nStartTime = 0;
	int _nEndTime = 0;

	// 构建测试数据
	cout << endl << "构建" << TEST_DATA_COUNT << "个随机数..."; // print
	_nStartTime = GetTickCount(); // time
	for (size_t i = 0; i < TEST_DATA_COUNT; i++)
	{
		dArr[i] = random(0, 100);
#ifdef PRINT_TEST_DATA
		if (i % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << dArr[i] << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "构建随机数成功！共用时：" << _nTime << "毫秒" << endl;

	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		dFunArr[i] = dArr[i];
	}

	// 构建一个对象
	CSortStack<double> tStack;

	// 通过预分配空间增加插入的速度（可选）
#ifdef PRE_ALLOC_MEM
	cout << endl << "预分配空间..."; // print
	_nStartTime = GetTickCount(); // time
	if (!tStack.reserve(TEST_DATA_COUNT))
	{
		return -1;
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "预分配空间成功！共用时：" << _nTime << "毫秒" << endl; // print
#else
	cout << endl << "没有选择预分配空间" << endl; // print
#endif

	// 插入数据的方法
	cout << endl << "插入数据..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_DATA_COUNT; i++)
	{
		tStack.insert(dArr[i]);
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "插入数据成功！共用时：" << _nTime << "毫秒" << endl; // print

	// 遍历数据的方法一：使用下标（只读）
	int nSize = tStack.size();
	cout << endl << "遍历数据的方法一，使用下标（只读）..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < nSize; i++)
	{
		// 下标直接访问
		double v = tStack[i];
#ifdef PRINT_TEST_DATA
		if (i % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << v << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "遍历数据结束！共用时：" << _nTime << "毫秒" << endl; // print

	// 遍历数据的方法二：使用迭代器
	cout << endl << "遍历数据的方法二，使用迭代器（只读）..."; // print
	_nStartTime = GetTickCount(); // time
	int nIndex = 0;
	for (CSortStack<double>::const_iterator citer = tStack.cbegin();
		citer != tStack.cend(); citer++)
	{
		double v = *citer;
#ifdef PRINT_TEST_DATA
		if (nIndex++ % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << v << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "遍历数据结束！共用时：" << _nTime << "毫秒" << endl; // print

	// 查找数据的方法
	cout << endl << "搜索" << TEST_FUN_COUNT << "个数据..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		int id = tStack.search(dFunArr[i]);
#ifdef PRINT_TEST_DATA
		cout << endl << "数字：" << _dTestData[i] << "，位置：" << id;	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "搜索数据结束！共用时：" << _nTime << "毫秒" << endl; // print

	// 删除首尾数据的方法
	cout << endl << "移除前：" << TEST_FUN_COUNT << "个数据..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		CSortStack<double>::const_iterator cfront = tStack.pop_front();
		if (cfront != NULL)
		{
			double dfront = *cfront;
#ifdef PRINT_TEST_DATA
			if (nIndex++ % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << dfront << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "从首移除数据结束！共用时：" << _nTime << "毫秒" << endl; // print

	cout << endl << "移除后：" << TEST_FUN_COUNT << "个数据..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		CSortStack<double>::const_iterator cback = tStack.pop_back();
		if (cback != NULL)
		{
			double dback = *cback;
#ifdef PRINT_TEST_DATA
			if (nIndex++ % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << dback << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "从尾搜索数据结束！共用时：" << _nTime << "毫秒" << endl; // print


	// 删除任意位置数据的方法
	int _nSuc = 0;
	int _nFal = 0;
	cout << endl << "从任意位置移除" << TEST_FUN_COUNT << "个数据..."; // print
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		bool bRet = tStack.remove(dFunArr[i]);
		if (bRet) _nSuc++;
		else _nFal++;
#ifdef PRINT_TEST_DATA
		cout << endl << "移除数字" << _dTestData[i];	// print
		if (bRet) cout << "成功";
		else cout << "失败，数字不存在";
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "移除数据结束！共" << _nSuc << "个数字移除成功，"
		<< _nFal << "个数字移除失败（数字不存在）。"
		<< "共用时：" << _nTime << "毫秒" << endl; // print

	nSize = tStack.size();
	cout << endl << "最终还剩" << nSize << "个数据："; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < nSize; i++)
	{
		// 下标直接访问
		CSortStack<double>::const_iterator _citer = tStack.at(i);
		if (_citer != NULL)
		{
			double v = *_citer;
#ifdef PRINT_TEST_DATA
			if (i % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << v << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "遍历数据结束！共用时：" << _nTime << "毫秒" << endl; // print

	cout << endl;
	system("pause");
	return 0;
}

int main(int argc, char *argv[])
{
	double *dArr = new double[TEST_DATA_COUNT];
	double *dFunArr = new double[TEST_FUN_COUNT];
	int nRet = testUseSortStack(dArr, dFunArr);
	delete[] dArr;
	delete[] dFunArr;
}