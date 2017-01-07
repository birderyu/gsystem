#include "gsinglelinkedlist.h"
#include "gcircularlinkedlist.h"
#include "gdoublelinkedlist.h"
#include "glist.h"

#include <iostream>

gvoid SingleLinkedListTest()
{
	GSingleLinkedList<gint> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);
	list.AddLast(5);
	list.AddFirst(0);
	list.AddFirst(-1);
	list.AddFirst(-2);

	gint h = list.GetFirstData();
	gint t = list.GetFirstData();

	gint i1 = list.GetDataAt(1);
	gint i5 = list.GetDataAt(5);

	list.InsertAfter(5, 10);

	gint i6 = list.GetDataAt(6);

	gint f10 = list.IndexOf(10);
	gint f11 = list.IndexOf(11);

	list.AddLast(0);

	gint fc = list.IndexOfCircle();

	int stop = 1;
	stop++;
}

gvoid CircularLinkedTest()
{
	GCircularLinkedList<gint> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);

	gint i1 = list.GetNext()->m_tData;
	gint i2 = list.GetNext()->m_tData;
	gint i3 = list.GetNext()->m_tData;
	gint i4 = list.GetNext()->m_tData;
	gint i5 = list.GetNext()->m_tData;
	gint i6 = list.GetNext()->m_tData;

	int stop = 1;
	stop++;
}

gvoid DoubleLinkedListTest()
{
	GDoubleLinkedList<gint> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);
	list.AddLast(5);
	list.AddFirst(0);
	list.AddFirst(-1);
	list.AddFirst(-2);

	gint h = list.GetFirstData();
	gint t = list.GetLastData();

	gint i1 = list.GetDataAt(1);
	gint i5 = list.GetDataAt(5);

	list.InsertAfter(5, 10);

	gint i6 = list.GetDataAt(6);

	gint f10 = list.IndexOf(10);
	gint f11 = list.IndexOf(11);

	list.RemoveFirst();
	list.RemoveLast();

	int stop = 1;
	stop++;
}

gvoid ListTest()
{
	GList<gint> datas;
	datas.PushBack(1);
	datas.PushBack(2);
	datas.PushBack(3);
	datas.PushBack(4);
	datas.PushFront(0);
	datas.PushFront(-1);

	for (GList<gint>::ConstIterator citer = datas.ConstBegin();
		citer != datas.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	std::cout << std::endl;

	datas.PopBack();
	datas.PopBack();
	datas.PopFront();

	for (GList<gint>::ConstIterator citer = datas.ConstBegin();
		citer != datas.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	gint stop = 1;
	stop++;

}