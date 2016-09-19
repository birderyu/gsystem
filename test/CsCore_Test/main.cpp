#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"
#include "MemPool_Test.h"

#include "CsString.h"
#include "CsString_Private.h"
#include "CsVariant.h"
#include "CsMemPool.h"
#include "CsNumber.h"
#include <windows.h>

int main(int argc, char *argv[])
{
	CsString ss("123");
	cs_int ii = ss.ToInt();
	//TestMemPool();
	int _nStartTime = GetTickCount(); // time
	for (int i = 0; i < 10000000; i++)
	{
		CsString s("123");
	}
	int _nEndTime = GetTickCount(); // time
	int _nTime = (_nEndTime - _nStartTime); // time

	
	system("pause");
}