#include "CsString.h"
#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"
#include "MemPool_Test.h"


#include "CsStringList.h"
#include "CsVariant.h"
#include "CsMemoryPool.h"
#include "CsPackage.h"
#include "Bytes_Test.h"
#include <windows.h>
#include "CsSingleLinkedList.h"
#include "CsFilter.h"

#include <atomic>
#include "CsAtomic.h"
#include "CsMutex.h"
#include "CsNullLock.h"
#include "CsNew.h"

#include "dlmalloc.h"
#include "CsBlock.h"
#include "CsCStringHelper.h"
#include "CsString_Ex.h"
#include "CsVariant_Ex.h"
#include "List_Test.h"
#include "CsNumber.h"
#include "Hash_Test.h"

#include "CsSharedPointer.h"

#include "CsStringList.h"
#include "CsStaticArray.h"
#include "CsSingleton.h"

void TestSharedPtr()
{
	CsSharedPointer<CsString> pstr(new CsString("123"));
	if (!pstr.IsNull()) {
		CsSharedPointer<CsString> pstr2;
		pstr2 = pstr;
		cs_int i1 = pstr->ToInt();
		cs_int i2 = pstr2->ToInt();
		int stop = 1;
		stop++;
	}
	int stop = 1;
	stop++;
}

void TestArray()
{
	const cs_size_t length = 100000;
	cs_int _nStartTime = GetTickCount(); // time
	for (cs_size_t i = 0; i < length; i++)
	{
		CsDynamicArray<cs_int> arr(length);
		for (cs_size_t j = 0; j < length; j++)
		{
			arr[j] = j;
		}
	}
	cs_int _nMiddleTime = GetTickCount(); // time
	for (cs_size_t i = 0; i < length; i++)
	{
		cs_int *arr = new cs_int[length];
		for (cs_size_t j = 0; j < length; j++)
		{
			arr[j] = j;
		}
		delete[]arr;
	}
	cs_int _nEndTime = GetTickCount(); // time
	cs_int _nTime1 = (_nMiddleTime - _nStartTime); // time
	cs_int _nTime2 = (_nEndTime - _nMiddleTime); // time
}

int main(int argc, char *argv[])
{
	CsBytes bytes;
	cs_byte v1 = 9;
	cs_int v2 = 123321;
	cs_int64 v3 = 1233211233223321LL;
	cs_float v4 = 9.87;
	cs_double v5 = 2314.6546546;
	bytes << v1 << v2 << v3 << v4 << v5;

	cs_byte _v1;
	cs_int _v2;
	cs_int64 _v3;
	cs_float _v4;
	cs_double _v5;
	bytes >> _v1 >> _v2 >> _v3 >> _v4 >> _v5;

	//TestHashTable();
	//TestBSTree();
	//TestSharedPtr();

	//TestHashTable();
	//DoubleLinkedListTest();

	cs_int ___nStartTime = GetTickCount(); // time

	//CsString str1("123456789012345123456789012345123456789012345123456789012345123456789012345");
	//CsString str1("123");
	for (cs_size_t i = 0; i < 10000000; i++)
	{
		//CsString str("123456789012345");
		//std::string str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		//CsString str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		CsString_Ex str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		//delete str;

		//CsString str(str1);
	}
	cs_int ___nEndTime = GetTickCount(); // time
	cs_int ___nTime = (___nEndTime - ___nStartTime); // time

	system("pause");
}