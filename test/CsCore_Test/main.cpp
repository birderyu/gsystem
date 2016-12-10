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

int main(int argc, char *argv[])
{
	TestHashTable();
	//TestBSTree();
	std::string stdstr;
	cs_size_t stdstrsize = stdstr.max_size();
	cs_size_t stdstrnpos= stdstr.npos;

	CsString s1("111");
	CsString s2("222");
	cs_cstring cs1 = s1.CString();
	cs_cstring cs2 = s2.CString();
	CsStringList sl;
	sl.Add(s1);
	sl.Add(s2);
	CsString sl1 = sl.GetAt(0);
	CsString sl2 = sl.GetAt(1);
	cs_cstring csl1 = sl1.CString();
	cs_cstring csl2 = sl2.CString();

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
		CsString str("123456789012345123456789012345123456789012345123456789012345123456789012345");
		//CsString_Ex str("123");
		//delete str;

		//CsString str(str1);
	}
	cs_int ___nEndTime = GetTickCount(); // time
	cs_int ___nTime = (___nEndTime - ___nStartTime); // time

	system("pause");
}