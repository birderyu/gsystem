#pragma once

#include "gallocator.h"
#include "gstring.h"

gvoid Allocator_Test()
{
	// 为基本内置类型分配一个空间
	gint *p_int = GAllocate<gint>();

	// 释放一个基本内置类型的空间
	GDeallocate<gint>(p_int);

	// 为其他类型对象分配一个空间
	// 注意：仅仅分配了空间，若未调用构造函数，对象会处于“未定义”的状态
	GString *p_str = GAllocate<GString>();

	// 释放一个其他类型对象的空间
	// 注意：仅仅释放了空间，若未调用析构函数，可能会存在内存泄漏
	GDeallocate<GString>(p_str);

	// 分配多个连续空间
	gint *p_int_arr = GAllocate<gint>(10);

	// 重新分配多个连续空间
	p_int_arr = GReallocate<gint>(p_int_arr, 20);

	// 释放多个连续空间
	GDeallocate<gint>(p_int_arr);
}
