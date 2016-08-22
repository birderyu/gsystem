#include "CsMap.h"

void TestMap()
{
	CsMap<cs_int, CsString> map;
	CsMap<cs_int, CsString>::Iterator iter = map.Insert(1, "aaa");

	int stop = 1;
	stop++;

}