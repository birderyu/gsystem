#include "CsSingleLinkedList.h"
#include "CsCircularLinkedList.h"
#include "CsDoubleLinkedList.h"

cs_void SingleLinkedListTest()
{
	CsSingleLinkedList<cs_int> list;
	list.AddTail(1);
	list.AddTail(2);
	list.AddTail(3);
	list.AddTail(4);
	list.AddTail(5);
	list.AddHead(0);
	list.AddHead(-1);
	list.AddHead(-2);

	cs_int h = list.GetHead();
	cs_int t = list.GetTail();

	cs_int i1 = list.GetAt(1);
	cs_int i5 = list.GetAt(5);

	list.InsertAfter(5, 10);

	cs_int i6 = list.GetAt(6);

	cs_int f10 = list.IndexOf(10);
	cs_int f11 = list.IndexOf(11);

	list.AddTail(0);

	cs_int fc = list.IndexOfCircle();

	int stop = 1;
	stop++;
}

cs_void CircularLinkedTest()
{
	CsCircularLinkedList<cs_int> list;
	list.AddTail(1);
	list.AddTail(2);
	list.AddTail(3);
	list.AddTail(4);

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
	list.AddTail(1);
	list.AddTail(2);
	list.AddTail(3);
	list.AddTail(4);
	list.AddTail(5);
	list.AddHead(0);
	list.AddHead(-1);
	list.AddHead(-2);

	cs_int h = list.GetHead();
	cs_int t = list.GetTail();

	cs_int i1 = list.GetAt(1);
	cs_int i5 = list.GetAt(5);

	list.InsertAfter(5, 10);

	cs_int i6 = list.GetAt(6);

	cs_int f10 = list.IndexOf(10);
	cs_int f11 = list.IndexOf(11);

	list.RemoveHead();
	list.RemoveTail();

	int stop = 1;
	stop++;
}