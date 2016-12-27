#include "CsSingleLinkedList.h"
#include "CsCircularLinkedList.h"
#include "CsDoubleLinkedList.h"
#include "CsList.h"

#include <iostream>

cs_void SingleLinkedListTest()
{
	CsSingleLinkedList<cs_int> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);
	list.AddLast(5);
	list.AddFirst(0);
	list.AddFirst(-1);
	list.AddFirst(-2);

	cs_int h = list.GetFirstData();
	cs_int t = list.GetFirstData();

	cs_int i1 = list.GetDataAt(1);
	cs_int i5 = list.GetDataAt(5);

	list.InsertAfter(5, 10);

	cs_int i6 = list.GetDataAt(6);

	cs_int f10 = list.IndexOf(10);
	cs_int f11 = list.IndexOf(11);

	list.AddLast(0);

	cs_int fc = list.IndexOfCircle();

	int stop = 1;
	stop++;
}

cs_void CircularLinkedTest()
{
	CsCircularLinkedList<cs_int> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);

	cs_int i1 = list.GetNext()->m_tData;
	cs_int i2 = list.GetNext()->m_tData;
	cs_int i3 = list.GetNext()->m_tData;
	cs_int i4 = list.GetNext()->m_tData;
	cs_int i5 = list.GetNext()->m_tData;
	cs_int i6 = list.GetNext()->m_tData;

	int stop = 1;
	stop++;
}

cs_void DoubleLinkedListTest()
{
	CsDoubleLinkedList<cs_int> list;
	list.AddLast(1);
	list.AddLast(2);
	list.AddLast(3);
	list.AddLast(4);
	list.AddLast(5);
	list.AddFirst(0);
	list.AddFirst(-1);
	list.AddFirst(-2);

	cs_int h = list.GetFirstData();
	cs_int t = list.GetLastData();

	cs_int i1 = list.GetDataAt(1);
	cs_int i5 = list.GetDataAt(5);

	list.InsertAfter(5, 10);

	cs_int i6 = list.GetDataAt(6);

	cs_int f10 = list.IndexOf(10);
	cs_int f11 = list.IndexOf(11);

	list.RemoveFirst();
	list.RemoveLast();

	int stop = 1;
	stop++;
}

cs_void ListTest()
{
	CsList<cs_int> datas;
	datas.PushBack(1);
	datas.PushBack(2);
	datas.PushBack(3);
	datas.PushBack(4);
	datas.PushFront(0);
	datas.PushFront(-1);

	for (CsList<cs_int>::ConstIterator citer = datas.ConstBegin();
		citer != datas.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	std::cout << std::endl;

	datas.PopBack();
	datas.PopBack();
	datas.PopFront();

	for (CsList<cs_int>::ConstIterator citer = datas.ConstBegin();
		citer != datas.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	cs_int stop = 1;
	stop++;

}