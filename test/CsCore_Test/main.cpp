#include <iostream>
#include "CsString.h"
#include "CsArray.h"
#include "CsSort.h"
#include "CsBTree.h"

int main(int argc, char *argv[])
{
	CsBTree<cs_int> tBTree;

	CsArray<cs_int> tArray;
	tArray.ReSize(5);
	tArray[0] = 5;
	tArray[1] = 3; //
	tArray[2] = 2;
	tArray[3] = 4; //
	tArray[4] = 1;

	CsSort::HeapSort<CsArray<cs_int>, cs_int>(tArray, 2, 3);
	
	for (cs_size_t i = 0; i < tArray.Length(); i++)
	{
		cs_int v = tArray[i];
		int stop = 1;
		stop++;
	}

	int stop = 1;
	stop++;
 }