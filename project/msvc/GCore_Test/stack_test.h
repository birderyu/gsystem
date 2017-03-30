#pragma once
#include <gtest/gtest.h>
#include "garraystack.h"
#include "gliststack.h"
#include "gstring.h"

TEST(ArrayStackTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GArrayStack<gint> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	ASSERT_EQ(5, stack.Size()) << "栈中的元素个数应该是5，但这里是" << stack.Size();
	ASSERT_EQ(5, stack.Top()) << "栈顶元素应该是5，但这里是" << stack.Top();

	gint top_value = 0;
	stack.Pop(&top_value);
	ASSERT_EQ(5, top_value) << "栈顶元素应该是5，但这里是" << top_value;
	stack.Pop(&top_value);
	ASSERT_EQ(4, top_value) << "栈顶元素应该是4，但这里是" << top_value;

	stack.Push(10);
	ASSERT_EQ(4, stack.Size()) << "栈中的元素个数应该是4，但这里是" << stack.Size();
	stack.Pop(&top_value);
	ASSERT_EQ(10, top_value) << "栈顶元素应该是10，但这里是" << top_value;
	
	stack.Pop(&top_value);
	ASSERT_EQ(3, top_value) << "栈顶元素应该是3，但这里是" << top_value;
	
	stack.Clear();
	ASSERT_EQ(0, stack.Size()) << "栈中的元素个数应该是0，但这里是" << stack.Size();

	// 插入一百万个元素
	for (gsize i = 0; i < 1000000; i++)
	{
		stack.Push(i);
	}
	ASSERT_EQ(1000000, stack.Size()) << "栈中的元素个数应该是1000000，但这里是" << stack.Size();
	for (gint i = 1000000 - 1; i >= 0; i--)
	{
		stack.Pop(&top_value);
		ASSERT_EQ(i, top_value) << "栈顶元素应该是" << i << "，但这里是" << top_value;
	}
	ASSERT_TRUE(stack.IsEmpty()) << "栈应该被置空，但这里不为空";

	stack.Push(100);
	stack.Push(200);
	stack.Push(300);
	stack.Push(400);
	stack.Pop();

	// 验证拷贝构造
	GArrayStack<gint> _stack(stack);
	ASSERT_EQ(3, _stack.Size()) << "栈中的元素个数应该是3，但这里是" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "栈中的元素不应该为空";
	_stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "栈顶元素应该是300，但这里是" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "栈顶元素应该是200，但这里是" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "栈顶元素应该是100，但这里是" << top_value;

	// 验证移动构造
	GArrayStack<gint> __stack(GMove(stack));
	ASSERT_TRUE(stack.IsEmpty());
	__stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "栈顶元素应该是300，但这里是" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "栈顶元素应该是200，但这里是" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "栈顶元素应该是100，但这里是" << top_value;

	stack.Push(400);
	stack.Push(500);
	stack.Push(600);
	stack.Push(700);
	stack.Pop();

	// 验证拷贝赋值
	GArrayStack<gint> _stack_;
	_stack_ = stack;
	ASSERT_EQ(3, _stack_.Size()) << "栈中的元素个数应该是3，但这里是" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "栈中的元素不应该为空";
	_stack_.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "栈顶元素应该是600，但这里是" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "栈顶元素应该是500，但这里是" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "栈顶元素应该是400，但这里是" << top_value;

	// 验证移动赋值
	GArrayStack<gint> __stack__;
	__stack__ = GMove(stack);
	ASSERT_TRUE(stack.IsEmpty());
	__stack__.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "栈顶元素应该是600，但这里是" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "栈顶元素应该是500，但这里是" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "栈顶元素应该是400，但这里是" << top_value;

	// 一个存放String类型的栈
	GArrayStack<GString> stack_str;
	stack_str.Push("abc");
	stack_str.Push("this is stack test of gsystem test.");
	ASSERT_EQ(2, stack_str.Size()) << "栈中的元素个数应该是2，但这里是" << stack_str.Size();
	GString str;
	stack_str.Pop(&str);
	ASSERT_EQ("this is stack test of gsystem test.", str);
}

TEST(ListStackTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GListStack<gint> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	ASSERT_EQ(5, stack.Size()) << "栈中的元素个数应该是5，但这里是" << stack.Size();
	ASSERT_EQ(5, stack.Top()) << "栈顶元素应该是5，但这里是" << stack.Top();

	gint top_value = 0;
	stack.Pop(&top_value);
	ASSERT_EQ(5, top_value) << "栈顶元素应该是5，但这里是" << top_value;
	stack.Pop(&top_value);
	ASSERT_EQ(4, top_value) << "栈顶元素应该是4，但这里是" << top_value;

	stack.Push(10);
	ASSERT_EQ(4, stack.Size()) << "栈中的元素个数应该是4，但这里是" << stack.Size();
	stack.Pop(&top_value);
	ASSERT_EQ(10, top_value) << "栈顶元素应该是10，但这里是" << top_value;

	stack.Pop(&top_value);
	ASSERT_EQ(3, top_value) << "栈顶元素应该是3，但这里是" << top_value;

	stack.Clear();
	ASSERT_EQ(0, stack.Size()) << "栈中的元素个数应该是0，但这里是" << stack.Size();

	// 插入一百万个元素
	for (gsize i = 0; i < 1000000; i++)
	{
		stack.Push(i);
	}
	ASSERT_EQ(1000000, stack.Size()) << "栈中的元素个数应该是1000000，但这里是" << stack.Size();
	for (gint i = 1000000 - 1; i >= 0; i--)
	{
		stack.Pop(&top_value);
		ASSERT_EQ(i, top_value) << "栈顶元素应该是" << i << "，但这里是" << top_value;
	}
	ASSERT_TRUE(stack.IsEmpty()) << "栈应该被置空，但这里不为空";

	stack.Push(100);
	stack.Push(200);
	stack.Push(300);
	stack.Push(400);
	stack.Pop();

	// 验证拷贝构造
	GListStack<gint> _stack(stack);
	ASSERT_EQ(3, _stack.Size()) << "栈中的元素个数应该是3，但这里是" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "栈中的元素不应该为空";
	_stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "栈顶元素应该是300，但这里是" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "栈顶元素应该是200，但这里是" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "栈顶元素应该是100，但这里是" << top_value;

	// 验证移动构造
	GListStack<gint> __stack(GMove(stack));
	ASSERT_TRUE(stack.IsEmpty());
	__stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "栈顶元素应该是300，但这里是" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "栈顶元素应该是200，但这里是" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "栈顶元素应该是100，但这里是" << top_value;

	stack.Push(400);
	stack.Push(500);
	stack.Push(600);
	stack.Push(700);
	stack.Pop();

	// 验证拷贝赋值
	GListStack<gint> _stack_;
	_stack_ = stack;
	ASSERT_EQ(3, _stack_.Size()) << "栈中的元素个数应该是3，但这里是" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "栈中的元素不应该为空";
	_stack_.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "栈顶元素应该是600，但这里是" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "栈顶元素应该是500，但这里是" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "栈顶元素应该是400，但这里是" << top_value;

	// 验证移动赋值
	GListStack<gint> __stack__;
	__stack__ = GMove(stack);
	ASSERT_TRUE(stack.IsEmpty());
	__stack__.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "栈顶元素应该是600，但这里是" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "栈顶元素应该是500，但这里是" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "栈顶元素应该是400，但这里是" << top_value;

	// 一个存放String类型的栈
	GListStack<GString> stack_str;
	stack_str.Push("abc");
	stack_str.Push("this is stack test of gsystem test.");
	ASSERT_EQ(2, stack_str.Size()) << "栈中的元素个数应该是2，但这里是" << stack_str.Size();
	GString str;
	stack_str.Pop(&str);
	ASSERT_EQ("this is stack test of gsystem test.", str);
}