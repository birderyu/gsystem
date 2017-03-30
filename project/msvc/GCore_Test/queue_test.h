#pragma once
#include <gtest/gtest.h>
#include "garrayqueue.h"
#include "glistqueue.h"
#include "gstring.h"

TEST(ArrayQueueTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GArrayQueue<gint> queue;
	queue.EnQueue(1);
	queue.EnQueue(2);
	queue.EnQueue(3);
	queue.EnQueue(4);
	queue.EnQueue(5);
	ASSERT_EQ(5, queue.Size()) << "队列中的元素个数应该是5，但这里是" << queue.Size();
	ASSERT_EQ(1, queue.Head()) << "队头元素应该是1，但这里是" << queue.Head();

	gint head_value = 0;
	queue.DeQueue(&head_value);
	ASSERT_EQ(1, head_value) << "队头元素应该是1，但这里是" << head_value;
	queue.DeQueue(&head_value);
	ASSERT_EQ(2, head_value) << "队头元素应该是2，但这里是" << head_value;

	queue.EnQueue(10);
	ASSERT_EQ(4, queue.Size()) << "队列中的元素个数应该是4，但这里是" << queue.Size();
	queue.DeQueue(&head_value);
	ASSERT_EQ(3, head_value) << "队头元素应该是3，但这里是" << head_value;

	queue.EnQueue(11);
	queue.EnQueue(12);
	queue.EnQueue(13);

	queue.DeQueue(&head_value);
	ASSERT_EQ(4, head_value) << "队头元素应该是4，但这里是" << head_value;

	queue.Clear();
	ASSERT_EQ(0, queue.Size()) << "队列中的元素个数应该是0，但这里是" << queue.Size();

	// 插入一百万个元素
	for (gsize i = 0; i < 1000000; i++)
	{
		queue.EnQueue(i);
	}
	ASSERT_EQ(1000000, queue.Size()) << "队列中的元素个数应该是1000000，但这里是" << queue.Size();
	for (gint i = 0; i < 1000000; i++)
	{
		queue.DeQueue(&head_value);
		ASSERT_EQ(i, head_value) << "队头元素应该是" << i << "，但这里是" << head_value;
	}
	ASSERT_TRUE(queue.IsEmpty()) << "队列应该被置空，但这里不为空";

	queue.EnQueue(100);
	queue.EnQueue(200);
	queue.EnQueue(300);
	queue.EnQueue(400);
	queue.DeQueue();

	// 验证拷贝构造
	GArrayQueue<gint> _queue(queue);
	ASSERT_EQ(3, _queue.Size()) << "队列中的元素个数应该是3，但这里是" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "队列中的元素不应该为空";
	_queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "队头元素应该是200，但这里是" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "队头元素应该是300，但这里是" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "队头元素应该是400，但这里是" << head_value;

	// 验证移动构造
	GArrayQueue<gint> __queue(GMove(queue));
	ASSERT_TRUE(queue.IsEmpty());
	__queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "队头元素应该是200，但这里是" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "队头元素应该是300，但这里是" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "队头元素应该是400，但这里是" << head_value;

	queue.EnQueue(400);
	queue.EnQueue(500);
	queue.EnQueue(600);
	queue.EnQueue(700);
	queue.DeQueue();

	// 验证拷贝赋值
	GArrayQueue<gint> _queue_;
	_queue_ = queue;
	ASSERT_EQ(3, _queue_.Size()) << "队列中的元素个数应该是3，但这里是" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "队列中的元素不应该为空";
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "队头元素应该是500，但这里是" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "队头元素应该是600，但这里是" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "队头元素应该是700，但这里是" << head_value;

	// 验证移动赋值
	GArrayQueue<gint> __queue__;
	__queue__ = GMove(queue);
	ASSERT_TRUE(queue.IsEmpty());
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "队头元素应该是500，但这里是" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "队头元素应该是600，但这里是" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "队头元素应该是700，但这里是" << head_value;

	// 一个存放String类型的队列
	GArrayQueue<GString> queue_str;
	queue_str.EnQueue("this is queue test of gsystem test.");
	queue_str.EnQueue("abc");
	ASSERT_EQ(2, queue_str.Size()) << "队列中的元素个数应该是2，但这里是" << queue_str.Size();
	GString str;
	queue_str.DeQueue(&str);
	ASSERT_EQ("this is queue test of gsystem test.", str);
}

TEST(ListQueueTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GListQueue<gint> queue;
	queue.EnQueue(1);
	queue.EnQueue(2);
	queue.EnQueue(3);
	queue.EnQueue(4);
	queue.EnQueue(5);
	ASSERT_EQ(5, queue.Size()) << "队列中的元素个数应该是5，但这里是" << queue.Size();
	ASSERT_EQ(1, queue.Head()) << "队头元素应该是1，但这里是" << queue.Head();

	gint head_value = 0;
	queue.DeQueue(&head_value);
	ASSERT_EQ(1, head_value) << "队头元素应该是1，但这里是" << head_value;
	queue.DeQueue(&head_value);
	ASSERT_EQ(2, head_value) << "队头元素应该是2，但这里是" << head_value;

	queue.EnQueue(10);
	ASSERT_EQ(4, queue.Size()) << "队列中的元素个数应该是4，但这里是" << queue.Size();
	queue.DeQueue(&head_value);
	ASSERT_EQ(3, head_value) << "队头元素应该是3，但这里是" << head_value;

	queue.EnQueue(11);
	queue.EnQueue(12);
	queue.EnQueue(13);

	queue.DeQueue(&head_value);
	ASSERT_EQ(4, head_value) << "队头元素应该是4，但这里是" << head_value;

	queue.Clear();
	ASSERT_EQ(0, queue.Size()) << "队列中的元素个数应该是0，但这里是" << queue.Size();

	// 插入一百万个元素
	for (gsize i = 0; i < 1000000; i++)
	{
		queue.EnQueue(i);
	}
	ASSERT_EQ(1000000, queue.Size()) << "队列中的元素个数应该是1000000，但这里是" << queue.Size();
	for (gint i = 0; i < 1000000; i++)
	{
		queue.DeQueue(&head_value);
		ASSERT_EQ(i, head_value) << "队头元素应该是" << i << "，但这里是" << head_value;
	}
	ASSERT_TRUE(queue.IsEmpty()) << "队列应该被置空，但这里不为空";

	queue.EnQueue(100);
	queue.EnQueue(200);
	queue.EnQueue(300);
	queue.EnQueue(400);
	queue.DeQueue();

	// 验证拷贝构造
	GListQueue<gint> _queue(queue);
	ASSERT_EQ(3, _queue.Size()) << "队列中的元素个数应该是3，但这里是" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "队列中的元素不应该为空";
	_queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "队头元素应该是200，但这里是" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "队头元素应该是300，但这里是" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "队头元素应该是400，但这里是" << head_value;

	// 验证移动构造
	GListQueue<gint> __queue(GMove(queue));
	ASSERT_TRUE(queue.IsEmpty());
	__queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "队头元素应该是200，但这里是" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "队头元素应该是300，但这里是" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "队头元素应该是400，但这里是" << head_value;

	queue.EnQueue(400);
	queue.EnQueue(500);
	queue.EnQueue(600);
	queue.EnQueue(700);
	queue.DeQueue();

	// 验证拷贝赋值
	GListQueue<gint> _queue_;
	_queue_ = queue;
	ASSERT_EQ(3, _queue_.Size()) << "队列中的元素个数应该是3，但这里是" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "队列中的元素不应该为空";
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "队头元素应该是500，但这里是" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "队头元素应该是600，但这里是" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "队头元素应该是700，但这里是" << head_value;

	// 验证移动赋值
	GListQueue<gint> __queue__;
	__queue__ = GMove(queue);
	ASSERT_TRUE(queue.IsEmpty());
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "队头元素应该是500，但这里是" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "队头元素应该是600，但这里是" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "队头元素应该是700，但这里是" << head_value;

	// 一个存放String类型的队列
	GListQueue<GString> queue_str;
	queue_str.EnQueue("this is queue test of gsystem test.");
	queue_str.EnQueue("abc");
	ASSERT_EQ(2, queue_str.Size()) << "队列中的元素个数应该是2，但这里是" << queue_str.Size();
	GString str;
	queue_str.DeQueue(&str);
	ASSERT_EQ("this is queue test of gsystem test.", str);
}