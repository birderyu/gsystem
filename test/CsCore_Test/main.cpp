#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"

#include "CsString.h"
#include "CsString_Private.h"

int main(int argc, char *argv[])
{
	int a = sizeof(CsString);
	int b = sizeof(CsString_Private);
	TestRBTree();
	//TestRBTree();
	//TestInsertSort();
	system("pause");
}