#include "gstring.h"
#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"
#include "MemPool_Test.h"


#include "gstringlist.h"
#include "gvariant.h"
#include "gmemorypool.h"
#include "gpackage.h"
#include "Bytes_Test.h"
#include <windows.h>
#include "gsinglelinkedlist.h"

#include <atomic>
#include "gatomic.h"
#include "gmutex.h"
#include "gvoidlock.h"
#include "gnew.h"

#include "gblock.h"
#include "gcstringhelper.h"
#include "List_Test.h"
#include "gnumber.h"
#include "Hash_Test.h"

#include "gsharedpointer.h"

#include "gstringlist.h"
#include "gstaticarray.h"
#include "gsingleton.h"
#include "gbinaryheap.h"

#include "Array_Test.h"
#include "Vector_Test.h"
#include "File_Test.h"
#include "Map_Test.h"
#include "Set_Test.h"
//#include "CsRTree.h"

void TestSharedPtr()
{
	GSharedPointer<GString> pstr(new GString("123"));
	if (!pstr.IsNull()) {
		GSharedPointer<GString> pstr2;
		pstr2 = pstr;
		gint i1 = pstr->ToInt();
		gint i2 = pstr2->ToInt();
		int stop = 1;
		stop++;
	}
	int stop = 1;
	stop++;
}

void TestArray()
{
	const gsize length = 100000;
	gint _nStartTime = GetTickCount(); // time
	for (gsize i = 0; i < length; i++)
	{
		GDynamicArray<gint> arr(length);
		for (gsize j = 0; j < length; j++)
		{
			arr[j] = j;
		}
	}
	gint _nMiddleTime = GetTickCount(); // time
	for (gsize i = 0; i < length; i++)
	{
		gint *arr = new gint[length];
		for (gsize j = 0; j < length; j++)
		{
			arr[j] = j;
		}
		delete[]arr;
	}
	gint _nEndTime = GetTickCount(); // time
	gint _nTime1 = (_nMiddleTime - _nStartTime); // time
	gint _nTime2 = (_nEndTime - _nMiddleTime); // time
}

class CSAAA
	: public GObject
{

};

int main(int argc, char *argv[])
{
	gchar c = 'b';
	gbool b = G_CHAR_IS_SPACE(c);

	SetTest();
	TestMap();

	ListTest();

	TestTextFile();

	TestBytes();
	//TestDynamicArray();
	TestVector();

	gint arr[5];
	arr[0] = 12;
	arr[1] = 21;
	arr[2] = 32;
	arr[3] = 1;
	arr[4] = 18;

	GMinHeap<gint> min_heap;
	//MaxHeap<cs_int> min_heap;
	min_heap.Append(arr, 5);
	//min_heap.Insert(12);
	//min_heap.Insert(21);
	//min_heap.Insert(32);
	//min_heap.Insert(1);
	//min_heap.Insert(18);
	min_heap.Output();
	gint a1, a2, a3, a4, a5;
	min_heap.Pop(&a1);
	min_heap.Pop(&a2);
	min_heap.Pop(&a3);
	min_heap.Pop(&a4);
	min_heap.Pop(&a5);

	gsize ssss1 = GBytes::MAX_SIZE;
	gsize ssss2 = GBytes::NULL_POS;
	GBytes bytes;
	gbyte v1 = 9;
	gint v2 = 123321;
	gint64 v3 = 1233211233223321LL;
	gfloat v4 = 9.87;
	gdouble v5 = 2314.6546546;
	bytes << v1 << v2 << v3 << v4 << v5;

	gbyte _v1;
	gint _v2;
	gint64 _v3;
	gfloat _v4;
	gdouble _v5;
	bytes >> _v1 >> _v2 >> _v3 >> _v4 >> _v5;

	//TestHashTable();
	//TestBSTree();
	//TestSharedPtr();

	//TestHashTable();
	//DoubleLinkedListTest();

	gint ___nStartTime = GetTickCount(); // time

	//CsString str1("123456789012345123456789012345123456789012345123456789012345123456789012345");
	//CsString str1("123");
	for (gsize i = 0; i < 10000000; i++)
	{
		//CsString str("123456789012345");
		//std::string str("123");
		//CsString str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		GString str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		//delete str;

		//CsString str(str1);
	}
	gint ___nEndTime = GetTickCount(); // time
	gint ___nTime = (___nEndTime - ___nStartTime); // time

	system("pause");
}