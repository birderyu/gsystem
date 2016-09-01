#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"

#include "CsString.h"
#include "CsString_Private.h"
#include "CsVariant.h"

int main(int argc, char *argv[])
{
	CsVariant v("123");
	v.SetValue("321");
	CsString s = v.ToString();

	//TestBSTree();
	TestRBTree();
	//TestInsertSort();
	system("pause");
}